#pragma once
#include "fwd_include.h"

class IWaiter
{
    // pami�taj wska�nik 
    // IKitchen -> take_order()
    // IKitchen -> get_preapared()
    // wska�nik na kolekjke serwsiow - IGroup* take_servce()

public:
    virtual ~IWaiter() = 0 {};
};
