#ifndef RAM_H
#define RAM_H

#include "component.h"

#define RAM_FILE "./holders/ram.txt"

#define RAM_SLATS 3
#define RAM_MEMORY 4
#define RAM_FREQUENCY 5
#define RAM_TYPE 6
#define RAM_COST 7
#define RAM_AMOUNT 8

namespace Component
{
    class Ram : public Component
    {
    private:
        int capacity;
        int frequency;
        int slats;

        QString type;

    public:
        Ram();
        Ram(const Ram&);
        Ram(int articul, QString name, int cost, Type, int amount, int capacity, int frequency, int slats, QString type);

        ~Ram() {};

        int GetCapacity() const;
        int GetFrequency() const;
        int GetSlats() const;
        QString GetType() const;
    };
}

#endif // RAM_H
