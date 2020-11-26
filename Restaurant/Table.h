#pragma once

#include "ITable.h"

class Table : public Triggered, public Raportable, public ITable
{
private:
    static unsigned id_counter;
    static unsigned generate_unique_id();

    unsigned id;
    IGroup* group;
    bool group_preapring_to_leave;
    unsigned seats_number;

    bool check_can_place_group(IGroup* group);

public:

    virtual unsigned get_id() const;

    // interfejs dla generatora klientów
    virtual bool is_available() const;
    virtual unsigned get_empty_seats() const;
    virtual void place_group(IGroup* group);

    // interface dla grupy
    virtual void on_group_state_change(IGroup* group);

    virtual ~Table() override;
};
