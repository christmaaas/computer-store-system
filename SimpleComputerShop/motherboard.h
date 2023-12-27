#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include "component.h"

#define MOTHERBOARD_FILE "./holders/motherboard.txt"

#define MOTHERBOARD_SOCKET 3
#define MOTHERBOARD_CHIPSET 4
#define MOTHERBOARD_RAM_SLOTS 5
#define MOTHERBOARD_MEMORY_TYPE 6
#define MOTHERBOARD_FORM_FACTOR 7
#define MOTHERBOARD_GPU_TYPE 8
#define MOTHERBOARD_ROM_TYPE 9
#define MOTHERBOARD_COST 10
#define MOTHERBOARD_AMOUNT 11

namespace Component
{
    class Motherboard : public Component
    {
    private:
        QString socket;
        QString chipset;
        QString memoryType;
        QString formFactor;
        QString gpuSlot;
        QString romSlot;

        int ramSlots;

    public:
        Motherboard();
        Motherboard(const Motherboard&);
        Motherboard(int articul, QString name, int cost, Type type, int amount, QString socket, QString chipset, QString memoryType, QString formFactor, QString gpuSlot, QString romSlot, int ramSlots);

        ~Motherboard() {};

        QString GetSocket() const;
        QString GetChipset() const;
        QString GetMemoryType() const;
        QString GetFormFactor() const;
        QString GetGpuSlot() const;
        QString GetRomSlot() const;
        int GetRamSlots() const;
    };
}

#endif // MOTHERBOARD_H
