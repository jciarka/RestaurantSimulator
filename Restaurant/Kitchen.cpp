#include "Kitchen.h"
#include <sstream>
#include <algorithm>

Kitchen::Kitchen(IRaporter* global_raporter) : Raportable(global_raporter)
{ }

void Kitchen::take_order(IOrder* order)
{
	IDish* dish = order->get_dish();
	dish->set_kitchen(this);
	dish->begin_preparing();
	at_preparation.push_back(order);

	std::ostringstream raport_steram;
	raport_steram << "Kitchen: " << dish->to_string()
		<< " for Client " << order->get_client()->get_id()
		<< " - preparation starts";
	raport(raport_steram.str());
}

/// <summary>
/// Pass to waiter oldest prepared dish that is not delivered yet
/// </summary>
IOrder* Kitchen::deliver_preapared()
{
	if (prepared.empty())
		return nullptr;
	
	// Get oldest element in service queue
	IOrder* order = prepared.front();
	prepared.pop();
	return order;
}

/// <summary>
/// Move prepared dishes to queue of dishes to deliver
/// </summary>
void Kitchen::on_dish_state_change(IDish* dish)
{
	if (dish->get_state() != IDish::dish_state::PREPARED)
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Dish " << dish->get_id() << ": Kitchen on_dish_state_change called when dish is not prepared";
		throw std::logic_error(error_txt_stream.str());
	}
	
	// Find wright order in at_preparation vector
	auto order_pos = std::find_if(at_preparation.begin(), at_preparation.end(),
		[&](IOrder* order) { return order->get_dish() == dish; });
	if (order_pos == at_preparation.end())
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Dish " << dish->get_id() << ": Kitchen on_dish_state_change called and dish is not in at_preparation";
		throw std::logic_error(error_txt_stream.str());
	}

	// Add to prepared queue - orderes that are waiting for delivery
	IOrder* order = *order_pos;
	prepared.push(order);

	// Delete from at_preparation vector
	at_preparation.erase(order_pos);

	// Raport
	std::ostringstream raport_steram;
	raport_steram << "Kitchen: " << dish->to_string()
		<< " for Client " << order->get_client()->get_id()
		<< " is ready for delivery";
	raport(raport_steram.str());
}
