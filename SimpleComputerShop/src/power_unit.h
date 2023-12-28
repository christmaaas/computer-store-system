#ifndef POWER_UNIT_H
#define POWER_UNIT_H

#include "component.h"

#define POWER_UNIT_FILE "./holders/power_units.txt"

#define POWER_UNIT_POWER 3
#define POWER_UNIT_PINS 4
#define POWER_UNIT_FORM_FACTOR 5
#define POWER_UNIT_SERTIFICATE 6
#define POWER_UNIT_COST 7
#define POWER_UNIT_AMOUNT 8

namespace Component
{
    class Powerunit : public Component
    {
    private:
        int power;
        int pins;

        QString formFactor;
        QString sertificate;

    public:
        Powerunit();
        Powerunit(const Powerunit&);
        Powerunit(int articul, QString name, int cost, Type type, int amount, int power, int pins, QString formFactor, QString sertificate);

        ~Powerunit() {};

        int GetPower() const;
        int GetPins() const;
        QString GetFormFactor() const;
        QString GetSertificate() const;
    };
}

#endif // POWER_UNIT_H
