#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include "component.h"

namespace Component
{
    class Motherboard final : public Component
    {
    public:
        enum MotherboardSettings : uint8_t
        {
            Socket = 3,
            Chipset,
            RamSlots,
            MemoryType,
            Formfactor,
            GpuType,
            RomType,
            Cost,
            Amount,
        };

        Motherboard() noexcept = default;
        Motherboard(const Motherboard&) noexcept = default;
        Motherboard(const int article, const QString& name, const int cost, const ComponentType type,
            const int amount, const QString& socket, const QString& chipset, const QString& memoryType,
            const QString& formFactor, const QString& gpuSlot, const QString& romSlot, const int ramSlots) noexcept :
            Component(article, name, cost, type, amount)
        {
            this->socket = socket;
            this->chipset = chipset;
            this->memoryType = memoryType;
            this->formFactor = formFactor;
            this->gpuSlot = gpuSlot;
            this->romSlot = romSlot;
            this->ramSlots = ramSlots;
        }

        ~Motherboard() override = default;

        [[nodiscard]] inline const QString& GetSocket() const noexcept { return socket; }
        [[nodiscard]] inline const QString& GetChipset() const noexcept { return chipset; }
        [[nodiscard]] inline const QString& GetMemoryType() const noexcept { return memoryType; }
        [[nodiscard]] inline const QString& GetFormFactor() const noexcept { return formFactor; }
        [[nodiscard]] inline const QString& GetGpuSlot() const noexcept { return gpuSlot; }
        [[nodiscard]] inline const QString& GetRomSlot() const noexcept { return romSlot; }
        [[nodiscard]] inline int GetRamSlots() const noexcept { return ramSlots; }

    private:
        QString socket;
        QString chipset;
        QString memoryType;
        QString formFactor;
        QString gpuSlot;
        QString romSlot;
        int ramSlots = 0;
    };
}

#endif // MOTHERBOARD_H
