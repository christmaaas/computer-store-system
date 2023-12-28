#include "stock.h"

void Stock::OnEnterButtonClicked()
{
    QString enteredAmount = enterLineEdit->text();

    if(enteredAmount.toInt() > currentItemAmount || enteredAmount.toInt() < 1)
        QMessageBox::warning(nullptr, "Ошибка", "Некорректные данные");
    else
    {
        currentItemAmount = enteredAmount.toInt();
        addToCartDialog->accept();
    }
}

void Stock::CreateWindowForAmount()
{
    addToCartDialog = new QDialog();
    addToCartDialog->setWindowTitle("Добавление в корзину");

    addToCartDialog->resize(300, 100);

    QVBoxLayout* layout = new QVBoxLayout;

    QLabel* titleLabel = new QLabel("Введите количество товара для добавления");
    titleLabel->setFont(QFont("Arial", 12));

    enterLineEdit = new QLineEdit;
    enterLineEdit->setPlaceholderText("Ввод:");
    enterLineEdit->setFont(QFont("Arial", 12));

    QPushButton* enterButton = new QPushButton("Принять");
    enterButton->setFont(QFont("Arial", 12));

    layout->addWidget(titleLabel);
    layout->addWidget(enterLineEdit);
    layout->addWidget(enterButton);

    addToCartDialog->setLayout(layout);

    connect(enterButton, &QPushButton::clicked, this, &Stock::OnEnterButtonClicked);

    addToCartDialog->exec();

    delete titleLabel;
    delete enterButton;
    delete layout;
}

void Stock::OnStockItemDoubleClicked(QTableWidgetItem* item)
{
    if (item)
    {
        QString textFromFirstColumn = stockTable->item(item->row(), 0)->text();
        int indvNumber = textFromFirstColumn.toInt();

        QString textFromLastColumn = stockTable->item(item->row(), 5)->text();
        currentItemAmount = textFromLastColumn.toInt();

        Component::Component* component = findComponentByIndvNumber(stock, indvNumber);

        if(currentItemAmount != 1)
        {
            CreateWindowForAmount();

            if(addToCartDialog->result() != QDialog::Rejected)
                emit AddToCart(component, currentItemAmount);

            delete enterLineEdit;
            enterLineEdit = nullptr;

            delete addToCartDialog;
            addToCartDialog = nullptr;
        }
        else
            emit AddToCart(component, 1);
    }
}

void Stock::FillList()
{
    createAndPopulateFile();

    QFile file(BUFFER_FILE);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString str = in.readLine();
        QStringList substrings = str.split(";");

        Component::Type type = static_cast<Component::Type>(substrings[TYPE_OF_COMPONENT].toInt());

        switch(type)
        {
        case Component::Type::GPU:
        {
            Component::Gpu* gpu = new Component::Gpu(substrings[ID].toInt(), substrings[NAME_OF_COMPONENT], substrings[GPU_COST].toInt(), type, substrings[GPU_AMOUNT].toInt(), substrings[GPU_MEMORY].toInt(), substrings[GPU_FREQUENCY].toInt(), substrings[GPU_MEMORY_TYPE], substrings[GPU_SLOT], substrings[GPU_PINS].toInt(), substrings[GPU_RECOMMEND_POWER].toInt());
            amountOfComponents += gpu->GetAmount();
            stock.append(gpu);
            break;
        }
        case Component::Type::CPU:
        {
            Component::Cpu* cpu = new Component::Cpu(substrings[ID].toInt(), substrings[NAME_OF_COMPONENT], substrings[CPU_COST].toInt(), type, substrings[CPU_AMOUNT].toInt(), substrings[CPU_CORES].toInt(), substrings[CPU_STREAMS].toInt(), substrings[CPU_SOCKET], substrings[CPU_ARCHITECTURE], static_cast<CPU::IntegratedGpu>(substrings[CPU_INTEGRATED_GPU].toInt()));
            amountOfComponents += cpu->GetAmount();
            stock.append(cpu);
            break;
        }
        case Component::Type::RAM:
        {
            Component::Ram* ram = new Component::Ram(substrings[ID].toInt(), substrings[NAME_OF_COMPONENT], substrings[RAM_COST].toInt(), type, substrings[RAM_AMOUNT].toInt(), substrings[RAM_MEMORY].toInt(), substrings[RAM_FREQUENCY].toInt(), substrings[RAM_SLATS].toInt(), substrings[RAM_TYPE]);
            amountOfComponents += ram->GetAmount();
            stock.append(ram);
            break;
        }
        case Component::Type::ROM:
        {
            Component::Rom* rom = new Component::Rom(substrings[ID].toInt(), substrings[NAME_OF_COMPONENT], substrings[ROM_COST].toInt(), type, substrings[ROM_AMOUNT].toInt(), substrings[ROM_CAPACITY].toInt(), substrings[ROM_SPEED].toInt(), substrings[ROM_SLOT], substrings[ROM_TYPE]);
            amountOfComponents += rom->GetAmount();
            stock.append(rom);
            break;
        }
        case Component::Type::MOTHERBOARD:
        {
            Component::Motherboard* motherboard = new Component::Motherboard(substrings[ID].toInt(), substrings[NAME_OF_COMPONENT], substrings[MOTHERBOARD_COST].toInt(), type, substrings[MOTHERBOARD_AMOUNT].toInt(), substrings[MOTHERBOARD_SOCKET], substrings[MOTHERBOARD_CHIPSET], substrings[MOTHERBOARD_MEMORY_TYPE], substrings[MOTHERBOARD_FORM_FACTOR], substrings[MOTHERBOARD_GPU_TYPE], substrings[MOTHERBOARD_ROM_TYPE], substrings[MOTHERBOARD_RAM_SLOTS].toInt());
            amountOfComponents += motherboard->GetAmount();
            stock.append(motherboard);
            break;
        }
        case Component::Type::POWER_UNIT:
        {
            Component::Powerunit* power_unit = new Component::Powerunit(substrings[ID].toInt(), substrings[NAME_OF_COMPONENT], substrings[POWER_UNIT_COST].toInt(), type, substrings[POWER_UNIT_AMOUNT].toInt(), substrings[POWER_UNIT_POWER].toInt(), substrings[POWER_UNIT_PINS].toInt(), substrings[POWER_UNIT_FORM_FACTOR], substrings[POWER_UNIT_SERTIFICATE]);
            amountOfComponents += power_unit->GetAmount();
            stock.append(power_unit);
            break;
        }
        case Component::Type::CASE:
        {
            Component::Case* frame = new Component::Case(substrings[ID].toInt(), substrings[NAME_OF_COMPONENT], substrings[CASE_COST].toInt(), type, substrings[CASE_AMOUNT].toInt(), substrings[CASE_COLOR], substrings[CASE_MATERIAL], substrings[CASE_WINDOW], substrings[CASE_MB_FORM_FACTOR]);
            amountOfComponents += frame->GetAmount();
            stock.append(frame);
            break;
        }
        case Component::Type::COOLER:
        {
            Component::Cooler* cooler = new Component::Cooler(substrings[ID].toInt(), substrings[NAME_OF_COMPONENT], substrings[COOLER_COST].toInt(), type, substrings[COOLER_AMOUNT].toInt(), substrings[COOLER_SOCKETS], substrings[COOLER_COOLING_TYPE], substrings[COOLER_FORMFACTOR], substrings[COOLER_COOLING_POWER].toInt());
            amountOfComponents += cooler->GetAmount();
            stock.append(cooler);
            break;
        }
        default:
            break;
        }
    }

    file.close();
}

void Stock::FillTable(QTableWidget* table, QList<Component::Component*> components)
{
    disconnect(table, &QTableWidget::itemDoubleClicked, this, &Stock::OnStockItemDoubleClicked);

    table->clearContents();
    table->setRowCount(0);

    int row = 0;
    for (const Component::Component* component : components) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(component->GetArticul())));
        table->setItem(row, 2, new QTableWidgetItem(component->GetName()));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(component->GetCost()) + "$"));
        table->setItem(row, 5, new QTableWidgetItem(QString::number(component->GetAmount())));

        Component::Type type = component->GetType();

        switch(type)
        {
            case Component::GPU:
            {
                const Component::Gpu* gpu = dynamic_cast<const Component::Gpu*>(component);
                if (gpu)
                {
                    table->setItem(row, 1, new QTableWidgetItem("Видеокарта"));
                    table->setItem(row, 3, new QTableWidgetItem(QString::number(gpu->GetMemory()) + "ГБ/" + gpu->GetMemoryType() + "/" + QString::number(gpu->GetFrequency()) + "МГц/" + gpu->GetTireType()));
                }
                break;
            }
            case Component::CPU:
            {
                const Component::Cpu* cpu = dynamic_cast<const Component::Cpu*>(component);
                if (cpu)
                {
                    table->setItem(row, 1, new QTableWidgetItem("Процессор"));
                    table->setItem(row, 3, new QTableWidgetItem(QString::number(cpu->GetCores()) + " ядер/" + QString::number(cpu->GetStreams()) + " потоков/" + cpu->GetSocket() + "/" + cpu->GetArchitecture()));
                }
                break;
            }
            case Component::RAM:
            {
                const Component::Ram* ram = dynamic_cast<const Component::Ram*>(component);
                if (ram)
                {
                    table->setItem(row, 1, new QTableWidgetItem("Оперативная память"));
                    table->setItem(row, 3, new QTableWidgetItem(QString::number(ram->GetCapacity()) + "ГБ/" + ram->GetType() + "/" + QString::number(ram->GetFrequency()) + "ГГц/" + QString::number(ram->GetSlats()) + " планки"));
                }
                break;
            }
            case Component::ROM:
            {
                const Component::Rom* rom = dynamic_cast<const Component::Rom*>(component);
                if (rom)
                {
                    table->setItem(row, 1, new QTableWidgetItem("Накопитель"));
                    table->setItem(row, 3, new QTableWidgetItem(rom->GetType() + "/" + QString::number(rom->GetCapacity()) + "МБ/" + QString::number(rom->GetSpeed()) + "МБ/с|" + rom->GetSlot()));
                }
                break;
            }
            case Component::MOTHERBOARD:
            {
                const Component::Motherboard* motherboard = dynamic_cast<const Component::Motherboard*>(component);
                if (motherboard)
                {
                    table->setItem(row, 1, new QTableWidgetItem("Материнская плата"));
                    table->setItem(row, 3, new QTableWidgetItem(motherboard->GetSocket() + "/" + motherboard->GetChipset() + "/" + motherboard->GetMemoryType() + "/" + motherboard->GetFormFactor()));
                }
                break;
            }
            case Component::POWER_UNIT:
            {
                const Component::Powerunit* power_unit = dynamic_cast<const Component::Powerunit*>(component);
                if (power_unit)
                {
                    table->setItem(row, 1, new QTableWidgetItem("Блок питания"));
                    table->setItem(row, 3, new QTableWidgetItem(QString::number(power_unit->GetPower()) + "Вт/" + QString::number(power_unit->GetPins()) + "pin/" + power_unit->GetFormFactor() + "/" + power_unit->GetSertificate()));
                }
                break;
            }
            case Component::CASE:
            {
                const Component::Case* frame = dynamic_cast<const Component::Case*>(component);
                if (frame)
                {
                    table->setItem(row, 1, new QTableWidgetItem("Корпус"));
                    table->setItem(row, 3, new QTableWidgetItem(frame->GetFormFactor() + "/" + frame->GetColor() + "/" + frame->GetWindow() + "/" + frame->GetMaterial()));
                }
                break;
            }
            case Component::COOLER:
            {
                const Component::Cooler* cooler = dynamic_cast<const Component::Cooler*>(component);
                if (cooler)
                {
                    table->setItem(row, 1, new QTableWidgetItem("Охлаждение"));
                    table->setItem(row, 3, new QTableWidgetItem(cooler->GetSockets() + "/" + cooler->GetCoolingType() + "/" + cooler->GetFormFactor() + "/" + QString::number(cooler->GetCoolingPower()) + "Вт"));
                }
                break;
            }
            case Component::UNKNOWN:
                break;
            }

        for(int col = 0; col < table->columnCount(); col++)
        {
            QTableWidgetItem* item = table->item(row, col);

            if (item)
                item->setFlags((item->flags() & ~Qt::ItemIsEditable));
        }

        table->setRowHeight(row, QPaintDevice::PdmHeightMM);

        row++;
    }

    connect(table, &QTableWidget::itemDoubleClicked, this, &Stock::OnStockItemDoubleClicked);
}

Stock::Stock()
{
    amountOfComponents = 0;
    currentItemAmount = 0;

    stockTable = nullptr;

    enterLineEdit = nullptr;
    addToCartDialog = nullptr;

    stockFilterComboBox = nullptr;
    sortButton = nullptr;

    searchButton = nullptr;

    infoButton = nullptr;

    enterSearchLineEdit = nullptr;
    tableSearchResult = nullptr;
}

Stock::~Stock()
{
    delete stockTable;
    delete enterLineEdit;
    delete addToCartDialog;
    delete stockFilterComboBox;
    delete sortButton;
    delete searchButton;
    delete infoButton;
    delete enterSearchLineEdit;
    delete tableSearchResult;

    for(Component::Component* component : stock)
    {
        stock.removeOne(component);
        delete component;
    }
}

int Stock::GetAmountOfComponents()
{
    return amountOfComponents;
}

void Stock::FillSearchTable()
{
    QList<Component::Component*> searchResultList;

    if(!enterSearchLineEdit->text().isEmpty())
    {
        for (Component::Component* component : stock)
        {
            QString articul = QString::number(component->GetArticul());
            QString name = component->GetName();
            QString type = getTextType(component->GetType());

            if(articul.contains(enterSearchLineEdit->text()))
            {
                searchResultList.append(component);
            }
            else if(name.contains(enterSearchLineEdit->text()))
            {
                searchResultList.append(component);
            }
            else if(type.contains(enterSearchLineEdit->text()))
            {
                searchResultList.append(component);
            }
        }
    }

    if(searchResultList.isEmpty())
        QMessageBox::information(nullptr, "Поиск", "По данному запросу ничего не найдено");
    else
        FillTable(tableSearchResult, searchResultList);
}

void Stock::OnSearchAtStockClicked()
{
    QDialog* searchWindow = new QDialog();
    searchWindow->setWindowTitle("Поиск по складу");
    searchWindow->resize(1200, 400);

    QVBoxLayout* verticalLayout = new QVBoxLayout;

    enterSearchLineEdit = new QLineEdit;
    enterSearchLineEdit->setPlaceholderText("Введите поисковой запрос:");

    QPushButton* searchButton = new QPushButton("Поиск");
    connect(searchButton, &QPushButton::clicked, this, &Stock::FillSearchTable);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(enterSearchLineEdit);
    horizontalLayout->addWidget(searchButton);

    verticalLayout->addLayout(horizontalLayout);

    tableSearchResult = new QTableWidget;

    QTableWidget* buf = stockTable;
    stockTable = tableSearchResult;

    tableSearchResult->setColumnCount(6);
    tableSearchResult->setHorizontalHeaderLabels({"Артикул", "Тип", "Название", "Характеристики", "Цена", "Количество"});

    tableSearchResult->setColumnWidth(0, 60);
    tableSearchResult->setColumnWidth(1, 200);
    tableSearchResult->setColumnWidth(2, 350);
    tableSearchResult->setColumnWidth(3, 350);
    tableSearchResult->setColumnWidth(4, 100);
    tableSearchResult->setColumnWidth(5, 100);

    tableSearchResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableSearchResult->setSelectionMode(QAbstractItemView::SingleSelection);

    QLabel* searchResultLabel = new QLabel("Таблица с результатами поиска:");
    searchResultLabel->setFont(QFont("Arial", 12));

    verticalLayout->addWidget(searchResultLabel);
    verticalLayout->addWidget(tableSearchResult);

    searchWindow->setLayout(verticalLayout);

    searchWindow->exec();

    stockTable = buf;

    delete searchResultLabel;

    delete searchButton;

    delete enterSearchLineEdit;
    enterSearchLineEdit = nullptr;

    delete tableSearchResult;
    tableSearchResult = nullptr;

    delete horizontalLayout;
    delete verticalLayout;
    delete searchWindow;
}

void Stock::OnStockFilterChanged(int index)
{
    QString selectedFilter = stockFilterComboBox->currentText();

    Component::Type type = getTypeByFilter(selectedFilter);

    QList<Component::Component*> components = sortByTypeComponentList(stock, type);

    if(!components.isEmpty())
        FillTable(stockTable, components);
    else if(type == Component::UNKNOWN)
    {
        components = stock;
        FillTable(stockTable, components);
    }
    else
        QMessageBox::information(nullptr, "Выбранный тип", "Нет комплектующих выбранного типа");
}

void Stock::DeletePurchasedComponentsFromFile(Component::Component* stockComponent, int deletedAmount)
{
    QList<QStringList> records;

    QFile holderFile(getHolderByType(stockComponent->GetType()));

    if(holderFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&holderFile);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split(";");
            records.append(fields);
        }

        holderFile.close();
    }
    else
        return;

    for (int i = 0; i < records.size(); i++)
    {
        if (records[i][ID] == QString::number(stockComponent->GetArticul()))
        {
            if(stockComponent->GetAmount() > deletedAmount)
            {
                records[i][getAmountIndexByType(stockComponent->GetType())] = QString::number(stockComponent->GetAmount() - deletedAmount);
                break;
            }
            else
            {
                records.removeAt(i);
                break;
            }
        }
    }

    if(holderFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&holderFile);

        for (const QStringList &fields : records)
            out << fields.join(";") << "\n";

        holderFile.close();
    }
    else
        return;
}

void Stock::DeletePurchasedComponentsFromList(Component::Component* stockComponent, Component::Component* cartComponent)
{
    if(cartComponent->GetAmount() < stockComponent->GetAmount())
    {
        amountOfComponents -= cartComponent->GetAmount();
        DeletePurchasedComponentsFromFile(stockComponent, cartComponent->GetAmount());
        stockComponent->SetAmount(stockComponent->GetAmount() - cartComponent->GetAmount());
    }
    else
    {
        amountOfComponents -= stockComponent->GetAmount();
        DeletePurchasedComponentsFromFile(stockComponent, cartComponent->GetAmount());
        stock.removeOne(stockComponent);
        delete stockComponent;
    }
}

void createAndPopulateFile()
{
    QFile outFile(BUFFER_FILE);
    if(outFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&outFile);

        const QString inputFiles[] = {GPU_FILE, CPU_FILE, MOTHERBOARD_FILE, RAM_FILE, ROM_FILE, POWER_UNIT_FILE, CASES_FILE, COOLER_FILE};

        for (const QString& inputFile : inputFiles)
        {
            QFile inFile(inputFile);
            if(inFile.open(QIODevice::ReadOnly))
            {
                QTextStream in(&inFile);

                while (!in.atEnd())
                {
                    QString str = in.readLine();
                    out << str << "\n";
                }

                inFile.close();
            }
            else
                qDebug() << "Ошибка открытия файла " << inputFile;
        }
        outFile.close();
    }
    else
        qDebug() << "Ошибка открытия файла " << BUFFER_FILE;
}

void Stock::OnSortButtonClicked()
{
    QDialog sortDialog;
    sortDialog.setWindowTitle("Настройка сортировки");
    sortDialog.resize(250, 150);

    QVBoxLayout sortLayout(&sortDialog);

    Component::Type type = getTypeByFilter(stockFilterComboBox->currentText());
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

void Stock::OnAdmitSortButtonClicked(Component::Type type, QRadioButton& sortByAmountLowCheckBox, QRadioButton& sortByAmountHighCheckBox, QRadioButton& sortByPriceMinCheckBox, QRadioButton& sortByPriceMaxCheckBox, QRadioButton& sortByParameter1, QRadioButton& sortByParameter2, QRadioButton& sortByParameter3, QRadioButton& sortByParameter4)
{
    QList<Component::Component*> result = sortByTypeComponentList(stock, type);

    if(!result.isEmpty())
    {
        sortByType(result, type, sortByAmountLowCheckBox, sortByAmountHighCheckBox, sortByPriceMinCheckBox, sortByPriceMaxCheckBox, sortByParameter1, sortByParameter2, sortByParameter3, sortByParameter4);
        FillTable(stockTable, result);
    }
    else if(type == Component::UNKNOWN)
    {
        result = stock;
        sortByType(result, type, sortByAmountLowCheckBox, sortByAmountHighCheckBox, sortByPriceMinCheckBox, sortByPriceMaxCheckBox, sortByParameter1, sortByParameter2, sortByParameter3, sortByParameter4);
        FillTable(stockTable, result);
    }
    else
        QMessageBox::information(nullptr, "Выбранный тип", "Нет комплектующих выбранного типа");
}

void Stock::OnStockInfoButtonClicked()
{
    QDialog dialog;
    dialog.setWindowTitle("Информация о товарах склада");
    dialog.resize(500, 100);

    QVBoxLayout layout(&dialog);

    QWidget widget1, widget2, widget3, widget4, widget5, widget6, widget7, widget8;
    QVBoxLayout layout1(&widget1), layout2(&widget2), layout3(&widget3), layout4(&widget4), layout5(&widget5), layout6(&widget6), layout7(&widget7), layout8(&widget8);
    QLabel commmonLabell, label1, label2, label3, label4, label5, label6, label7, label8;
    QProgressBar progressBar1, progressBar2, progressBar3, progressBar4, progressBar5, progressBar6, progressBar7, progressBar8;

    QString progressBarStyle = "QProgressBar {" "    border: 2px solid grey;" "    border-radius: 5px;" "    text-align: center;" "    background-color: #FFFFFF;" "}" "QProgressBar::chunk {" "    background-color: #007ACC;" "    margin: 0px;" "}";

    commmonLabell.setText("Количество всех товаров на складе: " + QString::number(GetAmountOfComponents()) + " шт.");
    commmonLabell.setContentsMargins(10, 10, 10, 10);
    commmonLabell.setFont(QFont("Arial", 12));
    layout.addWidget(&commmonLabell);

    label1.setText("Процессоры: " + QString::number(getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::CPU))) + " шт.");
    label1.setFont(QFont("Arial", 12));
    progressBar1.setRange(0, 100);
    progressBar1.setValue(100 * getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::CPU)) / GetAmountOfComponents());
    progressBar1.setStyleSheet(progressBarStyle);
    layout1.addWidget(&label1);
    layout1.addWidget(&progressBar1);
    widget1.setLayout(&layout1);
    layout.addWidget(&widget1);

    label2.setText("Видеокарты: " + QString::number(getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::GPU))) + " шт.");
    label2.setFont(QFont("Arial", 12));
    progressBar2.setRange(0, 100);
    progressBar2.setValue(100 * getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::GPU)) / GetAmountOfComponents());
    progressBar2.setStyleSheet(progressBarStyle);
    layout2.addWidget(&label2);
    layout2.addWidget(&progressBar2);
    widget2.setLayout(&layout2);
    layout.addWidget(&widget2);

    label3.setText("Материнские платы: " + QString::number(getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::MOTHERBOARD))) + " шт.");
    label3.setFont(QFont("Arial", 12));
    progressBar3.setRange(0, 100);
    progressBar3.setValue(100 * getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::MOTHERBOARD)) / GetAmountOfComponents());
    progressBar3.setStyleSheet(progressBarStyle);
    layout3.addWidget(&label3);
    layout3.addWidget(&progressBar3);
    widget3.setLayout(&layout3);
    layout.addWidget(&widget3);

    label4.setText("Оперативная память: " + QString::number(getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::RAM))) + " шт.");
    label4.setFont(QFont("Arial", 12));
    progressBar4.setRange(0, 100);
    progressBar4.setValue(100 * getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::RAM)) / GetAmountOfComponents());
    progressBar4.setStyleSheet(progressBarStyle);
    layout4.addWidget(&label4);
    layout4.addWidget(&progressBar4);
    widget4.setLayout(&layout4);
    layout.addWidget(&widget4);

    label5.setText("Накопитель: " + QString::number(getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::ROM))) + " шт.");
    label5.setFont(QFont("Arial", 12));
    progressBar5.setRange(0, 100);
    progressBar5.setValue(100 * getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::ROM)) / GetAmountOfComponents());
    progressBar5.setStyleSheet(progressBarStyle);
    layout5.addWidget(&label5);
    layout5.addWidget(&progressBar5);
    widget5.setLayout(&layout5);
    layout.addWidget(&widget5);

    label6.setText("Блок питания: " + QString::number(getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::POWER_UNIT))) + " шт.");
    label6.setFont(QFont("Arial", 12));
    progressBar6.setRange(0, 100);
    progressBar6.setValue(100 * getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::POWER_UNIT)) / GetAmountOfComponents());
    progressBar6.setStyleSheet(progressBarStyle);
    layout6.addWidget(&label6);
    layout6.addWidget(&progressBar6);
    widget6.setLayout(&layout6);
    layout.addWidget(&widget6);

    label7.setText("Охлаждение: " + QString::number(getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::COOLER))) + " шт.");
    label7.setFont(QFont("Arial", 12));
    progressBar7.setRange(0, 100);
    progressBar7.setValue(100 * getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::COOLER)) / GetAmountOfComponents());
    progressBar7.setStyleSheet(progressBarStyle);
    layout7.addWidget(&label7);
    layout7.addWidget(&progressBar7);
    widget7.setLayout(&layout7);
    layout.addWidget(&widget7);

    label8.setText("Корпусы: " + QString::number(getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::CASE))) + " шт.");
    label8.setFont(QFont("Arial", 12));
    progressBar8.setRange(0, 100);
    progressBar8.setValue(100 * getAmountOfEachTypeList(sortByTypeComponentList(stock, Component::CASE)) / GetAmountOfComponents());
    progressBar8.setStyleSheet(progressBarStyle);
    layout8.addWidget(&label8);
    layout8.addWidget(&progressBar8);
    widget8.setLayout(&layout8);
    layout.addWidget(&widget8);

    dialog.setLayout(&layout);
    dialog.exec();
}

void Stock::CreateTab(QWidget* stockTab, QVBoxLayout* stockLayout, QHBoxLayout* stockButtonLayout, QVBoxLayout* stockSortLayout)
{
    searchButton = new QPushButton("Поиск по складу", stockTab);
    searchButton->setFont(QFont("Arial", 12));
    connect(searchButton, &QPushButton::clicked, this, &Stock::OnSearchAtStockClicked);

    stockFilterComboBox = new QComboBox(stockTab);
    stockFilterComboBox->setFont(QFont("Arial", 12));
    stockFilterComboBox->addItem("Тип");
    stockFilterComboBox->addItem("Все");
    stockFilterComboBox->addItem("Видеокарты");
    stockFilterComboBox->addItem("Процессоры");
    stockFilterComboBox->addItem("Материнские платы");
    stockFilterComboBox->addItem("Оперативная память");
    stockFilterComboBox->addItem("Блоки питания");
    stockFilterComboBox->addItem("Накопители");
    stockFilterComboBox->addItem("Корпуса");
    stockFilterComboBox->addItem("Охлаждение");

    stockFilterComboBox->setItemData(0, 0, Qt::UserRole - 1);

    connect(stockFilterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Stock::OnStockFilterChanged);

    stockTable = new QTableWidget(stockTab);
    stockTable->setColumnCount(6);
    stockTable->setHorizontalHeaderLabels({"Артикул", "Тип", "Название", "Характеристики", "Цена", "Количество"});

    stockTable->setColumnWidth(0, 60);
    stockTable->setColumnWidth(1, 200);
    stockTable->setColumnWidth(2, 370);
    stockTable->setColumnWidth(3, 550);
    stockTable->setColumnWidth(4, 100);
    stockTable->setColumnWidth(5, 100);

    stockTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    stockTable->setSelectionMode(QAbstractItemView::SingleSelection);

    sortButton = new QPushButton("Сортировать", stockTab);
    sortButton->setFont(QFont("Arial", 12));
    connect(sortButton, &QPushButton::clicked, this, &Stock::OnSortButtonClicked);

    infoButton = new QPushButton("Информация о складе", stockTab);
    infoButton->setFont(QFont("Arial", 12));
    connect(infoButton, &QPushButton::clicked, this, &Stock::OnStockInfoButtonClicked);

    stockLayout = new QVBoxLayout(stockTab);

    stockButtonLayout = new QHBoxLayout(stockTab);

    stockSortLayout = new QVBoxLayout(stockTab);
    stockSortLayout->addWidget(stockFilterComboBox);
    stockSortLayout->addWidget(sortButton);

    stockButtonLayout->addLayout(stockSortLayout);
    stockButtonLayout->addWidget(searchButton);
    stockButtonLayout->addWidget(infoButton);

    stockLayout->addLayout(stockButtonLayout);
    stockLayout->addWidget(stockTable);
}

QList<Component::Component*>& Stock::GetStock()
{
    return stock;
}

QTableWidget* Stock::GetStockTable()
{
    return stockTable;
}
