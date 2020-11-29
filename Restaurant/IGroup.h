#pragma once

#include "fwd_include.h"

#include <vector>
#include "IClient.h"


class IGroup
{
public:
    // wektor klient�w 
    // wskaxnik na stolik
    // wska�nik na kolekjke serwsiow - raise_service(IGroup*)

    virtual unsigned get_id() const = 0;
    virtual IClient::client_state get_state() const = 0;

    // interfejs dla kelnera
    virtual std::vector<IClient*> get_clients() const = 0;

    // interfejs dla generatora grup
    virtual void add_client(IClient* client) = 0;

    // interfejs dla klienta
    virtual void on_client_state_changed(IClient* clinet) = 0;
    virtual ITable* get_table() const = 0;

    // interfejs dla sto�u
    virtual unsigned get_members_num() const = 0;
    virtual void seat_at_table(ITable* table) = 0;  // uwaga metod� wywo�uje tylko st�
    virtual void begin_feast() = 0;

    // funkcja remove clients dedykowana do ��czenia grup - musi dealokowa� wszelkie zasoby w do��czanej grupie
    virtual std::vector<IClient*> remove_clients() = 0;
    virtual void merge(IGroup* group) = 0;

    virtual ~IGroup() = 0 {}; // Delete clients 
};