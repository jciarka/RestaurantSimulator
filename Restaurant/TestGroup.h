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
    std::vector<IClient*> give_clients() override
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
    virtual unsigned get_members_num() override { return 0; };
    virtual unsigned merge(IGroup* group) override { return 1;  };
    virtual IClient::client_state get_group_state() override { return IClient::client_state::EATING; };


    virtual ~TestGroup() override { }; // Delete clients 
};