#ifndef COOLER_H
#define COOLER_H

#include "component.h"

#define COOLER_FILE "./holders/cooler.txt"

#define COOLER_SOCKETS 3
#define COOLER_COOLING_TYPE 4
#define COOLER_FORMFACTOR 5
#define COOLER_COOLING_POWER 6
#define COOLER_COST 7
#define COOLER_AMOUNT 8

namespace Component
{
    class Cooler : public Component
    {
    private:
        QString sockets;
        QString coolingType;
        QString formFactor;

        int coolingPower;

    public:
        Cooler();
        Cooler(const Cooler&);
        Cooler(int articul, QString name, int cost, Type type, int amount, QString sockets, QString coolingType, QString formFactor, int coolingPower);

        ~Cooler() {};

        QString GetSockets() const;
        QString GetCoolingType() const;
        QString GetFormFactor() const;
        int GetCoolingPower() const;
    };
}

#endif // COOLER_H
