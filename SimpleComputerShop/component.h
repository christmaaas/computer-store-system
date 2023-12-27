#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <iostream>
#include <QFile>
#include <QtWidgets>
#include <QHash>
#include <algorithm>
#include <QtGlobal>
#include <QDate>

#define COUNT_OF_COMPONENTS 8

namespace Component
{
    enum Type
    {
        UNKNOWN = 0,
        GPU,
        CPU,
        RAM,
        ROM,
        MOTHERBOARD,
        POWER_UNIT,
        CASE,
        COOLER
    };
    class Component
    {
    private:
        QString name;
        Type type;
        int cost;
        int articul;
        int amount;
    public:
        Component();
        Component(const Component&);
        Component(int, QString, int, Type, int);

        virtual ~Component() {};

        QString GetName() const;
        int GetCost() const;
        Type GetType() const;
        int GetArticul() const;
        int GetAmount() const;
        void SetAmount(int);
    };
}

#endif // COMPONENT_H
