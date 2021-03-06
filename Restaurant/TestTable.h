#pragma once

#include "ITable.h"

class TestTable : public ITable
{
    // Wektor grup
public:

    virtual unsigned get_id() const override { return 4; };

    // interfejs dla generatora klient?w
    virtual bool is_available() const override { return true; };
    virtual unsigned get_empty_seats() const override  { return 20; };
    virtual bool can_place_group(const IGroup* group) const override { return true; };
    virtual void place_group(std::unique_ptr<IGroup> group) override { };

    // interface dla grupy
    virtual void on_group_state_change(IGroup* group) override { };

    virtual ~TestTable() {};
};
