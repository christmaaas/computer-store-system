#ifndef CASE_H
#define CASE_H

#include "component.h"

namespace Component
{
    class Case final : public Component
    {
    public:
        enum CaseSettings : uint8_t
        {
            Color = 3,
            Material,
            Window,
            Formfactor,
            Cost,
            Amount,
        };

        Case() noexcept = default;
        Case(const Case&) noexcept = default;
        Case(const int article, const QString& name, const int cost,
            const ComponentType type, const int amount, const QString& color,
            const QString& material, const QString& window, const QString& formfactor) noexcept :
            Component(article, name, cost, type, amount)
        {
            this->color = color;
            this->material = material;
            this->window = window;
            this->formfactor = formfactor;
        }

        ~Case() override = default;

        [[nodiscard]] inline const QString& GetColor() const noexcept { return color; }
        [[nodiscard]] inline const QString& GetMaterial() const noexcept { return material; }
        [[nodiscard]] inline const QString& GetWindow() const noexcept { return window; }
        [[nodiscard]] inline const QString& GetFormFactor() const noexcept { return formfactor; }

    private:
        QString color;
        QString material;
        QString window;
        QString formfactor;
    };
}
#endif // CASE_H
