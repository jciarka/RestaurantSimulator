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
    virtual IClient::client_state get_state() const = 0;

    // interfejs dla kelnera
    virtual std::vector<IClient*> get_clients() = 0;

    // interfejs dla generatora grup
    virtual void add_client(std::unique_ptr<IClient> client) = 0;

    // interfejs dla klienta
    virtual void on_client_state_changed(IClient* clinet) = 0;
    virtual ITable* get_table() const = 0;

    // interfejs dla sto³u
    virtual unsigned get_members_num() const = 0;
    virtual void seat_at_table(ITable* table) = 0;  // uwaga metodê wywo³uje tylko stó³
    virtual void begin_feast() = 0;

    // funkcja remove clients dedykowana do ³¹czenia grup - musi dealokowaæ wszelkie zasoby w do³¹czanej grupie
    virtual std::unique_ptr<std::vector<std::unique_ptr<IClient> > > move_clients() = 0;
    virtual void merge(std::unique_ptr<IGroup> group) = 0;

    virtual ~IGroup() = 0 {}; // Delete clients 
};