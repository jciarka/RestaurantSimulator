#pragma once

#include "ITable.h"

class Table : public Triggered, public Raportable, public ITable
{
private:
    static unsigned id_counter;
    static unsigned generate_unique_id();

    unsigned id;
    std::unique_ptr<IGroup> group;
    bool group_preapring_to_leave;
    unsigned seats_number;

public:
    Table(unsigned seats_number, ITrigger* global_trigger, IRaporter* global_raporter);

    virtual unsigned get_id() const;

    // interfejs dla generatora klientów
    virtual bool is_available() const override;
    virtual unsigned get_empty_seats() const override;
    virtual bool can_place_group(const IGroup* group) const override;
    virtual void place_group(std::unique_ptr<IGroup> group) override;

    // interface dla grupy
    virtual void on_group_state_change(IGroup* group) override;

    // Triggered
    virtual void execute_iteration() override;

    virtual ~Table() override;
};
