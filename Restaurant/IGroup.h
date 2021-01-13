#pragma once

#include "fwd_include.h"

#include <vector>
#include "IClient.h"


class IGroup
{
public:

    virtual unsigned get_id() const = 0;
    virtual IClient::client_state get_state() const = 0;

    // Interface for Waiter
    virtual std::vector<IClient*> get_clients() = 0;

    // Interface for gorup generator
    virtual void add_client(std::unique_ptr<IClient> client) = 0;

    // interface for Waiter
    virtual void on_client_state_changed(IClient* clinet) = 0;
    virtual ITable* get_table() const = 0;

    // interface for Table
    virtual unsigned get_members_num() const = 0;
    virtual void seat_at_table(ITable* table) = 0;  // uwaga metodê wywo³uje tylko stó³
    virtual void begin_feast() = 0;

    // function below addes clients to existing group
    virtual std::unique_ptr<std::vector<std::unique_ptr<IClient> > > move_clients() = 0;
    virtual void merge(std::unique_ptr<IGroup> group) = 0;

    virtual ~IGroup() = 0 {};

    friend std::ostream& operator<<(std::ostream& os, const IGroup& group);
};