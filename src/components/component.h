#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>

namespace Component
{
    enum class ComponentType : uint8_t
    {
        Unknown = 0,
        Gpu,
        Cpu,
        Ram,
        Rom,
        Motherboard,
        PowerUnit,
        Case,
        Cooler
    };

    class Component
    {
    public:
        Component() noexcept = default;
        Component(const Component&) noexcept = default;
        Component(const int article, const QString& name, const int cost,
            const ComponentType type, const int amount) noexcept
        {
            this->article = article;
            this->name = name;
            this->cost = cost;
            this->type = type;
            this->amount = amount;
        }

        virtual ~Component() = default;

        [[nodiscard]] inline const QString& GetName() const noexcept { return name; }
        [[nodiscard]] inline ComponentType GetType() const noexcept { return type; }
        [[nodiscard]] inline int GetCost() const noexcept { return cost; }
        [[nodiscard]] inline int GetArticle() const noexcept { return article; }
        [[nodiscard]] inline int GetAmount() const noexcept { return amount; }

        inline void SetAmount(const int amount) noexcept { this->amount = amount; }

    public:
        static constexpr uint8_t totalComponentsCount = 8u;

    private:
        QString name;
        ComponentType type = ComponentType::Unknown;
        int cost = 0;
        int article = 0;
        int amount = 0;
    };
}
#endif // COMPONENT_H
