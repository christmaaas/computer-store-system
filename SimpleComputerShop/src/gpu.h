#ifndef GPU_H
#define GPU_H

#include "component.h"

#define GPU_FILE "./holders/gpu.txt"

#define GPU_MEMORY 3
#define GPU_MEMORY_TYPE 4
#define GPU_FREQUENCY 5
#define GPU_SLOT 6
#define GPU_PINS 7
#define GPU_RECOMMEND_POWER 8
#define GPU_COST 9
#define GPU_AMOUNT 10

namespace Component
{
    class Gpu : public Component
    {
    private:
        int memory;
        int frequency;

        int pins;
        int recommendPower;

        QString memoryType;
        QString tireType;

    public:
        Gpu();
        Gpu(const Gpu&);
        Gpu(int articul, QString name, int cost, Type type, int amount, int memory, int frequency, QString memoryType, QString tireType, int pins, int recommendPower);

        ~Gpu() {};

        QString GetMemoryType() const;
        QString GetTireType() const;
        int GetPins() const;
        int GetMemory() const;
        int GetFrequency() const;
        int GetRecommendPower() const;
    };
}

#endif // GPU_H
