#include "cart.h"

void Cart::DeleteFromCart(Component::Component* component)
{
    amountOfComponents -= component->GetAmount();
    totalCost -= (component->GetCost() * component->GetAmount());

    cart.removeOne(component);
    delete component;

    FillTable(cart);

    QMessageBox::information(nullptr, "Выбранный товар", "Товар удален из корзины");
}

void Cart::AddComponent(Component::Component* component, int amountToAdd)
{
    bool isInCart = false;

    for(Component::Component* cart_component : cart)
    {
        if(cart_component->GetArticul() == component->GetArticul())
        {
            int total_amount = cart_component->GetAmount() + amountToAdd;
            if(cart_component->GetAmount() == component->GetAmount())
            {
                QMessageBox::information(nullptr, "Выбранный товар", "Достигнуто максимальное количество данного товара");
                isInCart = true;
                break;
            }
            else if(total_amount > component->GetAmount())
            {
                QMessageBox::information(nullptr, "Выбранный товар", "Нельзя добавить столько товара");
                isInCart = true;
                break;
            }
            else
            {
                cart_component->SetAmount(total_amount);
                totalCost += (component->GetCost() * amountToAdd);
                FillTable(cart);
                isInCart = true;
                QMessageBox::information(nullptr, "Добавление в корзину", "Товар добавлен в корзину");
                break;
            }
        }
    }
    if(!isInCart)
    {
        Component::Component* copy = getObjectByType(component);
        copy->SetAmount(amountToAdd);

        cart.append(copy);
        amountOfComponents += amountToAdd;
        totalCost += (component->GetCost() * amountToAdd);
        FillTable(cart);
        QMessageBox::information(nullptr, "Добавление в корзину", "Товар добавлен в корзину");
    }
}

void Cart::FillTable(QList<Component::Component*> components)
{
    disconnect(cartTable, &QTableWidget::itemDoubleClicked, this, &Cart::OnCartItemDoubleClicked);

    cartTable->clearContents();
    cartTable->setRowCount(0); // Убираем все строки

    int row = 0;
    for (const Component::Component* component : components) {
        cartTable->insertRow(row);
        cartTable->setItem(row, 0, new QTableWidgetItem(QString::number(component->GetArticul())));
        cartTable->setItem(row, 1, new QTableWidgetItem(component->GetName()));
        cartTable->setItem(row, 2, new QTableWidgetItem(component->GetName()));
        cartTable->setItem(row, 4, new QTableWidgetItem(QString::number(component->GetCost()) + "$"));
        cartTable->setItem(row, 5, new QTableWidgetItem(QString::number(component->GetAmount())));

        Component::Type type = component->GetType();

        switch(type)
        {
            case Component::GPU:
            {
                const Component::Gpu* gpu = dynamic_cast<const Component::Gpu*>(component);
                if (gpu)
                {
                    cartTable->setItem(row, 1, new QTableWidgetItem("Видеокарта"));
                    cartTable->setItem(row, 3, new QTableWidgetItem(QString::number(gpu->GetMemory()) + "ГБ/" + gpu->GetMemoryType() + "/" + QString::number(gpu->GetFrequency()) + "МГц/" + gpu->GetTireType()));
                }
                break;
            }
            case Component::CPU:
            {
                const Component::Cpu* cpu = dynamic_cast<const Component::Cpu*>(component);
                if (cpu)
                {
                    cartTable->setItem(row, 1, new QTableWidgetItem("Процессор"));
                    cartTable->setItem(row, 3, new QTableWidgetItem(QString::number(cpu->GetCores()) + " ядер/" + QString::number(cpu->GetStreams()) + " потоков/" + cpu->GetSocket() + "/" + cpu->GetArchitecture()));
                }
                break;
            }
            case Component::RAM:
            {
                const Component::Ram* ram = dynamic_cast<const Component::Ram*>(component);
                if (ram)
                {
                    cartTable->setItem(row, 1, new QTableWidgetItem("Оперативная память"));
                    cartTable->setItem(row, 3, new QTableWidgetItem(QString::number(ram->GetCapacity()) + "ГБ/" + ram->GetType() + "/" + QString::number(ram->GetFrequency()) + "ГГц/" + QString::number(ram->GetSlats()) + " планки"));
                }
                break;
            }
            case Component::ROM:
            {
                const Component::Rom* storagedevice = dynamic_cast<const Component::Rom*>(component);
                if (storagedevice)
                {
                    cartTable->setItem(row, 1, new QTableWidgetItem("Накопитель"));
                    cartTable->setItem(row, 3, new QTableWidgetItem(storagedevice->GetType() + "/" + QString::number(storagedevice->GetCapacity()) + "МБ/" + QString::number(storagedevice->GetSpeed()) + "МБ/с|" + storagedevice->GetSlot()));
                }
                break;
            }
            case Component::MOTHERBOARD:
            {
                const Component::Motherboard* motherboard = dynamic_cast<const Component::Motherboard*>(component);
                if (motherboard)
                {
                    cartTable->setItem(row, 1, new QTableWidgetItem("Материнская плата"));
                    cartTable->setItem(row, 3, new QTableWidgetItem(motherboard->GetSocket() + "/" + motherboard->GetChipset() + "/" + motherboard->GetMemoryType() + "/" + motherboard->GetFormFactor()));
                }
                break;
            }
            case Component::POWER_UNIT:
            {
                const Component::Powerunit* powerUnit = dynamic_cast<const Component::Powerunit*>(component);
                if (powerUnit)
                {
                    cartTable->setItem(row, 1, new QTableWidgetItem("Блок питания"));
                    cartTable->setItem(row, 3, new QTableWidgetItem(QString::number(powerUnit->GetPower()) + "Вт/" + QString::number(powerUnit->GetPins()) + "pin/" + powerUnit->GetFormFactor() + "/" + powerUnit->GetSertificate()));
                }
                break;
            }
            case Component::CASE:
            {
                const Component::Case* frame = dynamic_cast<const Component::Case*>(component);
                if (frame)
                {
                    cartTable->setItem(row, 1, new QTableWidgetItem("Корпус"));
                    cartTable->setItem(row, 3, new QTableWidgetItem(frame->GetFormFactor() + "/" + frame->GetColor() + "/" + frame->GetWindow() + "/" + frame->GetMaterial()));
                }
                break;
            }
            case Component::COOLER:
            {
                const Component::Cooler* cooler = dynamic_cast<const Component::Cooler*>(component);
                if (cooler)
                {
                    cartTable->setItem(row, 1, new QTableWidgetItem("Охлаждение"));
                    cartTable->setItem(row, 3, new QTableWidgetItem(cooler->GetSockets() + "/" + cooler->GetCoolingType() + "/" + cooler->GetFormFactor() + "/" + QString::number(cooler->GetCoolingPower()) + "Вт"));
                }
                break;
            }
        }

        for(int col = 0; col < cartTable->columnCount(); col++)
        {
            QTableWidgetItem* item = cartTable->item(row, col);
            if (item)
            {
                item->setFlags((item->flags() & ~Qt::ItemIsEditable));
            }
        }

        cartTable->setRowHeight(row, QPaintDevice::PdmHeight);

        row++;
    }

    cartSumLabel->setText("Сумма заказа: " + QString::number(totalCost) + "$");

    connect(cartTable, &QTableWidget::itemDoubleClicked, this, &Cart::OnCartItemDoubleClicked);
}

void Cart::ClearTable()
{
    amountOfComponents = 0;
    totalCost = 0;

    cartTable->clearContents();
    cartTable->setRowCount(0); // Убираем все строки

    for(Component::Component* component : cart)
    {
        cart.removeOne(component);
        delete component;
    }

    cartSumLabel->setText("Сумма заказа: 0$");
}

void Cart::OnClearCartClicked()
{
    if(cart.isEmpty())
        QMessageBox::information(nullptr, "Корзина", "Корзина пуста");
    else
    {
        ClearTable();
        QMessageBox::information(nullptr, "Корзина", "Корзина очищена");
    }
}

Cart::Cart()
{
    amountOfComponents = 0;
    totalCost = 0;

    cartTable = nullptr;

    cartSumLabel = nullptr;

    cartFilterComboBox = nullptr;

    sortButton = nullptr;
    clearCartButton = nullptr;
    orderButton = nullptr;
}

Cart::~Cart()
{
    delete cartTable;
    delete cartSumLabel;
    delete cartFilterComboBox;
    delete sortButton;
    delete clearCartButton;
    delete orderButton;

    for(Component::Component* component : cart)
    {
        cart.removeOne(component);
        delete component;
    }
}

void Cart::OnCartFilterChanged(int index)
{
    if(cart.isEmpty())
        QMessageBox::information(nullptr, "Корзина", "Корзина пуста");
    else
    {
        QString selectedFilter = cartFilterComboBox->currentText();

        Component::Type type = getTypeByFilter(selectedFilter);

        QList<Component::Component*> components = sortByTypeComponentList(cart, type);

        if(!components.isEmpty())
            FillTable(components);
        else if(type == Component::UNKNOWN)
        {
            components = cart;
            FillTable(components);
        }
        else
            QMessageBox::information(nullptr, "Выбранный тип", "Нет комплектующих выбранного типа");
    }
}

void Cart::OnCartItemDoubleClicked(QTableWidgetItem* item)
{
    if(item)
    {
        QString textFromFirstColumn = cartTable->item(item->row(), 0)->text();
        int indvNumber = textFromFirstColumn.toInt();

        Component::Component* component = findComponentByIndvNumber(cart, indvNumber);

        DeleteFromCart(component);
    }
}

void Cart::MakeAnOrder(QList<Component::Component*> stock)
{
    for(Component::Component* cart_component : cart)
    {
        for(Component::Component* stock_component : stock)
        {
            if(cart_component->GetArticul() == stock_component->GetArticul())
                emit DeletePurchasedComponents(stock_component, cart_component);
        }
    }
}

int Cart::GetTotalCost()
{
    return totalCost;
}

int Cart::GetAmountOfComponents()
{
    return amountOfComponents;
}

void Cart::OnSortButtonClicked()
{
    if(cart.isEmpty())
        QMessageBox::information(nullptr, "Корзина", "Корзина пуста");
    else
    {
        QDialog sortDialog;
        sortDialog.setWindowTitle("Настройка сортировки");
        sortDialog.resize(250, 150);

        QVBoxLayout sortLayout(&sortDialog);

        Component::Type type = getTypeByFilter(cartFilterComboBox->currentText());
        QString sortParameter1, sortParameter2, sortParameter3, sortParameter4;

        QRadioButton sortByAmountLowCheckBox("Количество(min)"), sortByAmountHighCheckBox("Количество(max)"), sortByPriceMinCheckBox("Цена(min)"), sortByPriceMaxCheckBox("Цена(max)");
        sortLayout.addWidget(&sortByAmountLowCheckBox);
        sortLayout.addWidget(&sortByAmountHighCheckBox);
        sortLayout.addWidget(&sortByPriceMinCheckBox);
        sortLayout.addWidget(&sortByPriceMaxCheckBox);

        QRadioButton sortByParameter1, sortByParameter2, sortByParameter3, sortByParameter4;

        if (type != Component::Type::UNKNOWN)
        {
            getSortParameters(type, &sortParameter1, &sortParameter2, &sortParameter3, &sortParameter4);

            sortByParameter1.setText(sortParameter1);
            sortByParameter2.setText(sortParameter2);
            sortByParameter3.setText(sortParameter3);
            sortByParameter4.setText(sortParameter4);
            sortLayout.addWidget(&sortByParameter1);
            sortLayout.addWidget(&sortByParameter2);
            sortLayout.addWidget(&sortByParameter3);
            sortLayout.addWidget(&sortByParameter4);
        }

        QPushButton sortButton("Применить сортировку");
        sortLayout.addWidget(&sortButton);
        connect(&sortButton, &QPushButton::clicked, this, [&](){
            OnAdmitSortButtonClicked(type, sortByAmountLowCheckBox, sortByAmountHighCheckBox, sortByPriceMinCheckBox, sortByPriceMaxCheckBox, sortByParameter1, sortByParameter2, sortByParameter3, sortByParameter4);
        });

        sortDialog.exec();
    }
}

void Cart::OnAdmitSortButtonClicked(Component::Type type, QRadioButton& sortByAmountLowCheckBox, QRadioButton& sortByAmountHighCheckBox, QRadioButton& sortByPriceMinCheckBox, QRadioButton& sortByPriceMaxCheckBox, QRadioButton& sortByParameter1, QRadioButton& sortByParameter2, QRadioButton& sortByParameter3, QRadioButton& sortByParameter4)
{
    QList<Component::Component*> result = sortByTypeComponentList(cart, type);

    if(!result.isEmpty())
    {
        sortByType(result, type, sortByAmountLowCheckBox, sortByAmountHighCheckBox, sortByPriceMinCheckBox, sortByPriceMaxCheckBox, sortByParameter1, sortByParameter2, sortByParameter3, sortByParameter4);
        FillTable(result);
    }
    else if(type == Component::UNKNOWN)
    {
        result = cart;
        sortByType(result, type, sortByAmountLowCheckBox, sortByAmountHighCheckBox, sortByPriceMinCheckBox, sortByPriceMaxCheckBox, sortByParameter1, sortByParameter2, sortByParameter3, sortByParameter4);
        FillTable(result);
    }
    else
        QMessageBox::information(nullptr, "Выбранный тип", "Нет комплектующих выбранного типа");
}

void Cart::AddConfiguration(QList<Component::Component*> configuration)
{
    for(Component::Component* configurationComponent : configuration)
    {
        for(Component::Component* cart_component : cart)
        {
            if(cart_component->GetArticul() == configurationComponent->GetArticul() && cart_component->GetAmount() == configurationComponent->GetAmount())
            {
                QMessageBox::information(nullptr, "Корзина", "Конфигурация не может быть добавлена в корзину. В корзине находится максимальное количество выбранных товаров");
                return;
            }
        }
    }
    for(Component::Component* configurationComponent : configuration)
    {
        bool isInCart = false;

        for(Component::Component* cart_component : cart)
        {
            if(cart_component->GetArticul() == configurationComponent->GetArticul())
            {
                cart_component->SetAmount(cart_component->GetAmount() + 1);
                totalCost += configurationComponent->GetCost();
                FillTable(cart);
                isInCart = true;
                break;
            }
        }
        if(!isInCart)
        {
            Component::Component* copy = getObjectByType(configurationComponent);
            copy->SetAmount(1);

            cart.append(copy);
            amountOfComponents += 1;
            totalCost += configurationComponent->GetCost();
            FillTable(cart);
        }
    }
    QMessageBox::information(nullptr, "Корзина", "Конфигурация добавлена в корзину");
}

void Cart::CreateTab(QWidget* cartTab, QVBoxLayout* cartLayout, QHBoxLayout* cartButtonsLayout, QVBoxLayout* cartSortLayout)
{
    cartFilterComboBox = new QComboBox(cartTab);
    cartFilterComboBox->setFont(QFont("Arial", 12));
    cartFilterComboBox->addItem("Тип");
    cartFilterComboBox->addItem("Все");
    cartFilterComboBox->addItem("Видеокарты");
    cartFilterComboBox->addItem("Процессоры");
    cartFilterComboBox->addItem("Материнские платы");
    cartFilterComboBox->addItem("Оперативная память");
    cartFilterComboBox->addItem("Блоки питания");
    cartFilterComboBox->addItem("Накопители");
    cartFilterComboBox->addItem("Корпуса");
    cartFilterComboBox->addItem("Охлаждение");

    cartFilterComboBox->setItemData(0, 0, Qt::UserRole - 1);

    connect(cartFilterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Cart::OnCartFilterChanged);

    cartTable = new QTableWidget(cartTab);
    cartTable->setColumnCount(6);
    cartTable->setHorizontalHeaderLabels({"Артикул", "Тип", "Название", "Характеристики", "Цена", "Количество"});

    cartTable->setColumnWidth(0, 60);
    cartTable->setColumnWidth(1, 200);
    cartTable->setColumnWidth(2, 350);
    cartTable->setColumnWidth(3, 550);
    cartTable->setColumnWidth(4, 100);
    cartTable->setColumnWidth(5, 100);

    cartTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    cartTable->setSelectionMode(QAbstractItemView::SingleSelection);

    sortButton = new QPushButton("Сортировать", cartTab);
    sortButton->setFont(QFont("Arial", 12));
    connect(sortButton, &QPushButton::clicked, this, &Cart::OnSortButtonClicked);

    clearCartButton = new QPushButton("Очистить корзину", cartTab);
    clearCartButton->setFont(QFont("Arial", 12));
    connect(clearCartButton, &QPushButton::clicked, this, &Cart::OnClearCartClicked);

    orderButton = new QPushButton("Оформить заказ", cartTab);
    orderButton->setFont(QFont("Arial", 12));

    cartSumLabel = new QLabel("Сумма заказа: 0$", cartTab);
    cartSumLabel->setFont(QFont("Arial", 12));

    cartLayout = new QVBoxLayout(cartTab);

    cartButtonsLayout = new QHBoxLayout(cartTab);

    cartSortLayout = new QVBoxLayout(cartTab);
    cartSortLayout->addWidget(cartFilterComboBox);
    cartSortLayout->addWidget(sortButton);

    cartButtonsLayout->addLayout(cartSortLayout);
    cartButtonsLayout->addWidget(clearCartButton);
    cartButtonsLayout->addWidget(orderButton);
    cartButtonsLayout->addWidget(cartSumLabel);

    cartLayout->addLayout(cartButtonsLayout);
    cartLayout->addWidget(cartTable);
}

QPushButton* Cart::GetOrderButton()
{
    return orderButton;
}

QList<Component::Component*>& Cart::GetCart()
{
    return cart;
}
