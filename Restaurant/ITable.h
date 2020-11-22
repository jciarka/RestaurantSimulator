#pragma once

#include "fwd_include.h"

#include "IGroup.h"

class ITable
{
    // Wektor grup
public:

    // interfejs dla generatora klientów
    virtual bool is_available() = 0;
    virtual unsigned get_empty_seats() = 0;
    virtual void place_group() = 0;

    // interface dla grupy
    virtual void on_group_state_change(IGroup* group) = 0;

    virtual ~ITable() = 0 {};
};
