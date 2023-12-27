#include "alghoritms.h"

QList<Component::Component*> sortByTypeComponentList(QList<Component::Component*> lisToSort, Component::Type type)
{
    QList<Component::Component*> newList;

    for(Component::Component* component : lisToSort)
    {
        if(component->GetType() == type)
            newList.append(component);
    }

    return newList;
}

int getAmountOfEachTypeList(QList<Component::Component*> list)
{
    int resultAmount = 0;

    for(Component::Component* component : list)
        resultAmount += component->GetAmount();

    return resultAmount;
}

Component::Component* findComponentByIndvNumber(QList<Component::Component*> list, int articul)
{
    for(Component::Component* component : list)
    {
        if(component->GetArticul() == articul)
            return component;
    }

    return nullptr;
}

Component::Component* getObjectByType(Component::Component* component)
{
    Component::Type type = component->GetType();

    switch(type)
    {
    case Component::Type::GPU:
    {
        const Component::Gpu* buf_gpu = dynamic_cast<const Component::Gpu*>(component);
        Component::Gpu* gpu = new Component::Gpu(*buf_gpu);
        return gpu;
    }
    case Component::Type::CPU:
    {
        const Component::Cpu* buf_cpu = dynamic_cast<const Component::Cpu*>(component);
        Component::Cpu* cpu = new Component::Cpu(*buf_cpu);
        return cpu;
    }
    case Component::Type::RAM:
    {
        const Component::Ram* buf_ram = dynamic_cast<const Component::Ram*>(component);
        Component::Ram* ram = new Component::Ram(*buf_ram);
        return ram;
    }
    case Component::Type::ROM:
    {
        const Component::Rom* buf_storagedevice = dynamic_cast<const Component::Rom*>(component);
        Component::Rom* storagedevice = new Component::Rom(*buf_storagedevice);
        return storagedevice;
    }
    case Component::Type::MOTHERBOARD:
    {
        const Component::Motherboard* buf_motherboard = dynamic_cast<const Component::Motherboard*>(component);
        Component::Motherboard* motherboard = new Component::Motherboard(*buf_motherboard);
        return motherboard;
    }
    case Component::Type::POWER_UNIT:
    {
        const Component::Powerunit* buf_powerunit = dynamic_cast<const Component::Powerunit*>(component);
        Component::Powerunit* powerunit = new Component::Powerunit(*buf_powerunit);
        return powerunit;
    }
    case Component::Type::CASE:
    {
        const Component::Case* buf_frame = dynamic_cast<const Component::Case*>(component);
        Component::Case* frame = new Component::Case(*buf_frame);
        return frame;
    }
    case Component::Type::COOLER:
    {
        const Component::Cooler* buf_cooler = dynamic_cast<const Component::Cooler*>(component);
        Component::Cooler* cooler = new Component::Cooler(*buf_cooler);
        return cooler;
    }
    default:
        break;
    }

    return nullptr;
}

Component::Type getTypeByFilter(QString selectedFilter)
{
    if (selectedFilter == "Все")
        return Component::UNKNOWN;
    else if (selectedFilter == "Видеокарты")
        return Component::GPU;
    else if (selectedFilter == "Процессоры")
        return Component::CPU;
    else if (selectedFilter == "Материнские платы")
        return Component::MOTHERBOARD;
    else if (selectedFilter == "Оперативная память")
        return Component::RAM;
    else if (selectedFilter == "Блоки питания")
        return Component::POWER_UNIT;
    else if (selectedFilter == "Накопители")
        return Component::ROM;
    else if (selectedFilter == "Корпуса")
        return Component::CASE;
    else if (selectedFilter == "Охлаждение")
        return Component::COOLER;
    return Component::UNKNOWN;

}

QString getTextType(Component::Type type)
{
    switch(type)
    {
    case Component::GPU:
        return "Видеокарта";
    case Component::CPU:
        return "Процессор";
    case Component::MOTHERBOARD:
        return "Материнская плата";
    case Component::RAM:
        return "Оперативная память";
    case Component::POWER_UNIT:
        return "Блок питания";
    case Component::ROM:
        return "Накопитель";
    case Component::CASE:
        return "Корпус";
    case Component::COOLER:
        return "Охлаждение";
    }
}

int getAmountIndexByType(Component::Type type)
{
    switch(type)
    {
    case Component::GPU:
        return GPU_AMOUNT;
    case Component::CPU:
        return CPU_AMOUNT;
    case Component::MOTHERBOARD:
        return MOTHERBOARD_AMOUNT;
    case Component::RAM:
        return RAM_AMOUNT;
    case Component::ROM:
        return ROM_AMOUNT;
    case Component::CASE:
        return CASE_AMOUNT;
    case Component::POWER_UNIT:
        return POWER_UNIT_AMOUNT;
    case Component::COOLER:
        return COOLER_AMOUNT;
    default:
        return -1;
    }
    return -1;
}

QString getHolderByType(Component::Type type)
{
    switch(type)
    {
    case Component::GPU:
        return GPU_FILE;
    case Component::CPU:
        return CPU_FILE;
    case Component::MOTHERBOARD:
        return MOTHERBOARD_FILE;
    case Component::RAM:
        return RAM_FILE;
    case Component::ROM:
        return ROM_FILE;
    case Component::CASE:
        return CASES_FILE;
    case Component::POWER_UNIT:
        return POWER_UNIT_FILE;
    case Component::COOLER:
        return COOLER_FILE;
    default:
        return "NONE";
    }
    return "NONE";
}

void getSortParameters(Component::Type type, QString* parameter1, QString* parameter2, QString* parameter3, QString* parameter4)
{
    switch(type)
    {
    case Component::GPU:
    {
        *parameter1 = "Объем памяти";
        *parameter2 = "Частота";
        *parameter3 = "Тип памяти";
        *parameter4 = "Слот";
        break;
    }
    case Component::CPU:
    {
        *parameter1 = "Кол-во ядер";
        *parameter2 = "Кол-во потоков";
        *parameter3 = "Сокет";
        *parameter4 = "Чипсет";
        break;
    }
    case Component::MOTHERBOARD:
    {
        *parameter1 = "Сокет";
        *parameter2 = "Чипсет";
        *parameter3 = "Тип памяти";
        *parameter4 = "Форм-фактор";
        break;
    }
    case Component::RAM:
    {
        *parameter1 = "Объем";
        *parameter2 = "Частота";
        *parameter3 = "Тип";
        *parameter4 = "Кол-во планок";
        break;
    }
    case Component::POWER_UNIT:
    {
        *parameter1 = "Мощность";
        *parameter2 = "Пины";
        *parameter3 = "Форм-фактор";
        *parameter4 = "Сертификат";
        break;
    }
    case Component::ROM:
    {
        *parameter1 = "Тип";
        *parameter2 = "Объем";
        *parameter3 = "Скорость";
        *parameter4 = "Слот";
        break;
    }
    case Component::CASE:
    {
        *parameter1 = "Форм-фактор";
        *parameter2 = "Цвет";
        *parameter3 = "Окно";
        *parameter4 = "Материал";
        break;
    }
    case Component::COOLER:
    {
        *parameter1 = "Сокеты";
        *parameter2 = "Тип";
        *parameter3 = "Форм-фактор";
        *parameter4 = "Мощность";
        break;
    }
    }
}

void sortByType(QList<Component::Component*>& result, Component::Type type, QRadioButton& sortByAmountLowCheckBox, QRadioButton& sortByAmountHighCheckBox, QRadioButton& sortByPriceMinCheckBox, QRadioButton& sortByPriceMaxCheckBox, QRadioButton& sortByParameter1, QRadioButton& sortByParameter2, QRadioButton& sortByParameter3, QRadioButton& sortByParameter4)
{
    if(sortByAmountLowCheckBox.isChecked())
        sortByFunctionComponentList(result, compareAmountLow);
    else if(sortByAmountHighCheckBox.isChecked())
        sortByFunctionComponentList(result, compareAmountHigh);
    else if(sortByPriceMinCheckBox.isChecked())
        sortByFunctionComponentList(result, compareCostLow);
    else if(sortByPriceMaxCheckBox.isChecked())
        sortByFunctionComponentList(result, compareCostHigh);
    if(type != Component::UNKNOWN)
    {
        switch(type)
        {
        case Component::GPU:
        {
            if(sortByParameter1.isChecked())
                sortByFunctionComponentList(result, compareGpuMemory);
            else if(sortByParameter2.isChecked())
                sortByFunctionComponentList(result, compareGpuFrequency);
            else if(sortByParameter3.isChecked())
                sortByFunctionComponentList(result, compareGpuMemoryType);
            else if(sortByParameter4.isChecked())
                sortByFunctionComponentList(result, compareGpuTireType);
            break;
        }
        case Component::CPU:
        {
            if(sortByParameter1.isChecked())
                sortByFunctionComponentList(result, compareCpuCores);
            else if(sortByParameter2.isChecked())
                sortByFunctionComponentList(result, compareCpuStreams);
            else if(sortByParameter3.isChecked())
                sortByFunctionComponentList(result, compareCpuSocket);
            else if(sortByParameter4.isChecked())
                sortByFunctionComponentList(result, compareCpuChipset);
            break;
        }
        case Component::MOTHERBOARD:
        {
            if(sortByParameter1.isChecked())
                sortByFunctionComponentList(result, compareMotherboardSocket);
            else if(sortByParameter2.isChecked())
                sortByFunctionComponentList(result, compareMotherboardChipset);
            else if(sortByParameter3.isChecked())
                sortByFunctionComponentList(result, compareMotherboardMemoryType);
            else if(sortByParameter4.isChecked())
                sortByFunctionComponentList(result, compareMotherboardFormfactor);
            break;
        }
        case Component::RAM:
        {
            if(sortByParameter1.isChecked())
                sortByFunctionComponentList(result, compareRamAmount);
            else if(sortByParameter2.isChecked())
                sortByFunctionComponentList(result, compareRamFrequency);
            else if(sortByParameter3.isChecked())
                sortByFunctionComponentList(result, compareRamType);
            else if(sortByParameter4.isChecked())
                sortByFunctionComponentList(result, compareRamSlats);
            break;
        }
        case Component::POWER_UNIT:
        {
            if(sortByParameter1.isChecked())
                sortByFunctionComponentList(result, comparePowerunitPower);
            else if(sortByParameter2.isChecked())
                sortByFunctionComponentList(result, comparePowerunitPins);
            else if(sortByParameter3.isChecked())
                sortByFunctionComponentList(result, comparePowerunitFormfactor);
            else if(sortByParameter4.isChecked())
                sortByFunctionComponentList(result, comparePowerunitSertificate);
            break;
        }
        case Component::ROM:
        {
            if(sortByParameter1.isChecked())
                sortByFunctionComponentList(result, compareRomType);
            else if(sortByParameter2.isChecked())
                sortByFunctionComponentList(result, compareRomAmount);
            else if(sortByParameter3.isChecked())
                sortByFunctionComponentList(result, compareRomSpeed);
            else if(sortByParameter4.isChecked())
                sortByFunctionComponentList(result, compareRomSlot);
            break;
        }
        case Component::CASE:
        {
            if(sortByParameter1.isChecked())
                sortByFunctionComponentList(result, compareCaseFormfactor);
            else if(sortByParameter2.isChecked())
                sortByFunctionComponentList(result, compareCaseColor);
            else if(sortByParameter3.isChecked())
                sortByFunctionComponentList(result, compareCaseWindow);
            else if(sortByParameter4.isChecked())
                sortByFunctionComponentList(result, compareCaseMaterial);
            break;
        }
        case Component::COOLER:
        {
            if(sortByParameter1.isChecked())
                sortByFunctionComponentList(result, compareCoolerSockets);
            else if(sortByParameter2.isChecked())
                sortByFunctionComponentList(result, compareCoolerType);
            else if(sortByParameter3.isChecked())
                sortByFunctionComponentList(result, compareCoolerFormfactor);
            else if(sortByParameter4.isChecked())
                sortByFunctionComponentList(result, compareCoolerPower);
            break;
        }
        default:
            break;
        }
    }
}

bool compareAmountHigh(Component::Component* a, Component::Component* b)
{
    return a->GetAmount() > b->GetAmount();
}

bool compareAmountLow(Component::Component* a, Component::Component* b)
{
    return a->GetAmount() < b->GetAmount();
}

bool compareCostHigh(Component::Component* a, Component::Component* b)
{
    return a->GetCost() > b->GetCost();
}

bool compareCostLow(Component::Component* a, Component::Component* b)
{
    return a->GetCost() < b->GetCost();
}

bool compareGpuMemory(Component::Component* a, Component::Component* b)
{
    Component::Gpu* gpu_a = dynamic_cast<Component::Gpu*>(a);
    Component::Gpu* gpu_b = dynamic_cast<Component::Gpu*>(b);
    return gpu_a->GetMemory() < gpu_b->GetMemory();
}

bool compareGpuMemoryType(Component::Component* a, Component::Component* b)
{
    Component::Gpu* gpu_a = dynamic_cast<Component::Gpu*>(a);
    Component::Gpu* gpu_b = dynamic_cast<Component::Gpu*>(b);
    return gpu_a->GetMemoryType()[4] < gpu_b->GetMemoryType()[4];
}

bool compareGpuFrequency(Component::Component* a, Component::Component* b)
{
    Component::Gpu* gpu_a = dynamic_cast<Component::Gpu*>(a);
    Component::Gpu* gpu_b = dynamic_cast<Component::Gpu*>(b);
    return gpu_a->GetFrequency() < gpu_b->GetFrequency();
}

bool compareGpuTireType(Component::Component* a, Component::Component* b)
{
    Component::Gpu* gpu_a = dynamic_cast<Component::Gpu*>(a);
    Component::Gpu* gpu_b = dynamic_cast<Component::Gpu*>(b);
    return gpu_a->GetTireType()[14] < gpu_b->GetTireType()[14];
}

bool compareCpuCores(Component::Component* a, Component::Component* b)
{
    Component::Cpu* cpu_a = dynamic_cast<Component::Cpu*>(a);
    Component::Cpu* cpu_b = dynamic_cast<Component::Cpu*>(b);
    return cpu_a->GetCores() < cpu_b->GetCores();
}

bool compareCpuStreams(Component::Component* a, Component::Component* b)
{
    Component::Cpu* cpu_a = dynamic_cast<Component::Cpu*>(a);
    Component::Cpu* cpu_b = dynamic_cast<Component::Cpu*>(b);
    return cpu_a->GetStreams() < cpu_b->GetStreams();
}

bool compareCpuSocket(Component::Component* a, Component::Component* b)
{
    Component::Cpu* cpu_a = dynamic_cast<Component::Cpu*>(a);
    Component::Cpu* cpu_b = dynamic_cast<Component::Cpu*>(b);
    return cpu_a->GetSocket()[0] < cpu_b->GetSocket()[0];
}

bool compareCpuChipset(Component::Component* a, Component::Component* b)
{
    Component::Cpu* cpu_a = dynamic_cast<Component::Cpu*>(a);
    Component::Cpu* cpu_b = dynamic_cast<Component::Cpu*>(b);
    return cpu_a->GetArchitecture()[0] < cpu_b->GetArchitecture()[0];
}

bool compareMotherboardSocket(Component::Component* a, Component::Component* b)
{
    Component::Motherboard* motherboard_a = dynamic_cast<Component::Motherboard*>(a);
    Component::Motherboard* motherboard_b = dynamic_cast<Component::Motherboard*>(b);
    return motherboard_a->GetSocket()[0] < motherboard_b->GetSocket()[0];
}

bool compareMotherboardChipset(Component::Component* a, Component::Component* b)
{
    Component::Motherboard* motherboard_a = dynamic_cast<Component::Motherboard*>(a);
    Component::Motherboard* motherboard_b = dynamic_cast<Component::Motherboard*>(b);
    return motherboard_a->GetChipset()[0] < motherboard_b->GetChipset()[0];
}

bool compareMotherboardMemoryType(Component::Component* a, Component::Component* b)
{
    Component::Motherboard* motherboard_a = dynamic_cast<Component::Motherboard*>(a);
    Component::Motherboard* motherboard_b = dynamic_cast<Component::Motherboard*>(b);
    return motherboard_a->GetMemoryType()[3] < motherboard_b->GetMemoryType()[3];
}

bool compareMotherboardFormfactor(Component::Component* a, Component::Component* b)
{
    Component::Motherboard* motherboard_a = dynamic_cast<Component::Motherboard*>(a);
    Component::Motherboard* motherboard_b = dynamic_cast<Component::Motherboard*>(b);
    return motherboard_a->GetFormFactor()[0] < motherboard_b->GetFormFactor()[0];
}

bool compareRamAmount(Component::Component* a, Component::Component* b)
{
    Component::Ram* ram_a = dynamic_cast<Component::Ram*>(a);
    Component::Ram* ram_b = dynamic_cast<Component::Ram*>(b);
    return ram_a->GetCapacity() < ram_b->GetCapacity();
}

bool compareRamFrequency(Component::Component* a, Component::Component* b)
{
    Component::Ram* ram_a = dynamic_cast<Component::Ram*>(a);
    Component::Ram* ram_b = dynamic_cast<Component::Ram*>(b);
    return ram_a->GetFrequency() < ram_b->GetFrequency();
}

bool compareRamType(Component::Component* a, Component::Component* b)
{
    Component::Ram* ram_a = dynamic_cast<Component::Ram*>(a);
    Component::Ram* ram_b = dynamic_cast<Component::Ram*>(b);
    return ram_a->GetType()[3] < ram_b->GetType()[3];
}

bool compareRamSlats(Component::Component* a, Component::Component* b)
{
    Component::Ram* ram_a = dynamic_cast<Component::Ram*>(a);
    Component::Ram* ram_b = dynamic_cast<Component::Ram*>(b);
    return ram_a->GetSlats() < ram_b->GetSlats();
}

bool comparePowerunitPower(Component::Component* a, Component::Component* b)
{
    Component::Powerunit* powerunit_a = dynamic_cast<Component::Powerunit*>(a);
    Component::Powerunit* powerunit_b = dynamic_cast<Component::Powerunit*>(b);
    return powerunit_a->GetPower() < powerunit_b->GetPower();
}

bool comparePowerunitPins(Component::Component* a, Component::Component* b)
{
    Component::Powerunit* powerunit_a = dynamic_cast<Component::Powerunit*>(a);
    Component::Powerunit* powerunit_b = dynamic_cast<Component::Powerunit*>(b);
    return powerunit_a->GetPins() < powerunit_b->GetPins();
}

bool comparePowerunitFormfactor(Component::Component* a, Component::Component* b)
{
    Component::Powerunit* powerunit_a = dynamic_cast<Component::Powerunit*>(a);
    Component::Powerunit* powerunit_b = dynamic_cast<Component::Powerunit*>(b);
    return powerunit_a->GetFormFactor()[0] < powerunit_b->GetFormFactor()[0];
}

bool comparePowerunitSertificate(Component::Component* a, Component::Component* b)
{
    Component::Powerunit* powerunit_a = dynamic_cast<Component::Powerunit*>(a);
    Component::Powerunit* powerunit_b = dynamic_cast<Component::Powerunit*>(b);
    return powerunit_a->GetSertificate()[0] < powerunit_b->GetSertificate()[0];
}

bool compareRomType(Component::Component* a, Component::Component* b)
{
    Component::Rom* rom_a = dynamic_cast<Component::Rom*>(a);
    Component::Rom* rom_b = dynamic_cast<Component::Rom*>(b);
    return rom_a->GetType()[0] < rom_b->GetType()[0];
}

bool compareRomAmount(Component::Component* a, Component::Component* b)
{
    Component::Rom* rom_a = dynamic_cast<Component::Rom*>(a);
    Component::Rom* rom_b = dynamic_cast<Component::Rom*>(b);
    return rom_a->GetCapacity() < rom_b->GetCapacity();
}

bool compareRomSpeed(Component::Component* a, Component::Component* b)
{
    Component::Rom* rom_a = dynamic_cast<Component::Rom*>(a);
    Component::Rom* rom_b = dynamic_cast<Component::Rom*>(b);
    return rom_a->GetSpeed() < rom_b->GetSpeed();
}

bool compareRomSlot(Component::Component* a, Component::Component* b)
{
    Component::Rom* rom_a = dynamic_cast<Component::Rom*>(a);
    Component::Rom* rom_b = dynamic_cast<Component::Rom*>(b);
    return rom_a->GetSlot()[0] < rom_b->GetSlot()[0];
}

bool compareCaseColor(Component::Component* a, Component::Component* b)
{
    Component::Case* case_a = dynamic_cast<Component::Case*>(a);
    Component::Case* case_b = dynamic_cast<Component::Case*>(b);
    return case_a->GetColor()[0] < case_b->GetColor()[0];
}

bool compareCaseMaterial(Component::Component* a, Component::Component* b)
{
    Component::Case* case_a = dynamic_cast<Component::Case*>(a);
    Component::Case* case_b = dynamic_cast<Component::Case*>(b);
    return case_a->GetMaterial()[0] < case_b->GetMaterial()[0];
}

bool compareCaseWindow(Component::Component* a, Component::Component* b)
{
    Component::Case* case_a = dynamic_cast<Component::Case*>(a);
    Component::Case* case_b = dynamic_cast<Component::Case*>(b);
    return case_a->GetWindow()[0] < case_b->GetWindow()[0];
}

bool compareCaseFormfactor(Component::Component* a, Component::Component* b)
{
    Component::Case* case_a = dynamic_cast<Component::Case*>(a);
    Component::Case* case_b = dynamic_cast<Component::Case*>(b);
    return case_a->GetFormFactor()[0] < case_b->GetFormFactor()[0];
}

bool compareCoolerSockets(Component::Component* a, Component::Component* b)
{
    Component::Cooler* cooler_a = dynamic_cast<Component::Cooler*>(a);
    Component::Cooler* cooler_b = dynamic_cast<Component::Cooler*>(b);
    return cooler_a->GetSockets()[0] < cooler_b->GetSockets()[0];
}

bool compareCoolerType(Component::Component* a, Component::Component* b)
{
    Component::Cooler* cooler_a = dynamic_cast<Component::Cooler*>(a);
    Component::Cooler* cooler_b = dynamic_cast<Component::Cooler*>(b);
    return cooler_a->GetCoolingType()[0] < cooler_b->GetCoolingType()[0];
}

bool compareCoolerFormfactor(Component::Component* a, Component::Component* b)
{
    Component::Cooler* cooler_a = dynamic_cast<Component::Cooler*>(a);
    Component::Cooler* cooler_b = dynamic_cast<Component::Cooler*>(b);
    return cooler_a->GetFormFactor()[0] < cooler_b->GetFormFactor()[0];
}

bool compareCoolerPower(Component::Component* a, Component::Component* b)
{
    Component::Cooler* cooler_a = dynamic_cast<Component::Cooler*>(a);
    Component::Cooler* cooler_b = dynamic_cast<Component::Cooler*>(b);
    return cooler_a->GetCoolingPower() < cooler_b->GetCoolingPower();
}

void sortByFunctionComponentList(QList<Component::Component*>& list_to_sort, bool (*func)(Component::Component* a, Component::Component* b))
{
    std::sort(list_to_sort.begin(), list_to_sort.end(), func);
}
