#include "motherboard.h"

namespace Component
{
    Motherboard::Motherboard() : Component()
    {
        socket = nullptr;
        chipset = nullptr;
        memoryType = nullptr;
        formFactor = nullptr;
        gpuSlot = nullptr;
        romSlot = nullptr;
        ramSlots = 0;
    }
    Motherboard::Motherboard(const Motherboard& component) : Component(component)
    {
        socket = component.socket;
        chipset = component.chipset;
        memoryType = component.memoryType;
        formFactor = component.formFactor;
        gpuSlot = component.gpuSlot;
        romSlot = component.romSlot;
        ramSlots = component.ramSlots;
    }
    Motherboard::Motherboard(int articul, QString name, int cost, Type type, int amount, QString socket, QString chipset, QString memoryType, QString formFactor, QString gpuSlot, QString romSlot, int ramSlots) : Component(articul, name, cost, type, amount)
    {
        this->socket = socket;
        this->chipset = chipset;
        this->memoryType = memoryType;
        this->formFactor = formFactor;
        this->gpuSlot = gpuSlot;
        this->romSlot = romSlot;
        this->ramSlots = ramSlots;
    }
    QString Motherboard::GetSocket() const
    {
        return socket;
    }
    QString Motherboard::GetChipset() const
    {
        return chipset;
    }
    QString Motherboard::GetMemoryType() const
    {
        return memoryType;
    }
    QString Motherboard::GetFormFactor() const
    {
        return formFactor;
    }
    QString Motherboard::GetGpuSlot() const
    {
        return gpuSlot;
    }
    QString Motherboard::GetRomSlot() const
    {
        return romSlot;
    }
    int Motherboard::GetRamSlots() const
    {
        return ramSlots;
    }
}

