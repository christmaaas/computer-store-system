#include "case.h"

namespace Component
{
    Case::Case() : Component()
    {
        color = nullptr;
        material = nullptr;
        window = nullptr;
        formFactor = nullptr;
    }
    Case::Case(const Case& component) : Component(component)
    {
        color = component.color;
        material = component.material;
        window = component.window;
        formFactor = component.formFactor;
    }
    Case::Case(int articul, QString name, int cost, Type type, int amount, QString color, QString material, QString window, QString formFactor) : Component(articul, name, cost, type, amount)
    {
        this->color = color;
        this->material = material;
        this->window = window;
        this->formFactor = formFactor;
    }
    QString Case::GetColor() const
    {
        return color;
    }
    QString Case::GetMaterial() const
    {
        return material;
    }
    QString Case::GetWindow() const
    {
        return window;
    }
    QString Case::GetFormFactor() const
    {
        return formFactor;
    }
}

