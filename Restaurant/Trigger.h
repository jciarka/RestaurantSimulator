#pragma once
#include <vector>
#include "ITrigger.h"

/// <summary>
/// Klasa Trigger zawiera wskaŸniki na wszytkie obiekty 
/// w restauracji które musz¹ wykonywaæ pewne czynnoœci w re¿imie czasowym
/// 
/// Za dodawnaie obiektów odpowiadaj¹ same obiekty w restauracji - 
/// nale¿ zadbaæ aby dodawa³y siê do listy Trigera w momencie ich inicjacji
/// oraz usuwa³y siê w chwili destrukcji
/// 
/// Wywolywana jest metoda execute_iteration wszystkich subskrybowanych obiektów
/// przez metodê execute_iteration() klasy Trigger
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