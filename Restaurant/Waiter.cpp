#include "Waiter.h"
#include "IServiceQueue.h"
#include "IOrder.h"
#include "IClient.h"

#include <vector>
#include <sstream>



Waiter::Waiter(IKitchen* kitchen, IServiceQueue* service_queue, ITrigger& global_trigger, IRaporter& global_raporter)
	: Triggered(global_trigger), Raportable(global_raporter), kitchen(kitchen), service_queue(service_queue)
{
}

void Waiter::execute_iteration()
{
	IOrder* order = kitchen->deliver_preapared();
	if (order != nullptr)
	{
		IClient* client = order->get_client();
		client->pick_up_order(order);
		return;
	}
	
	IGroup* group = service_queue->dequeue_service();
	if (group != nullptr)
	{
		std::vector<IOrder*> orders;
		std::stringstream error_txt_stream;

		switch (group->get_group_state())		
		{
		case IClient::client_state::READY_TO_ORDER:
			for (auto client : group->give_clients())
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
			for (auto client : group->give_clients())
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