#pragma once
#include <vector>
#include "ITrigger.h"

/// <summary>
/// Klasa Trigger zawiera wska�niki na wszytkie obiekty 
/// w restauracji kt�re musz� wykonywa� pewne czynno�ci w re�imie czasowym
/// 
/// Za dodawnaie obiekt�w odpowiadaj� same obiekty w restauracji - 
/// nale� zadba� aby dodawa�y si� do listy Trigera w momencie ich inicjacji
/// oraz usuwa�y si� w chwili destrukcji
/// 
/// Wywolywana jest metoda execute_iteration wszystkich subskrybowanych obiekt�w
/// przez metod� execute_iteration() klasy Trigger
/// </summary>
/// 

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