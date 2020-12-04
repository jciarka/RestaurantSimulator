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

IOrder* Kitchen::deliver_preapared()
{
	if (prepared.empty())
		return nullptr;
	
	// Pobierz najstarzy element
	IOrder* order = prepared.front();
	// Usuñ go z kolejki
	prepared.pop();
	return order;
}

void Kitchen::on_dish_state_change(IDish* dish)
{
	if (dish->get_state() != IDish::dish_state::PREPARED)
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Dish " << dish->get_id() << ": Kitchen on_dish_state_change called when dish is not prepared";
		throw std::logic_error(error_txt_stream.str());
	}
	
	// ZnajdŸ zamówienie wektorze at_preparation
	auto order_pos = std::find_if(at_preparation.begin(), at_preparation.end(),
		[&](IOrder* order) { return order->get_dish() == dish; });
	if (order_pos == at_preparation.end())
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Dish " << dish->get_id() << ": Kitchen on_dish_state_change called and dish is not in at_preparation";
		throw std::logic_error(error_txt_stream.str());
	}

	// Dodaj do kolejki prepared
	IOrder* order = *order_pos;
	prepared.push(order);

	// Usuñ z wektora at_preparation
	at_preparation.erase(order_pos);

	// raportuj
	std::ostringstream raport_steram;
	raport_steram << "Kitchen: " << dish->to_string()
		<< " for Client " << order->get_client()->get_id()
		<< " is ready for delivery";
	raport(raport_steram.str());
}
