#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "alghoritms.h"

class Configurator : public QObject
{
    Q_OBJECT
private:
    int currentSum;

    QTableWidget* selectTable;

    QPushButton* cpuButton;
    QPushButton* motherboardButton;
    QPushButton* gpuButton;
    QPushButton* ramButton;
    QPushButton* romButton;
    QPushButton* coolerButton;
    QPushButton* powerUnitButton;
    QPushButton* caseButton;
    QPushButton* clearButton;
    QPushButton* confirmButton;

    QLabel* cpuLabel;
    QLabel* motherboardLabel;
    QLabel* gpuLabel;
    QLabel* ramLabel;
    QLabel* romLabel;
    QLabel* coolerLabel;
    QLabel* powerUnitLabel;
    QLabel* caseLabel;
    QLabel* selectedCpuLabel;
    QLabel* selectedMotherboardLabel;
    QLabel* selectedGpuLabel;
    QLabel* selectedRamLabel;
    QLabel* selectedRomLabel;
    QLabel* selectedCoolerLabel;
    QLabel* selectedPowerUnitLabel;
    QLabel* selectedCaseLabel;
    QLabel* configuratorSelectLabel;
    QLabel* configuratorSelectedLabel;
    QLabel* sumLabel;

    QList<Component::Component*> commonList;
    QList<Component::Component*> stock;

private slots:
    void OnSelectTableItemDoubledclicked(QTableWidgetItem* item);

public slots:
    void OnClearConfigurationClicked();
    void OnDoneButtonClicked();

signals:
    void AddConfigurationToCart(QList<Component::Component*> configuration);

public:
    Configurator();
    ~Configurator();

    QList<Component::Component*> SortSelectedType(QList<Component::Component*> currentList, Component::Type selectedType);
    void FillTable(QList<Component::Component*> currentList);
    void CreateDialogForSelect(QList<Component::Component*> stock, QList<Component::Component*> currentList, Component::Type selectedType);
    void ClearConfiguration();
    Component::Component* GetByType(Component::Type type);
    bool IsInCommonListDelete(Component::Type type);
    bool IsInCommonList(Component::Type type);
    bool CheckForComponentInCommonList(Component::Type type);
    void CreateTab(QWidget* configuratorTab, QVBoxLayout* verticalConfiguratorLayout1, QVBoxLayout* verticalConfiguratorLayout2, QHBoxLayout* horizontalConfiguratorLayout);
    QPushButton* GetCpuButton() const;
    QPushButton* GetMotherboardButton() const;
    QPushButton* GetGpuButton() const;
    QPushButton* GetRamButton() const;
    QPushButton* GetRomButton() const;
    QPushButton* GetCoolerButton() const;
    QPushButton* GetPowerUnitButton() const;
    QPushButton* GetCaseButton() const;
    QPushButton* GetClearButton() const;
    QPushButton* GetConfirmButton() const;
};

bool checkForComponentInCommonList(Component::Type type);
Component::Component* getByType(QList<Component::Component*> commonList);

#endif // CONFIGURATOR_H
