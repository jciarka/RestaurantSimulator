#pragma once
#include "IServiceQueue.h"
#include "Raportable.h"
#include <queue>

class ServiceQueue : public Raportable, public IServiceQueue
{
public:
    std::queue<IGroup*> service_queue;

public:
    ServiceQueue(IRaporter& global_raporter);

    virtual void queue_service(IGroup* group) override;
    virtual IGroup* dequeue_service() override;

    virtual ~ServiceQueue() override {};
};
