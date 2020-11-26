#pragma once
#pragma once

#include "IGroup.h"
#include <iostream>

class TestGroup : public IGroup
{
public:
    // wektor klientów 
    // wskaxnik na stolik
    // wskaŸnik na kolekjke serwsiow - raise_service(IGroup*)

    virtual unsigned get_id() const override { return 1; }

    // interfejs dla kelnera
    std::vector<IClient*> get_clients() const override
    {
        std::vector<IClient*> clients;
        return clients;
    }

    // interfejs dla klienta
    virtual void on_client_state_changed(IClient* clinet) override
    {
        //std::cout << " Klient nr " << clinet->get_id() << "zglasza zmiane stanu" << std::endl;
    } 
    // interfejs dla sto³u
    virtual unsigned get_members_num() const override { return 0; };
    virtual void begin_feast() override { };
    virtual void seat_at_table(ITable* table) override { };
    virtual void merge(IGroup* group) override { };
    virtual std::vector<IClient*> remove_clients() { return get_clients(); };
    virtual ITable* get_table() const override { return nullptr; };

    virtual IClient::client_state get_state() const override { return IClient::client_state::EATING; };



    virtual ~TestGroup() override { }; // Delete clients 
};


