#pragma once

#include "IGroup.h"
/*

class Group : public TriggeredCounter, public Raportable, public IGroup
{
private:
    static unsigned id_counter;
    static unsigned generate_unique_id();

    unsigned id;
    IClient::client_state state;

    std::vector<IClient*> clients;
    ITable* table;
    IServiceQueue* service_queue;
public:
    Group(bool waiting_for_friends, ITable* table, ITrigger& global_trigger, IRaporter& global_raporter);

    virtual unsigned get_id() const override;

    // interfejs dla kelnera
    virtual std::vector<IClient*> give_clients() override;

    // interfejs dla klienta
    virtual void on_client_state_changed(IClient* clinet) override;

    // interfejs dla sto³u
    virtual unsigned get_members_num() override;
    virtual unsigned merge(IGroup* group) override;
    virtual IClient::client_state get_group_state() override;


    virtual ~Group(); // Delete clients 
};
*/