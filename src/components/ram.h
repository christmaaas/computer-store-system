#ifndef RAM_H
#define RAM_H

#include "component.h"

namespace Component
{
    class Ram final : public Component
    {
    public:
        enum RamSettings : uint8_t
        {
            Slats = 3,
            Memory,
            Frequency,
            Type,
            Cost,
            Amount
        };

        Ram() noexcept = default;
        Ram(const Ram&) noexcept = default;
        Ram(const int article, const QString& name, const int cost, const ComponentType type,
            const int amount, const int capacity, const int frequency, const int slats,
            const QString& ramType) noexcept
            : Component(article, name, cost, type, amount)
        {
            this->capacity = capacity;
            this->frequency = frequency;
            this->slats = slats;
            this->type = ramType;
        }

        [[nodiscard]] inline int GetCapacity() const noexcept { return capacity; }
        [[nodiscard]] inline int GetFrequency() const noexcept { return frequency; }
        [[nodiscard]] inline int GetSlats() const noexcept { return slats; }
        [[nodiscard]] inline const QString& GetType() const noexcept { return type; }

    private:
        int capacity = 0;
        int frequency = 0;
        int slats = 0;
        QString type;
    };
}

#endif // RAM_H