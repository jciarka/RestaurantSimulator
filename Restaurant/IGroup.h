#pragma once

#include "fwd_include.h"

#include <vector>
#include "IClient.h"


class IGroup
{
public:
    // wektor klientów 
    // wskaxnik na stolik
    // wskaŸnik na kolekjke serwsiow - raise_service(IGroup*)

    virtual unsigned get_id() const = 0;

    // interfejs dla kelnera
    virtual std::vector<IClient*> give_clients() = 0;

    // interfejs dla klienta
    virtual void on_client_state_changed(IClient* clinet) = 0;

    // interfejs dla sto³u
    virtual unsigned get_members_num() = 0;
    virtual unsigned merge(IGroup* group) = 0;
    virtual IClient::client_state get_group_state() = 0;


    virtual ~IGroup() = 0 {}; // Delete clients 
};