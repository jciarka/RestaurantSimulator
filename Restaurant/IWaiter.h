#pragma once
#include "fwd_include.h"

class IWaiter
{
    // pamiÍtaj wskaünik 
    // IKitchen -> take_order()
    // IKitchen -> get_preapared()
    // wskaünik na kolekjke serwsiow - IGroup* take_servce()

public:
    virtual ~IWaiter() = 0 {};
};
