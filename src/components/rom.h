#ifndef ROM_H
#define ROM_H

#include "component.h"

namespace Component
{
    class Rom final : public Component
    {
    public:
        enum RomSettings : uint8_t
        {
            Type = 3,
            Capacity,
            Speed,
            Slot,
            Cost,
            Amount
        };

        Rom() noexcept = default;
        Rom(const Rom&) noexcept = default;
        Rom(const int article, const QString& name, const int cost, const ComponentType type,
            const int amount, const int capacity, const int speed, const QString& slot,
            const QString& romType) noexcept
            : Component(article, name, cost, type, amount)
        {
            this->capacity = capacity;
            this->speed = speed;
            this->slot = slot;
            this->type = romType;
        }

        [[nodiscard]] inline int GetCapacity() const noexcept { return capacity; }
        [[nodiscard]] inline int GetSpeed() const noexcept { return speed; }
        [[nodiscard]] inline const QString& GetSlot() const noexcept { return slot; }
        [[nodiscard]] inline const QString& GetType() const noexcept { return type; }

    private:
        int capacity = 0;
        int speed = 0;
        QString slot;
        QString type;
    };
}

#endif // ROM_H