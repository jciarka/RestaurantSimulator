#pragma once
#include "IGroup.h"

class IServiceQueue
{
public:
    virtual void queue_service(IGroup* group) = 0;
    virtual IGroup* dequeue_service() = 0;

    virtual ~IServiceQueue() = 0 {};
};
