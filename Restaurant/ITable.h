#pragma once

#include "fwd_include.h"

#include "IGroup.h"

class ITable
{
    // Wektor grup
public:

    virtual unsigned get_id() const = 0;

    // interfejs dla generatora klientów
    virtual bool is_available() const = 0;
    virtual unsigned get_empty_seats() const = 0;
    virtual bool can_place_group(const IGroup* group) const = 0;
    virtual void place_group(std::unique_ptr<IGroup> group) = 0;

    // interface dla grupy
    virtual void on_group_state_change(IGroup* group) = 0;

    virtual ~ITable() = 0 { };

    friend std::ostream& operator<<(std::ostream& os, const ITable& table);
};
