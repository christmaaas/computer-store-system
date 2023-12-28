#include "component.h"

namespace Component
{
    Component::Component()
    {
        articul = 0;
        name = nullptr;
        cost = 0;
        type = UNKNOWN;
        amount = 0;
    }
    Component::Component(const Component& component)
    {
        articul = component.articul;
        name = component.name;
        cost = component.cost;
        type = component.type;
        amount = component.amount;
    }
    Component::Component(int articul, QString name, int cost, Type type, int amount)
    {
        this->articul = articul;
        this->name = name;
        this->cost = cost;
        this->type = type;
        this->amount = amount;
    }
    QString Component::GetName() const
    {
        return this->name;
    }
    int Component::GetCost() const
    {
        return this->cost;
    }
    Type Component::GetType() const
    {
        return this->type;
    }
    int Component::GetArticul() const
    {
        return articul;
    }
    int Component::GetAmount() const
    {
        return amount;
    }
    void Component::SetAmount(int amount)
    {
        this->amount = amount;
    }
}

