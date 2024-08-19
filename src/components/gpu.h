#ifndef GPU_H
#define GPU_H

#include "component.h"

namespace Component
{
    class Gpu final : public Component
    {
    public:
        enum GpuSettings : uint8_t
        {
            Memory = 3,
            MemoryType,
            Frequency,
            Slot,
            Pins,
            Power,
            Cost,
            Amount,
        };

        Gpu() noexcept = default;
        Gpu(const Gpu&) noexcept = default;
        Gpu(const int article, const QString& name, const int cost, const ComponentType type,
            const int amount, const int memory, const int frequency, const QString& memoryType,
            const QString& tireType, const int pins, const int recommendPower) noexcept :
            Component(article, name, cost, type, amount)
        {
            this->memory = memory;
            this->frequency = frequency;
            this->pins = pins;
            this->recommendPower = recommendPower;
            this->memoryType = memoryType;
            this->tireType = tireType;
        }

        ~Gpu() override = default;

        [[nodiscard]] inline const QString& GetMemoryType() const noexcept { return memoryType; }
        [[nodiscard]] inline const QString& GetTireType() const noexcept { return tireType; }
        [[nodiscard]] inline int GetPins() const noexcept { return pins; }
        [[nodiscard]] inline int GetMemory() const noexcept { return memory; }
        [[nodiscard]] inline int GetFrequency() const noexcept { return frequency; }
        [[nodiscard]] inline int GetRecommendPower() const noexcept { recommendPower; }

    private:
        int memory = 0;
        int frequency = 0;
        int pins = 0;
        int recommendPower = 0;
        QString memoryType;
        QString tireType;
    };
}

#endif // GPU_H
