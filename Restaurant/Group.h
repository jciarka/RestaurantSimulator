#pragma once

#include "IGroup.h"


class Group : public Triggered, public Raportable, public IGroup
{
private:
    static unsigned id_counter;
    static unsigned generate_unique_id();

    const unsigned id;
    IClient::client_state state;
    ITable* table;
    IServiceQueue* const service_queue;
    std::vector<IClient*> clients;

public:
    Group(bool waiting_for_friends, IServiceQueue* service_queue, ITrigger& global_trigger, IRaporter& global_raporter);

    virtual unsigned get_id() const override;
    virtual IClient::client_state get_state() const override;

    // interfejs dla kelnera
    virtual std::vector<IClient*> get_clients() const override;
    virtual ITable* get_table() const override;

    // interfejs dla klienta
    virtual void on_client_state_changed(IClient* clinet) override;

    // interfejs dla sto³u
    virtual unsigned get_members_num() const override;
    virtual void seat_at_table(ITable* table) override;
    virtual void begin_feast() override;

    virtual std::vector<IClient*> remove_clients() override;
    virtual void merge(IGroup* group) override;

    // Triggered
    virtual void execute_iteration() override { };

    virtual ~Group(); // Delete clients 
};
