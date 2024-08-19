#ifndef COOLER_H
#define COOLER_H

#include "component.h"

namespace Component
{
    class Cooler final : public Component
    {
    public:
        enum CoolerSettings : uint8_t
        {
            Sockets = 3,
            CollingType,
            Formfactor,
            Power,
            Cost,
            Amount,
        };

        Cooler() noexcept = default;
        Cooler(const Cooler&) noexcept = default;
        Cooler(const int article, const QString& name, const int cost,
            const ComponentType type, const int amount, const QString& sockets,
            const QString& coolingType, const QString& formFactor, const int coolingPower) noexcept :
            Component(article, name, cost, type, amount)
        {
            this->sockets = sockets;
            this->coolingType = coolingType;
            this->formFactor = formFactor;
            this->coolingPower = coolingPower;
        }

        ~Cooler() override = default;

        [[nodiscard]] inline const QString& GetSockets() const noexcept { return sockets; }
        [[nodiscard]] inline const QString& GetCoolingType() const noexcept { return coolingType; }
        [[nodiscard]] inline const QString& GetFormFactor() const noexcept { return formFactor; }
        [[nodiscard]] inline int GetCoolingPower() const noexcept { return coolingPower; }

    private:
        QString sockets;
        QString coolingType;
        QString formFactor;
        int coolingPower = 0;
    };
}

#endif // COOLER_H
