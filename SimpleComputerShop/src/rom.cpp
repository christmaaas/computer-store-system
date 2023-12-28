#include "rom.h"

namespace Component
{
    Rom::Rom() : Component()
    {
        capacity = 0;
        speed = 0;
        slot = nullptr;
        type = nullptr;
    }
    Rom::Rom(const Rom& component) : Component(component)
    {
        capacity = component.capacity;
        speed = component.speed;
        slot = component.slot;
        type = component.type;
    }
    Rom::Rom(int articul, QString name, int cost, Type type, int amount, int capacity, int speed, QString slot, QString typeOfDevice) : Component(articul, name, cost, type, amount)
    {
        this->capacity = capacity;
        this->speed = speed;
        this->slot = slot;
        this->type = typeOfDevice;
    }
    int Rom::GetCapacity() const
    {
        return capacity;
    }
    int Rom::GetSpeed() const
    {
        return speed;
    }
    QString Rom::GetSlot() const
    {
        return slot;
    }
    QString Rom::GetType() const
    {
        return type;
    }
}

