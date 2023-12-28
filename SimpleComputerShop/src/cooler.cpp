#include "cooler.h"

namespace Component
{
    Cooler::Cooler() : Component()
    {
        sockets = 0;
        coolingType = 0;
        formFactor = nullptr;
        coolingPower = 0;
    }
    Cooler::Cooler(const Cooler& component) : Component(component)
    {
        sockets = component.sockets;
        coolingType = component.coolingType;
        formFactor = component.formFactor;
        coolingPower = component.coolingPower;
    }
    Cooler::Cooler(int articul, QString name, int cost, Type type, int amount, QString sockets, QString coolingType, QString formFactor, int coolingPower) : Component(articul, name, cost, type, amount)
    {
        this->sockets = sockets;
        this->coolingType = coolingType;
        this->formFactor = formFactor;
        this->coolingPower = coolingPower;
    }
    QString Cooler::GetSockets() const
    {
        return sockets;
    }
    QString Cooler::GetCoolingType() const
    {
        return coolingType;
    }
    QString Cooler::GetFormFactor() const
    {
        return formFactor;
    }
    int Cooler::GetCoolingPower() const
    {
        return coolingPower;
    }
}
