#ifndef CART_H
#define CART_H

#include "alghoritms.h"

class Cart : public QObject
{
    Q_OBJECT

private:
    int amountOfComponents;
    int totalCost;

    QComboBox* cartFilterComboBox;

    QTableWidget* cartTable;

    QLabel* cartSumLabel;

    QPushButton* sortButton;
    QPushButton* clearCartButton;
    QPushButton* orderButton;

    QList<Component::Component*> cart;

private slots:
    void OnCartItemDoubleClicked(QTableWidgetItem* item);
    void OnAdmitSortButtonClicked(Component::Type type, QRadioButton& sortByAmountLowCheckBox, QRadioButton& sortByAmountHighCheckBox, QRadioButton& sortByPriceMinCheckBox, QRadioButton& sortByPriceMaxCheckBox, QRadioButton& sortByParameter1, QRadioButton& sortByParameter2, QRadioButton& sortByParameter3, QRadioButton& sortByParameter4);

public slots:
    void AddComponent(Component::Component* component, int amountToAdd);
    void AddConfiguration(QList<Component::Component*> configuration);
    void OnClearCartClicked();

    void OnCartFilterChanged(int index);
    void OnSortButtonClicked();

signals:
    void DeletePurchasedComponents(Component::Component* stockComponent, Component::Component* cartComponent);

public:
    Cart();
    ~Cart();

    void DeleteFromCart(Component::Component* component);
    void FillTable(QList<Component::Component*> components);
    void ClearTable();
    int GetTotalCost();
    int GetAmountOfComponents();
    void MakeAnOrder(QList<Component::Component*> stock);
    void CreateTab(QWidget* cartTab, QVBoxLayout* cartLayout, QHBoxLayout* cartButtonsLayout, QVBoxLayout* cartSortLayout);
    QPushButton* GetOrderButton();
    QList<Component::Component*>& GetCart();

};

Component::Component* getObjectByType(Component::Type type, Component::Component* component);
Component::Type getTypeByFilter(QString selectedFilter);
QList<Component::Component*> sortByTypeComponentList(QList<Component::Component*> listToSort, Component::Type type);

#endif // CART_H
