#ifndef STOCK_H
#define STOCK_H

#include "alghoritms.h"

#define BUFFER_FILE "./holders/buffer.txt"

#define ID 0
#define TYPE_OF_COMPONENT 1
#define NAME_OF_COMPONENT 2

class Stock : public QObject
{
    Q_OBJECT
private:
    int amountOfComponents;
    int currentItemAmount;

    QDialog* addToCartDialog;

    QLineEdit* enterLineEdit;

    QLineEdit* enterSearchLineEdit;

    QTableWidget* stockTable;
    QTableWidget* tableSearchResult;

    QComboBox* stockFilterComboBox;

    QPushButton* sortButton;
    QPushButton* searchButton;
    QPushButton* infoButton;

    QList<Component::Component*> stock;

    void CreateWindowForAmount();
    void DeletePurchasedComponentsFromFile(Component::Component* stockComponent, int deletedAmount);

private slots:
    void OnStockItemDoubleClicked(QTableWidgetItem* item);
    void OnEnterButtonClicked();
    void OnAdmitSortButtonClicked(Component::Type type, QRadioButton& sortByAmountLowCheckBox, QRadioButton& sortByAmountHighCheckBox, QRadioButton& sortByPriceMinCheckBox, QRadioButton& sortByPriceMaxCheckBox, QRadioButton& sortByParameter1, QRadioButton& sortByParameter2, QRadioButton& sortByParameter3, QRadioButton& sortByParameter4);

signals:
    void AddToCart(Component::Component* component, int amountToAdd);

public slots:
    void OnSearchAtStockClicked();
    void OnStockFilterChanged(int index);
    void OnSortButtonClicked();
    void OnStockInfoButtonClicked();
    void DeletePurchasedComponentsFromList(Component::Component* stockComponent, Component::Component* cartComponent);

public:
    Stock();
    ~Stock();

    void FillList();
    void FillTable(QTableWidget* table, QList<Component::Component*> components);
    void FillSearchTable();
    int GetAmountOfComponents();
    void CreateTab(QWidget* stockTab, QVBoxLayout* stockLayout, QHBoxLayout* stockButtonLayout, QVBoxLayout* stockSortLayout);
    QList<Component::Component*>& GetStock();
    QTableWidget* GetStockTable();
};

int getAmountIndexByType(Component::Type type);
QString getHolderByType(Component::Type type);
void createAndPopulateFile();
QList<Component::Component*> sortByTypeComponentList(QList<Component::Component*> listToSort, Component::Type type);

#endif // STOCK_H
