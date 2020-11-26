#include "Table.h"
#include <sstream>

// ______________________________________________________________________________________________________
// Czêœæ statyczna
unsigned Table::id_counter = 0; // Inicjacja pocz¹tkowej wartosci od której nadawane bêdzie id

unsigned Table::generate_unique_id()
{
	return ++id_counter;
}
// ______________________________________________________________________________________________________


unsigned Table::get_id() const
{
    return 0;
}

bool Table::is_available() const
{
	if (group == nullptr)
	{
		return true;
	}

	if (group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		return true;
	}

	return false;
}

unsigned Table::get_empty_seats() const
{
	if (!is_available())
	{
		return 0;
	}

	if (group == nullptr)
	{
		return seats_number;
	}

	if (group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		return seats_number - group->get_members_num();
	}
}

bool Table::check_can_place_group(IGroup* group)
{
	if (group == nullptr)
	{
		return false;
	}

	// SprawdŸ czy dodawana grupa jest w odpowiedim stanie oraz czy jest odpowiednia liczba miejsc przy stole
	if (group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		if (get_empty_seats() <= group->get_members_num())
			return false;
	}
	else if (group->get_state() == IClient::client_state::READY_TO_BEGIN)
	{
		if (get_empty_seats() < group->get_members_num())
			return false;
	}
	else
	{
		return false;
	}
	return true;
}

void Table::place_group(IGroup* group)
{
	if (!check_can_place_group(group))
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group is invalid to be posed at table: " << id;
		throw std::logic_error(error_txt_stream.str());
	}

	if (this->group == nullptr)
	{
		// Powi¹¿ grupê i stolik
		this->group = group;
		group->seat_at_table(this);
	}
	else if (this->group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		// Po³¹cz grupê z istniej¹ca grup¹
		this->group->merge(group);
	}
	else
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group " << id << ": can't marge with other group when"
			<< " it is not waiting for friends or ready to eat";
		throw std::logic_error(error_txt_stream.str());
	}
}


void Table::on_group_state_change(IGroup* group)
{
	if (group->get_state() == IClient::client_state::LEAVING)
	{
		group_preapring_to_leave = true;
	}
}

Table::~Table()
{
	if (group != nullptr)
	{
		delete group;
	}
}
