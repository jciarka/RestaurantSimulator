#pragma once
#pragma once

#include "IGroup.h"
#include "TestTable.h"
#include <iostream>


class TestGroup : public IGroup
{
public:
    // wektor klientów 
    // wskaxnik na stolik
    // wskaŸnik na kolekjke serwsiow - raise_service(IGroup*)
    ITable* table;

    TestGroup() 
    {
        table = new TestTable();
    }

    virtual unsigned get_id() const override { return 1; }

    // interfejs dla kelnera
    virtual std::vector<IClient*> get_clients() override
    {
        std::vector<IClient*> clients;
        return clients;
    }

    // interfejs dla klienta
    virtual void on_client_state_changed(IClient* clinet) override
    {
        //std::cout << " Klient nr " << clinet->get_id() << "zglasza zmiane stanu" << std::endl;
    } 

    // interfejs dla generatora grup
    virtual void add_client(std::unique_ptr<IClient> client) override { return; };

    // interfejs dla sto³u
    virtual unsigned get_members_num() const override { return 0; };
    virtual void begin_feast() override { };
    virtual void seat_at_table(ITable* table) override { };
    virtual void merge(std::unique_ptr<IGroup> group) override { };
    virtual std::unique_ptr<std::vector<std::unique_ptr<IClient> > > move_clients() override
    {
        std::unique_ptr<std::vector<std::unique_ptr<IClient> > > temp { nullptr };
        return temp;
    } 

    virtual ITable* get_table() const override { return table; };

    virtual IClient::client_state get_state() const override { return IClient::client_state::READY_TO_BEGIN; };



    virtual ~TestGroup() override 
    {
        if (table != nullptr)
        {
            delete table;
        }
    }; // Delete clients 
};


