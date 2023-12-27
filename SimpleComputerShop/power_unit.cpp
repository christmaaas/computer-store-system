#include "power_unit.h"

namespace Component
{
    Powerunit::Powerunit() : Component()
    {
        power = 0;
        pins = 0;
        formFactor = nullptr;
        sertificate = nullptr;
    }
    Powerunit::Powerunit(const Powerunit& component) : Component(component)
    {
        power = component.power;
        pins = component.pins;
        formFactor = component.formFactor;
        sertificate = component.sertificate;
    }
    Powerunit::Powerunit(int articul, QString name, int cost, Type type, int amount, int power, int pins, QString formFactor, QString sertificate) : Component(articul, name, cost, type, amount)
    {
        this->power = power;
        this->pins = pins;
        this->formFactor = formFactor;
        this->sertificate = sertificate;
    }
    int Powerunit::GetPower() const
    {
        return power;
    }
    int Powerunit::GetPins() const
    {
        return pins;
    }
    QString Powerunit::GetFormFactor() const
    {
        return formFactor;
    }
    QString Powerunit::GetSertificate() const
    {
        return sertificate;
    }
}

