#pragma once
#include <vector>
#include "ITrigger.h"


// The Trigger class holds pointers to all objects
// in restaurants requiring the use of tools in the time regime
//
// Object deriving from ITriggered are added to the Triger list at the time of their initiation
// and are deleted at the time of destruction
//
// The execute_iteration method calls execute_iteration methods of all subscribed objects



class Trigger : public ITrigger
{
private:
    std::vector<ITriggered*> iterated_objects;
    std::vector<ITriggered*> objects_to_add;

public:
    virtual void execute_iteration() override;
    virtual void add_iterated_object(ITriggered* triggered_object) override;
    virtual void remove_iterated_object(ITriggered* triggered_object) override;
    virtual ~Trigger() {};
};