#include "gpu.h"

namespace Component
{
    Gpu::Gpu() : Component()
    {
        memory = 0;
        frequency = 0;
        pins = 0;
        recommendPower = 0;
        memoryType = nullptr;
        tireType = nullptr;
    }
    Gpu::Gpu(const Gpu& component) : Component(component)
    {
        memory = component.memory;
        frequency = component.frequency;
        pins = component.pins;
        memoryType = component.memoryType;
        tireType = component.tireType;
        recommendPower = component.recommendPower;
    }
    Gpu::Gpu(int articul, QString name, int cost, Type type, int amount, int memory, int frequency, QString memoryType, QString tireType, int pins, int recommendPower) : Component(articul, name, cost, type, amount)
    {
        this->memory = memory;
        this->frequency = frequency;
        this->pins = pins;
        this->recommendPower = recommendPower;

        this->memoryType = memoryType;
        this->tireType = tireType;
    }
    int Gpu::GetMemory() const
    {
        return this->memory;
    }
    QString Gpu::GetMemoryType() const
    {
        return this->memoryType;
    }
    QString Gpu::GetTireType() const
    {
        return this->tireType;
    }
    int Gpu::GetPins() const
    {
        return this->pins;
    }
    int Gpu::GetRecommendPower() const
    {
        return this->recommendPower;
    }
    int Gpu::GetFrequency() const
    {
        return this->frequency;
    }
}
