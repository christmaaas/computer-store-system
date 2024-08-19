#ifndef POWER_UNIT_H
#define POWER_UNIT_H

#include "component.h"

namespace Component
{
    class PowerUnit final : public Component
    {
    public:
        enum PowerUnitSettings : uint8_t
        {
            Power = 3,
            Pins,
            FormFactor,
            Certificate,
            Cost,
            Amount,
        };

        PowerUnit() noexcept = default;
        PowerUnit(const PowerUnit&) noexcept = default;
        PowerUnit(const int article, const QString& name, const int cost, const ComponentType type,
            const int amount, const int power, const int pins, const QString& formFactor,
            const QString& certificate) noexcept
            : Component(article, name, cost, type, amount)
        {
            this->power = power;
            this->pins = pins;
            this->formFactor = formFactor;
            this->certificate = certificate;
        }

        [[nodiscard]] inline int GetPower() const noexcept { return power; }
        [[nodiscard]] inline int GetPins() const noexcept { return pins; }
        [[nodiscard]] inline const QString& GetFormFactor() const noexcept { return formFactor; }
        [[nodiscard]] inline const QString& GetCertificate() const noexcept { return certificate; }

    private:
        int power = 0;
        int pins = 0;
        QString formFactor;
        QString certificate;
    };
}

#endif // POWER_UNIT_H