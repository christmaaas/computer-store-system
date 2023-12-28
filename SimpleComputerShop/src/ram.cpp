#include "ram.h"

namespace Component
{
    Ram::Ram() : Component()
    {
        capacity = 0;
        frequency = 0;
        slats = 0;
        type = nullptr;
    }
    Ram::Ram(const Ram& component) : Component(component)
    {
        capacity = component.capacity;
        frequency = component.frequency;
        slats = component.slats;
        type = component.type;
    }
    Ram::Ram(int articul, QString name, int cost, Type type, int amount, int capacity, int frequency, int slats, QString memoryType) : Component(articul, name, cost, type, amount)
    {
        this->capacity = capacity;
        this->frequency = frequency;
        this->slats = slats;
        this->type = memoryType;
    }
    int Ram::GetCapacity() const
    {
        return capacity;
    }
    int Ram::GetFrequency() const
    {
        return frequency;
    }
    int Ram::GetSlats() const
    {
        return slats;
    }
    QString Ram::GetType() const
    {
        return type;
    }
}

