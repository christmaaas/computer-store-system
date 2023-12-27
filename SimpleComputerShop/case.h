#ifndef CASE_H
#define CASE_H

#include "component.h"

#define CASES_FILE "./holders/cases.txt"

#define CASE_COLOR 3
#define CASE_MATERIAL 4
#define CASE_WINDOW 5
#define CASE_MB_FORM_FACTOR 6
#define CASE_COST 7
#define CASE_AMOUNT 8

namespace Component
{
    class Case : public Component
    {
    private:
        QString color;
        QString material;
        QString window;
        QString formFactor;

    public:
        Case();
        Case(const Case&);
        Case(int articul, QString name, int cost, Type type, int amount, QString color, QString material, QString window, QString form_factor);

        ~Case() {};

        QString GetColor() const;
        QString GetMaterial() const;
        QString GetWindow() const;
        QString GetFormFactor() const;
    };
}

#endif // CASE_H
