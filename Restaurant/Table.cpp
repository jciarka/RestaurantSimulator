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


Table::Table(unsigned seats_num, ITrigger* global_trigger, IRaporter* global_raporter) 
	         : Triggered(global_trigger), Raportable(global_raporter), id(generate_unique_id()),
			   seats_number(seats_num), group(nullptr), group_preapring_to_leave(false)
{
}

unsigned Table::get_id() const
{
    return 0;
}


bool Table::is_available() const
{
	/// There are two options when table is avilable:
	/// - when there is no group at it
	/// - when the group is waiting for friends

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
	/// There are two options when table is avilable:
	/// - when there is no group at it returns number of seats
	/// - when the group is waiting for friends returns number of empty seats
	/// - returns 0 otherwise

	if (group == nullptr)
	{
		return seats_number;
	}

	if (group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		return seats_number - group->get_members_num();
	}

	return 0;
}


bool Table::can_place_group(const IGroup* group) const
{
	/// Returns true when:
	/// - when table is empty or group at it is waiting for friends and
	///	  there is enough free seats at it:
	///			-> If group that is going to be placed is READY_TO_BEGIN
	///            number of seats must be equal or greater than the number of clients in this group
	///			-> If group that is going to be placed is WAITING_FOR_FRIENDS 
	///            number of seats must be greater than the number of clients in this group
	///            so there is some space left for another group that is going to join in the future 
	/// 
	/// - returns false otherwise
 
	if (group == nullptr)
	{
		return false;
	}

	// SprawdŸ czy dodawana grupa jest w odpowiedim stanie oraz czy jest odpowiednia liczba miejsc przy stole
	if (group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		// Jeœli grupa jest typu WAITING_FOR_FRIENDS przynajmniej jedno miejsce musi zostac wolne
		if (group->get_members_num() < get_empty_seats())
			return true;
	}
	else if (group->get_state() == IClient::client_state::READY_TO_BEGIN)
	{
		// Mo¿na zaj¹c wszytkie wolne miejsca
		if (group->get_members_num() <= get_empty_seats())
			return true;
	}

	// Jeœli niewystarczaj¹ca liczba miejsc lub grupa w innym stanie zwróæ false 
	return false;
}


void Table::place_group(std::unique_ptr<IGroup> group)
{
	/// Returns true when:
	/// - checks conditions for placing group and if table is:
	///			-> empty - group is posed at this table
	///			-> with group that is WAITING_FOR_FRIENDS groups are merged
	/// 
	if (!can_place_group(group.get()))
	{
		std::stringstream error_txt_stream;
		error_txt_stream << "Group is invalid to be posed at table: " << id;
		throw std::logic_error(error_txt_stream.str());
	}

	if (this->group == nullptr)
	{
		// Pose group at table
		// inform group about the table
		group->seat_at_table(this);

		// bind group with table
		this->group = std::move(group);
	}
	else if (this->group->get_state() == IClient::client_state::WAITING_FOR_FRIENDS)
	{
		// Merge group with existing group
		this->group->merge(std::move(group));
	}
	else
	{
		// throw exception otherwise
		std::stringstream error_txt_stream;
		error_txt_stream << "Group " << id << ": can't marge with other group when"
			<< " it is not waiting for friends or ready to eat";
		throw std::logic_error(error_txt_stream.str());
	}
}


void Table::on_group_state_change(IGroup* group)
{
	/// 
	/// State change handling
	/// in this case should handle only leaving group
	/// can't reset group in this method because it is called by this group
	/// remember information that group must be reseted at next execute_iteration call
	/// 
	if (group->get_state() == IClient::client_state::LEAVING)
	{
		group_preapring_to_leave = true;
	}
}

void Table::execute_iteration()
	///
	/// Handles leaving group if necesarry
	/// 
{
	if (group_preapring_to_leave)
	{
		group_preapring_to_leave = false;

		std::stringstream raport_stream;
		raport_stream << "Table: " << get_id() <<
			             " Group " << group->get_id() << " has left restaurant";
		raport(raport_stream.str());

		// delete group
		// table MUST define group as nullptr, when no group at table
		group.reset(nullptr);
	}
}

Table::~Table()
{
}
