#include "configurator.h"

Configurator::Configurator()
{
    selectTable = nullptr;
    currentSum = 0;

    cpuButton = nullptr;
    motherboardButton = nullptr;
    gpuButton = nullptr;
    ramButton = nullptr;
    romButton = nullptr;
    coolerButton = nullptr;
    powerUnitButton = nullptr;
    caseButton = nullptr;

    cpuLabel = nullptr;
    motherboardLabel = nullptr;
    gpuLabel = nullptr;
    ramLabel = nullptr;
    romLabel = nullptr;
    coolerLabel = nullptr;
    powerUnitLabel = nullptr;
    caseLabel = nullptr;

    selectedCpuLabel = nullptr;
    selectedMotherboardLabel = nullptr;
    selectedGpuLabel = nullptr;
    selectedRamLabel = nullptr;
    selectedRomLabel = nullptr;
    selectedCoolerLabel = nullptr;
    selectedPowerUnitLabel = nullptr;
    selectedCaseLabel = nullptr;

    configuratorSelectLabel = nullptr;
    configuratorSelectedLabel = nullptr;

    clearButton = nullptr;
    confirmButton = nullptr;
    sumLabel = nullptr;
}

Configurator::~Configurator()
{
    delete selectTable;

    delete cpuButton;
    delete motherboardButton;
    delete gpuButton;
    delete ramButton;
    delete romButton;
    delete coolerButton;
    delete powerUnitButton;
    delete caseButton;

    delete cpuLabel;
    delete motherboardLabel;
    delete gpuLabel;
    delete ramLabel;
    delete romLabel;
    delete coolerLabel;
    delete powerUnitLabel;
    delete caseLabel;

    delete selectedCpuLabel;
    delete selectedMotherboardLabel;
    delete selectedGpuLabel;
    delete selectedRamLabel;
    delete selectedRomLabel;
    delete selectedCoolerLabel;
    delete selectedPowerUnitLabel;
    delete selectedCaseLabel;

    delete configuratorSelectLabel;
    delete configuratorSelectedLabel;

    delete clearButton;
    delete confirmButton;
    delete sumLabel;
}

Component::Component* Configurator::GetByType(Component::Type type)
{
    for(Component::Component* component : commonList)
    {
        if(type == component->GetType())
            return component;
    }
    return nullptr;
}

QList<Component::Component*> Configurator::SortSelectedType(QList<Component::Component*> currentList, Component::Type selectedType)
{
    QList<Component::Component*> finallList;

    switch(selectedType)
    {
        case Component::CPU:
        {
            return currentList;
        }
        case Component::MOTHERBOARD:
        {
            const Component::Cpu* currentCpu = dynamic_cast<Component::Cpu*>(GetByType(Component::CPU));
            for(Component::Component* component : currentList)
            {
                Component::Motherboard* toMotherboard = dynamic_cast<Component::Motherboard*>(component);
                if(toMotherboard->GetSocket() == currentCpu->GetSocket())
                    finallList.append(component);
            }
            return finallList;
        }
        case Component::GPU:
        {
            const Component::Motherboard* currentMotherboard = dynamic_cast<Component::Motherboard*>(GetByType(Component::MOTHERBOARD));
            for(Component::Component* component : currentList)
            {
                Component::Gpu* toGpu = dynamic_cast<Component::Gpu*>(component);
                if(toGpu->GetTireType() == currentMotherboard->GetGpuSlot())
                    finallList.append(component);
            }
            return finallList;
        }
        case Component::RAM:
        {
            const Component::Motherboard* currentMotherboard = dynamic_cast<Component::Motherboard*>(GetByType(Component::MOTHERBOARD));
            for(Component::Component* component : currentList)
            {
                Component::Ram* toRam = dynamic_cast<Component::Ram*>(component);
                if(toRam->GetType() == currentMotherboard->GetMemoryType() && toRam->GetSlats() <= currentMotherboard->GetRamSlots())
                    finallList.append(component);
            }
            return finallList;
        }
        case Component::ROM:
        {
            const Component::Motherboard* currentMotherboard = dynamic_cast<Component::Motherboard*>(GetByType(Component::MOTHERBOARD));
            for(Component::Component* component : currentList)
            {
                Component::Rom* toRom = dynamic_cast<Component::Rom*>(component);
                if(currentMotherboard->GetRomSlot().contains(toRom->GetSlot()))
                    finallList.append(component);
            }
            return finallList;
        }
        case Component::POWER_UNIT:
        {
            const Component::Cpu* currentCpu = dynamic_cast<Component::Cpu*>(GetByType(Component::CPU));
            if(currentCpu->GetIntegratedGpu() == CPU::IntegratedGpu::PRESENT && !IsInCommonList(Component::GPU))
                return currentList;

            const Component::Gpu* currentGpu = dynamic_cast<Component::Gpu*>(GetByType(Component::GPU));
            for(Component::Component* component : currentList)
            {
                Component::Powerunit* toPowerunit = dynamic_cast<Component::Powerunit*>(component);
                if(toPowerunit->GetPins() == currentGpu->GetPins() && toPowerunit->GetPower() >= currentGpu->GetRecommendPower())
                    finallList.append(component);
            }
            return finallList;
        }
        case Component::COOLER:
        {
            const Component::Cpu* currentCpu = dynamic_cast<Component::Cpu*>(GetByType(Component::CPU));
            for(Component::Component* component : currentList)
            {
                Component::Cooler* toCooler = dynamic_cast<Component::Cooler*>(component);
                if(toCooler->GetSockets().contains(currentCpu->GetSocket()))
                    finallList.append(component);
            }
            return finallList;
        }
        case Component::CASE:
        {
            const Component::Motherboard* currentMotherboard = dynamic_cast<Component::Motherboard*>(GetByType(Component::MOTHERBOARD));
            for(Component::Component* component : currentList)
            {
                Component::Case* toCase = dynamic_cast<Component::Case*>(component);
                if(toCase->GetFormFactor() == "ATX" && currentMotherboard->GetFormFactor() == "mini-ATX" || toCase->GetFormFactor() == currentMotherboard->GetFormFactor()) // добавить сравнение по кулер (по-возможности) если нет то в фалйе удалить форма-фактор кулера
                    finallList.append(component);
            }
            return finallList;
        }
    }
    return currentList;
}

void Configurator::CreateDialogForSelect(QList<Component::Component*> stock, QList<Component::Component*> currentList, Component::Type selectedType)
{
    if(!currentList.isEmpty())
    {
        QDialog* selectWindow = new QDialog();
        selectWindow->setWindowTitle("Выбор комплектующих");
        selectWindow->resize(830, 300);

        QVBoxLayout* wLayout = new QVBoxLayout;

        selectTable = new QTableWidget;

        selectTable->setColumnCount(4);
        selectTable->setHorizontalHeaderLabels({"Артикул", "Выбранные комплектующие", "Характеристики", "Цена"});

        selectTable->setColumnWidth(0, 60);
        selectTable->setColumnWidth(1, 400);
        selectTable->setColumnWidth(2, 200);
        selectTable->setColumnWidth(3, 100);

        selectTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        selectTable->setSelectionMode(QAbstractItemView::SingleSelection);

        wLayout->addWidget(selectTable);

        selectWindow->setLayout(wLayout);

        this->stock = stock;
        FillTable(SortSelectedType(currentList, selectedType));

        selectWindow->exec();

        delete selectTable;
        selectTable = nullptr;

        delete wLayout;
        wLayout = nullptr;

        delete selectWindow;
        selectWindow = nullptr;
    }
    else
        QMessageBox::information(nullptr, "Выбранный тип", "Нет комплектующих выбранного типа");
}

void Configurator::OnSelectTableItemDoubledclicked(QTableWidgetItem* item)
{
    QString textFromFirstColumn = selectTable->item(item->row(), 0)->text();

    int indvNumber = textFromFirstColumn.toInt();

    Component::Component* component = findComponentByIndvNumber(stock, indvNumber);

    switch(component->GetType())
    {
        case Component::CPU:
        {
            if(IsInCommonListDelete(Component::CPU))
            {
                commonList.clear();
                currentSum = 0;

                selectedMotherboardLabel->setText("Материнская плата: не выбрано");
                selectedRamLabel->setText("Оперативная память: не выбрано");
                selectedRomLabel->setText("Накопитель: не выбрано");
                selectedCoolerLabel->setText("Охлаждение: не выбрано");
                selectedPowerUnitLabel->setText("Блок питания: не выбрано");
                selectedCaseLabel->setText("Корпус: не выбрано");
            }
            const Component::Cpu* currentCpu = dynamic_cast<Component::Cpu*>(component);

            if(currentCpu->GetIntegratedGpu() == CPU::IntegratedGpu::PRESENT)
                selectedGpuLabel->setText("Видеокарта: Встроенная графика");
            else
                selectedGpuLabel->setText("Видеокарта: не выбрано");

            selectedCpuLabel->setText("Процессор: " + currentCpu->GetName() + "(" + QString::number(currentCpu->GetCores()) + "/" + QString::number(currentCpu->GetStreams()) + ")");

            QMessageBox::information(nullptr, "Добавление", "Процессор добавлен");
            break;
        }
        case Component::MOTHERBOARD:
        {
            if(IsInCommonListDelete(Component::MOTHERBOARD))
            {
                IsInCommonListDelete(Component::GPU);
                IsInCommonListDelete(Component::CASE);
                IsInCommonListDelete(Component::RAM);
                IsInCommonListDelete(Component::ROM);

                selectedRamLabel->setText("Оперативная память: не выбрано");
                selectedCaseLabel->setText("Корпус: не выбрано");
                selectedRomLabel->setText("Накопитель: не выбрано");
            }
            const Component::Cpu* currentCpu = dynamic_cast<Component::Cpu*>(GetByType(Component::CPU));

            if(currentCpu->GetIntegratedGpu() == CPU::IntegratedGpu::PRESENT)
                selectedGpuLabel->setText("Видеокарта: Встроенная графика");
            else
                selectedGpuLabel->setText("Видеокарта: не выбрано");

            const Component::Motherboard* toMotherboard = dynamic_cast<Component::Motherboard*>(component);
            selectedMotherboardLabel->setText("Материнская плата: " + toMotherboard->GetName() + "(" + toMotherboard->GetSocket() + "/" + toMotherboard->GetChipset() + "/" + toMotherboard->GetMemoryType() + ")");

            QMessageBox::information(nullptr, "Добавление", "Материнская плата добавлена");
            break;
        }
        case Component::GPU:
        {
            if(IsInCommonListDelete(Component::GPU))
            {
                IsInCommonListDelete(Component::POWER_UNIT);

                selectedPowerUnitLabel->setText("Блок питания: не выбрано");
            }
            const Component::Gpu* toGpu = dynamic_cast<Component::Gpu*>(component);
            selectedGpuLabel->setText("Видеокарта: " + toGpu->GetName() + "(" + QString::number(toGpu->GetMemory()) + "ГБ/" + toGpu->GetMemoryType() + ")");

            QMessageBox::information(nullptr, "Добавление", "Видеокарта добавлена");
            break;
        }
        case Component::RAM:
        {
            IsInCommonListDelete(Component::RAM);
            const Component::Ram* toRam = dynamic_cast<Component::Ram*>(component);
            selectedRamLabel->setText("Оперативная память: " + toRam->GetName() + "(" + QString::number(toRam->GetCapacity()) + "ГБ/" + toRam->GetType() + ")");

            QMessageBox::information(nullptr, "Добавление", "Оперативная память добавлена");
            break;
        }
        case Component::ROM:
        {
            IsInCommonListDelete(Component::ROM);
            const Component::Rom* toRom = dynamic_cast<Component::Rom*>(component);
            selectedRomLabel->setText("Накопитель: " + toRom->GetName() + "(" + QString::number(toRom->GetCapacity()) + "ГБ/" + toRom->GetType() + ")");

            QMessageBox::information(nullptr, "Добавление", "Накопитель добавлен");
            break;
        }
        case Component::POWER_UNIT:
        {
            IsInCommonListDelete(Component::POWER_UNIT);
            const Component::Powerunit* toPowerUnit = dynamic_cast<Component::Powerunit*>(component);
            selectedPowerUnitLabel->setText("Блок питания: " + toPowerUnit->GetName() + "(" + QString::number(toPowerUnit->GetPower()) + "Вт/" + toPowerUnit->GetSertificate() + ")");

            QMessageBox::information(nullptr, "Добавление", "Блок питания добавлен");
            break;
        }
        case Component::COOLER:
        {
            IsInCommonListDelete(Component::COOLER);
            const Component::Cooler* toCooler = dynamic_cast<Component::Cooler*>(component);
            selectedCoolerLabel->setText("Охлаждение: " + toCooler->GetName() + "(" + toCooler->GetCoolingType() + ")");

            QMessageBox::information(nullptr, "Добавление", "Охлаждение добавлено");
            break;
        }
        case Component::CASE:
        {
            IsInCommonListDelete(Component::CASE);
            const Component::Case* toCase = dynamic_cast<Component::Case*>(component);
            selectedCaseLabel->setText("Корпус: " + toCase->GetName() + "(" + toCase->GetFormFactor() + ")");

            QMessageBox::information(nullptr, "Добавление", "Корпус добавлен");
            break;
        }
    }
    commonList.append(component);
    currentSum += component->GetCost();
    sumLabel->setText("СУММА: " + QString::number(currentSum) + "$");
}

void Configurator::FillTable(QList<Component::Component*> currentList)
{
    int row = 0;
    for (const Component::Component* component : currentList) {
        selectTable->insertRow(row);
        selectTable->setItem(row, 0, new QTableWidgetItem(QString::number(component->GetArticul())));
        selectTable->setItem(row, 1, new QTableWidgetItem(component->GetName()));
        selectTable->setItem(row, 3, new QTableWidgetItem(QString::number(component->GetCost()) + "$"));

        Component::Type type = component->GetType();

        switch(type)
        {
            case Component::GPU:
            {
                const Component::Gpu* gpu = dynamic_cast<const Component::Gpu*>(component);
                if (gpu)
                    selectTable->setItem(row, 2, new QTableWidgetItem(QString::number(gpu->GetMemory()) + "ГБ/" + gpu->GetMemoryType() + "/" + QString::number(gpu->GetFrequency()) + "ГГц"));
                break;
            }
            case Component::CPU:
            {
                const Component::Cpu* cpu = dynamic_cast<const Component::Cpu*>(component);
                if (cpu)
                    selectTable->setItem(row, 2, new QTableWidgetItem(QString::number(cpu->GetCores()) + " ядер/" + QString::number(cpu->GetStreams()) + " потоков/" + cpu->GetSocket() + "/" + cpu->GetArchitecture()));
                break;
            }
            case Component::RAM:
            {
                const Component::Ram* ram = dynamic_cast<const Component::Ram*>(component);
                if (ram)
                    selectTable->setItem(row, 2, new QTableWidgetItem(QString::number(ram->GetCapacity()) + "ГБ/" + ram->GetType() + "/" + QString::number(ram->GetFrequency()) + "ГГц/" + QString::number(ram->GetSlats()) + " планки"));
                break;
            }
            case Component::ROM:
            {
                const Component::Rom* rom = dynamic_cast<const Component::Rom*>(component);
                if (rom)
                    selectTable->setItem(row, 2, new QTableWidgetItem(rom->GetType() + "/" + QString::number(rom->GetCapacity()) + "МБ/" + QString::number(rom->GetSpeed()) + "МБ/с|" + rom->GetSlot()));
                break;
            }
            case Component::MOTHERBOARD:
            {
                const Component::Motherboard* motherboard = dynamic_cast<const Component::Motherboard*>(component);
                if (motherboard)
                    selectTable->setItem(row, 2, new QTableWidgetItem(motherboard->GetSocket() + "/" + motherboard->GetChipset() + "/" + motherboard->GetMemoryType() + "/" + motherboard->GetFormFactor()));
                break;
            }
            case Component::POWER_UNIT:
            {
                const Component::Powerunit* power_unit = dynamic_cast<const Component::Powerunit*>(component);
                if (power_unit)
                    selectTable->setItem(row, 2, new QTableWidgetItem(QString::number(power_unit->GetPower()) + "Вт/" + QString::number(power_unit->GetPins()) + "pin/" + power_unit->GetFormFactor() + "/" + power_unit->GetSertificate()));
                break;
            }
            case Component::CASE:
            {
                const Component::Case* frame = dynamic_cast<const Component::Case*>(component);
                if (frame)
                    selectTable->setItem(row, 2, new QTableWidgetItem(frame->GetFormFactor() + "/" + frame->GetColor() + "/" + frame->GetWindow() + "/" + frame->GetMaterial()));
                break;
            }
            case Component::COOLER:
            {
                const Component::Cooler* cooler = dynamic_cast<const Component::Cooler*>(component);
                if (cooler)
                    selectTable->setItem(row, 2, new QTableWidgetItem(cooler->GetSockets() + "/" + cooler->GetCoolingType() + "/" + cooler->GetFormFactor() + "/" + QString::number(cooler->GetCoolingPower()) + "Вт"));
                break;
            }
        }

        for(int col = 0; col < selectTable->columnCount(); col++)
        {
            QTableWidgetItem* item = selectTable->item(row, col);

            if (item)
                item->setFlags((item->flags() & ~Qt::ItemIsEditable));
        }

        selectTable->setRowHeight(row, QPaintDevice::PdmHeightMM);

        row++;
    }

    connect(selectTable, &QTableWidget::itemDoubleClicked, this, &Configurator::OnSelectTableItemDoubledclicked);
}

bool Configurator::CheckForComponentInCommonList(Component::Type type)
{
    switch(type)
    {
        case Component::CPU:
        {
            return true;
        }
        case Component::MOTHERBOARD:
        {
            if(!IsInCommonList(Component::CPU))
            {
                QMessageBox::information(nullptr, "Выбранное комплектующее", "Вы не выбрали процессор");
                return false;
            }
            return true;
        }
        case Component::GPU:
        {
            if(!IsInCommonList(Component::MOTHERBOARD))
            {
                QMessageBox::information(nullptr, "Выбранное комплектующее", "Вы не выбрали материнскую плату");
                return false;
            }
            return true;
        }
        case Component::RAM:
        {
            if(!IsInCommonList(Component::MOTHERBOARD))
            {
                QMessageBox::information(nullptr, "Выбранное комплектующее", "Вы не выбрали материнскую плату");
                return false;
            }
            return true;
        }
        case Component::ROM:
        {
            if(!IsInCommonList(Component::MOTHERBOARD))
            {
                QMessageBox::information(nullptr, "Выбранное комплектующее", "Вы не выбрали материнскую плату");
                return false;
            }
            return true;
        }
        case Component::POWER_UNIT:
        {
            const Component::Cpu* currentCpu = dynamic_cast<Component::Cpu*>(GetByType(Component::CPU));

            if(!IsInCommonList(Component::GPU))
            {
                if((currentCpu != nullptr && currentCpu->GetIntegratedGpu() == CPU::IntegratedGpu::ABSENT) || currentCpu == nullptr)
                {
                    QMessageBox::information(nullptr, "Выбранное комплектующее", "Вы не выбрали видеокарту");
                    return false;
                }
            }
            return true;
        }
        case Component::COOLER:
        {
            if(!IsInCommonList(Component::CPU))
            {
                QMessageBox::information(nullptr, "Выбранное комплектующее", "Вы не выбрали процессор");
                return false;
            }
            return true;
        }
        case Component::CASE:
        {
            if(!IsInCommonList(Component::MOTHERBOARD))
            {
                QMessageBox::information(nullptr, "Выбранное комплектующее", "Вы не выбрали материнскую плату");
                return false;
            }
            return true;
        }
    }
}

bool Configurator::IsInCommonListDelete(Component::Type type)
{
    for(Component::Component* component : commonList)
    {
        if(type == component->GetType())
        {
            commonList.removeOne(component);
            currentSum -= component->GetCost();
            return true;
        }
    }
    return false;
}

bool Configurator::IsInCommonList(Component::Type type)
{
    for(Component::Component* component : commonList)
    {
        if(type == component->GetType())
            return true;
    }
    return false;
}

void Configurator::ClearConfiguration()
{
    if(!commonList.empty())
    {
        commonList.clear();
        currentSum = 0;

        selectedCpuLabel->setText("Процессор: не выбрано");
        selectedMotherboardLabel->setText("Материнская плата: не выбрано");
        selectedGpuLabel->setText("Видеокарта: не выбрано");
        selectedRamLabel->setText("Оперативная память: не выбрано");
        selectedRomLabel->setText("Накопитель: не выбрано");
        selectedCoolerLabel->setText("Охлаждение: не выбрано");
        selectedPowerUnitLabel->setText("Блок питания: не выбрано");
        selectedCaseLabel->setText("Корпус: не выбрано");

        sumLabel->setText("СУММА: " + QString::number(currentSum) + "$");
    }
}

void Configurator::OnClearConfigurationClicked()
{
    if(!commonList.empty())
    {
        ClearConfiguration();
        QMessageBox::information(nullptr, "Конфигуратор", "Конфигурация сброшена");
    }
    else
        QMessageBox::warning(nullptr, "Конфигуратор", "Конфигурация пуста");
}

void Configurator::OnDoneButtonClicked()
{
    bool isAllComponentsThere = true;

    QString missComponents = "Не выбрано: ";

    for(int indexType = 1; indexType < COUNT_OF_COMPONENTS + 1; indexType++)
    {
        if(!IsInCommonList(static_cast<Component::Type>(indexType)))
        {
            if(static_cast<Component::Type>(indexType) == Component::GPU)
            {
                const Component::Cpu* currentCpu = dynamic_cast<Component::Cpu*>(GetByType(Component::CPU));
                if(currentCpu != nullptr && currentCpu->GetIntegratedGpu() == CPU::IntegratedGpu::PRESENT)
                    continue;
            }
            isAllComponentsThere = false;
            missComponents += getTextType(static_cast<Component::Type>(indexType)) += "; ";
        }
    }
    if(isAllComponentsThere)
    {
        emit AddConfigurationToCart(commonList);
        ClearConfiguration();
    }
    else
    {
        missComponents.chop(2);
        QMessageBox::warning(nullptr, "Конфигуратор", missComponents);
    }
}

void Configurator::CreateTab(QWidget* configuratorTab, QVBoxLayout* verticalConfiguratorLayout1, QVBoxLayout* verticalConfiguratorLayout2, QHBoxLayout* horizontalConfiguratorLayout)
{
    verticalConfiguratorLayout1 = new QVBoxLayout;
    verticalConfiguratorLayout2 = new QVBoxLayout;

    configuratorSelectLabel = new QLabel("Выберите конфигурацию компьютера");
    configuratorSelectLabel->setFont(QFont("Arial", 25));
    verticalConfiguratorLayout1->addWidget(configuratorSelectLabel);
    configuratorSelectLabel->setAlignment(Qt::AlignTop);

    cpuLabel = new QLabel("Процессор");
    cpuLabel->setFont(QFont("Arial", 14));
    cpuButton = new QPushButton("Выбрать процессор");
    cpuButton->setFixedWidth(275);
    verticalConfiguratorLayout1->addWidget(cpuLabel);
    verticalConfiguratorLayout1->addWidget(cpuButton);

    motherboardLabel = new QLabel("Материнская плата");
    motherboardLabel->setFont(QFont("Arial", 14));
    motherboardButton = new QPushButton("Выбрать материнскую плату");
    motherboardButton->setFixedWidth(275);
    verticalConfiguratorLayout1->addWidget(motherboardLabel);
    verticalConfiguratorLayout1->addWidget(motherboardButton);

    gpuLabel = new QLabel("Видеокарта");
    gpuLabel->setFont(QFont("Arial", 14));
    gpuButton = new QPushButton("Выбрать видеокарту");
    gpuButton->setFixedWidth(275);
    verticalConfiguratorLayout1->addWidget(gpuLabel);
    verticalConfiguratorLayout1->addWidget(gpuButton);

    ramLabel = new QLabel("Оперативная память");
    ramLabel->setFont(QFont("Arial", 14));
    ramButton = new QPushButton("Выбрать оперативную память");
    ramButton->setFixedWidth(275);
    verticalConfiguratorLayout1->addWidget(ramLabel);
    verticalConfiguratorLayout1->addWidget(ramButton);

    romLabel = new QLabel("Накопитель");
    romLabel->setFont(QFont("Arial", 14));
    romButton = new QPushButton("Выбрать накопитель");
    romButton->setFixedWidth(275);
    verticalConfiguratorLayout1->addWidget(romLabel);
    verticalConfiguratorLayout1->addWidget(romButton);

    coolerLabel = new QLabel("Охлаждение");
    coolerLabel->setFont(QFont("Arial", 14));
    coolerButton = new QPushButton("Выбрать охлаждение");
    coolerButton->setFixedWidth(275);
    verticalConfiguratorLayout1->addWidget(coolerLabel);
    verticalConfiguratorLayout1->addWidget(coolerButton);

    powerUnitLabel = new QLabel("Блок питания");
    powerUnitLabel->setFont(QFont("Arial", 14));
    powerUnitButton = new QPushButton("Выбрать блок питания");
    powerUnitButton->setFixedWidth(275);
    verticalConfiguratorLayout1->addWidget(powerUnitLabel);
    verticalConfiguratorLayout1->addWidget(powerUnitButton);

    caseLabel = new QLabel("Корпус");
    caseLabel->setFont(QFont("Arial", 14));
    caseButton = new QPushButton("Выбрать корпус");
    caseButton->setFixedWidth(275);
    verticalConfiguratorLayout1->addWidget(caseLabel);
    verticalConfiguratorLayout1->addWidget(caseButton);

    clearButton = new QPushButton("Очистить");
    connect(clearButton, &QPushButton::clicked, this, &Configurator::OnClearConfigurationClicked);
    clearButton->setFixedWidth(100);
    clearButton->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout1->addWidget(clearButton);

    configuratorSelectedLabel = new QLabel("Конфигурация компьютера");
    configuratorSelectedLabel->setFont(QFont("Arial", 25));
    verticalConfiguratorLayout2->addWidget(configuratorSelectedLabel);
    configuratorSelectedLabel->setAlignment(Qt::AlignTop);

    selectedCpuLabel = new QLabel("Процессор: не выбрано");
    selectedCpuLabel->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(selectedCpuLabel);

    selectedMotherboardLabel = new QLabel("Материнская плата: не выбрано");
    selectedMotherboardLabel->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(selectedMotherboardLabel);

    selectedGpuLabel = new QLabel("Видеокарта: не выбрано");
    selectedGpuLabel->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(selectedGpuLabel);

    selectedRamLabel = new QLabel("Оперативная память: не выбрано");
    selectedRamLabel->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(selectedRamLabel);

    selectedRomLabel = new QLabel("Накопитель: не выбрано");
    selectedRomLabel->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(selectedRomLabel);

    selectedCoolerLabel = new QLabel("Охлаждение: не выбрано");
    selectedCoolerLabel->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(selectedCoolerLabel);

    selectedPowerUnitLabel = new QLabel("Блок питания: не выбрано");
    selectedPowerUnitLabel->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(selectedPowerUnitLabel);

    selectedCaseLabel = new QLabel("Корпус: не выбрано");
    selectedCaseLabel->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(selectedCaseLabel);

    sumLabel = new QLabel("СУММА: 0$");
    sumLabel->setFont(QFont("Arial", 20));
    verticalConfiguratorLayout2->addWidget(sumLabel);

    confirmButton = new QPushButton("ГОТОВО");
    connect(confirmButton, &QPushButton::clicked, this, &Configurator::OnDoneButtonClicked);
    confirmButton->setFixedWidth(180);
    confirmButton->setFixedHeight(50);
    confirmButton->setFont(QFont("Arial", 14));
    verticalConfiguratorLayout2->addWidget(confirmButton);

    horizontalConfiguratorLayout = new QHBoxLayout;
    horizontalConfiguratorLayout->addLayout(verticalConfiguratorLayout1);
    horizontalConfiguratorLayout->addLayout(verticalConfiguratorLayout2);

    verticalConfiguratorLayout2->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    configuratorTab->setLayout(horizontalConfiguratorLayout);
}

QPushButton* Configurator::GetCpuButton() const
{
    return cpuButton;
}
QPushButton* Configurator::GetMotherboardButton() const
{
    return motherboardButton;
}
QPushButton* Configurator::GetGpuButton() const
{
    return gpuButton;
}
QPushButton* Configurator::GetRamButton() const
{
    return ramButton;
}
QPushButton* Configurator::GetRomButton() const
{
    return romButton;
}
QPushButton* Configurator::GetCoolerButton() const
{
    return coolerButton;
}
QPushButton* Configurator::GetPowerUnitButton() const
{
    return powerUnitButton;
}
QPushButton* Configurator::GetCaseButton() const
{
    return caseButton;
}
QPushButton* Configurator::GetClearButton() const
{
    return clearButton;
}
QPushButton* Configurator::GetConfirmButton() const
{
    return confirmButton;
}
