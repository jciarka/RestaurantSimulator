#include "Waiter.h"
#include "IServiceQueue.h"
#include "IOrder.h"
#include "IClient.h"

#include <vector>
#include <sstream>

// ______________________________________________________________________________________________________
// STATIC PART
unsigned Waiter::id_counter = 0;

unsigned Waiter::generate_unique_id()
{
	return ++id_counter;
}
// ______________________________________________________________________________________________________


Waiter::Waiter(IMenu* menu, IKitchen* kitchen, IServiceQueue* service_queue, ITrigger* global_trigger, IRaporter* global_raporter)
	: Triggered(global_trigger), Raportable(global_raporter), kitchen(kitchen), service_queue(service_queue), menu(menu), id(generate_unique_id())
{
}

unsigned Waiter::get_id() const
{
	return id;
}


/// <summary>
/// Waiter logic
/// </summary>
void Waiter::execute_iteration()
{

	// Firstly try to deliver prepared order
	IDish* order = kitchen->deliver_preapared();
	if (order != nullptr)
	{
		// Raport
		std::ostringstream raport_stream;
		raport_stream << *this << " delivering " << *order;
		raport(raport_stream.str());

		// deliver
		order->deliver();
		return;
	}
	
	// Else get group from service queue and try to serve it
	IGroup* group = service_queue->dequeue_service();
	if (group != nullptr)
	{
		std::vector<IDish*> orders;
		std::stringstream error_txt_stream;
		std::ostringstream raport_stream;


		switch (group->get_state())		
		{
		case IClient::client_state::WAITING_FOR_CARD:
			// Raport
			raport_stream << *this << " delivering cards to " << *group;
			raport(raport_stream.str());
			
			// Serve
			for (auto client : group->get_clients())
			{
				client->take_card(menu);
			}
			break;


		case IClient::client_state::READY_TO_ORDER:
			// Raport
			raport_stream << *this << " taking order from " << *group;
			raport(raport_stream.str());

			// Serve
			for (auto client : group->get_clients())
			{
				for (auto order : client->give_order())
				{
					orders.push_back(order);
				}
			}
			
			for (auto order : orders)
			{
				kitchen->take_order(order);
			}
			break;

		case IClient::client_state::FINISHED_EATING:
			// Raport
			raport_stream << *this << " taking payment form: " << *group;
			raport(raport_stream.str());

			// Serve
			for (auto client : group->get_clients())
			{
				client->pay();
			}
			break;

		default:
			error_txt_stream << "Service called when group is not READY_TO_ORDER or FINISHED_EATING";
			throw std::logic_error(error_txt_stream.str());
			break;
		}

	}   
}