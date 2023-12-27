#ifndef ROM_H
#define ROM_H

#include "component.h"

#define ROM_FILE "./holders/rom.txt"

#define ROM_TYPE 3
#define ROM_CAPACITY 4
#define ROM_SPEED 5
#define ROM_SLOT 6
#define ROM_COST 7
#define ROM_AMOUNT 8

namespace Component
{
    class Rom : public Component
    {
    private:
        int capacity;
        int speed;

        QString slot;
        QString type;

    public:
        Rom();
        Rom(const Rom&);
        Rom(int articul, QString name, int cost, Type, int amount, int capacity, int speed, QString slot, QString type);

        ~Rom() {};

        int GetCapacity() const;
        int GetSpeed() const;
        QString GetSlot() const;
        QString GetType() const;
    };
}

#endif // ROM_H
