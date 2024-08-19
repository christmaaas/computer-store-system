#include "stockRepository.h"

#include <QDebug>
#include <QFile>
#include <QString>

#include "components/case.h"
#include "components/cooler.h"
#include "components/cpu.h"
#include "components/gpu.h"
#include "components/motherboard.h"
#include "components/powerUnit.h"
#include "components/ram.h"
#include "components/rom.h"

static constexpr const char caseFile[] = "./resources/cases.txt";
static constexpr const char coolerFile[] = "./resources/cooler.txt";
static constexpr const char cpuFile[] = "./resources/cpu.txt";
static constexpr const char gpuFile[] = "./resources/gpu.txt";
static constexpr const char motherboardFile[] = "./resources/motherboard.txt";
static constexpr const char powerUnitFile[] = "./resources/power_units.txt";
static constexpr const char ramFile[] = "./resources/ram.txt";
static constexpr const char romFile[] = "./resources/rom.txt";

enum ComponentCommonFields {
    Id = 0,
    TypeOfComponent,
    NameOfComponent
};

namespace StockData
{
    const StockRepository::stockListType StockRepository::GetListOfType(const Component::ComponentType type) noexcept
    {
        if (stockList.empty())
        {
            FillStockList();
        }

        stockListType list;

        for (auto& component : stockList)
        {
            if (component->GetType() == type)
            {
                list.emplace_back(component);
            }
        }

        return list;
    }

    void StockRepository::FillStockList() noexcept
    {
        const QString inputFiles[] = { caseFile, coolerFile, cpuFile,
                                       gpuFile, motherboardFile, powerUnitFile,
                                       ramFile, romFile };

        for (const QString& inputFile : inputFiles)
        {
            QFile inFile(inputFile);
            if (!inFile.open(QIODevice::ReadOnly))
            {
                qDebug() << "Ошибка открытия файла " << inputFile;
                return;
            }

            while (!inFile.atEnd())
            {
                QString str = inFile.readLine();
                QStringList substrings = str.split(";");

                Component::ComponentType type = static_cast<Component::ComponentType>(substrings[TypeOfComponent].toInt());

                AddToStockListByType(type, substrings);
            }

            inFile.close();
        }
    }

    void StockRepository::AddToStockListByType(const Component::ComponentType type, const QStringList& substring) noexcept
    {
        switch (type)
        {
        case Component::ComponentType::Gpu:
        {
            std::shared_ptr<Component::Gpu> gpu = std::make_shared<Component::Gpu>(
                substring[Id].toInt(),
                substring[NameOfComponent],
                substring[Component::Gpu::GpuSettings::Cost].toInt(),
                type,
                substring[Component::Gpu::GpuSettings::Amount].toInt(),
                substring[Component::Gpu::GpuSettings::Memory].toInt(),
                substring[Component::Gpu::GpuSettings::Frequency].toInt(),
                substring[Component::Gpu::GpuSettings::MemoryType],
                substring[Component::Gpu::GpuSettings::Slot],
                substring[Component::Gpu::GpuSettings::Pins].toInt(),
                substring[Component::Gpu::GpuSettings::Power].toInt()
            );

            stockList.emplace_back(std::move(gpu));

            break;
        }
        case Component::ComponentType::Cpu:
        {
            std::shared_ptr<Component::Cpu> cpu = std::make_shared<Component::Cpu>(
                substring[Id].toInt(),
                substring[NameOfComponent],
                substring[Component::Cpu::CpuSettings::Cost].toInt(),
                type,
                substring[Component::Cpu::CpuSettings::Amount].toInt(),
                substring[Component::Cpu::CpuSettings::Cores].toInt(),
                substring[Component::Cpu::CpuSettings::Steams].toInt(),
                substring[Component::Cpu::CpuSettings::Socket],
                substring[Component::Cpu::CpuSettings::Architecture],
                static_cast<Component::Cpu::IntegratedGpu>(substring[Component::Cpu::CpuSettings::IntegrategGpu].toInt())
            );

            stockList.emplace_back(std::move(cpu));

            break;
        }
        case Component::ComponentType::Ram:
        {
            std::shared_ptr<Component::Ram> ram = std::make_shared<Component::Ram>(
                substring[Id].toInt(),
                substring[NameOfComponent],
                substring[Component::Ram::RamSettings::Cost].toInt(),
                type,
                substring[Component::Ram::RamSettings::Amount].toInt(),
                substring[Component::Ram::RamSettings::Memory].toInt(),
                substring[Component::Ram::RamSettings::Frequency].toInt(),
                substring[Component::Ram::RamSettings::Slats].toInt(),
                substring[Component::Ram::RamSettings::Type]
            );

            stockList.emplace_back(std::move(ram));

            break;
        }
        case Component::ComponentType::Rom:
        {
            std::shared_ptr<Component::Rom> rom = std::make_shared<Component::Rom>(
                substring[Id].toInt(),
                substring[NameOfComponent],
                substring[Component::Rom::RomSettings::Cost].toInt(),
                type,
                substring[Component::Rom::RomSettings::Amount].toInt(),
                substring[Component::Rom::RomSettings::Capacity].toInt(),
                substring[Component::Rom::RomSettings::Speed].toInt(),
                substring[Component::Rom::RomSettings::Slot],
                substring[Component::Rom::RomSettings::Type]
            );

            stockList.emplace_back(std::move(rom));

            break;
        }
        case Component::ComponentType::Motherboard:
        {
            std::shared_ptr<Component::Motherboard> motherboard = std::make_shared<Component::Motherboard>(
                substring[Id].toInt(),
                substring[NameOfComponent],
                substring[Component::Motherboard::MotherboardSettings::Cost].toInt(),
                type,
                substring[Component::Motherboard::MotherboardSettings::Amount].toInt(),
                substring[Component::Motherboard::MotherboardSettings::Socket],
                substring[Component::Motherboard::MotherboardSettings::Chipset],
                substring[Component::Motherboard::MotherboardSettings::MemoryType],
                substring[Component::Motherboard::MotherboardSettings::Formfactor],
                substring[Component::Motherboard::MotherboardSettings::GpuType],
                substring[Component::Motherboard::MotherboardSettings::RomType],
                substring[Component::Motherboard::MotherboardSettings::RamSlots].toInt()
            );

            stockList.emplace_back(std::move(motherboard));

            break;
        }
        case Component::ComponentType::PowerUnit:
        {
            std::shared_ptr<Component::PowerUnit> powerUnit = std::make_shared<Component::PowerUnit>(
                substring[Id].toInt(),
                substring[NameOfComponent],
                substring[Component::PowerUnit::PowerUnitSettings::Cost].toInt(),
                type,
                substring[Component::PowerUnit::PowerUnitSettings::Amount].toInt(),
                substring[Component::PowerUnit::PowerUnitSettings::Power].toInt(),
                substring[Component::PowerUnit::PowerUnitSettings::Pins].toInt(),
                substring[Component::PowerUnit::PowerUnitSettings::FormFactor],
                substring[Component::PowerUnit::PowerUnitSettings::Certificate]
            );

            stockList.emplace_back(std::move(powerUnit));

            break;
        }
        case Component::ComponentType::Case:
        {
            std::shared_ptr<Component::Case> frame = std::make_shared<Component::Case>(
                substring[Id].toInt(),
                substring[NameOfComponent],
                substring[Component::Case::CaseSettings::Cost].toInt(),
                type,
                substring[Component::Case::CaseSettings::Amount].toInt(),
                substring[Component::Case::CaseSettings::Color],
                substring[Component::Case::CaseSettings::Material],
                substring[Component::Case::CaseSettings::Window],
                substring[Component::Case::CaseSettings::Formfactor]
            );

            stockList.emplace_back(std::move(frame));

            break;
        }
        case Component::ComponentType::Cooler:
        {
            std::shared_ptr<Component::Cooler> cooler = std::make_shared<Component::Cooler>(
                substring[Id].toInt(),
                substring[NameOfComponent],
                substring[Component::Cooler::CoolerSettings::Cost].toInt(),
                type,
                substring[Component::Cooler::CoolerSettings::Amount].toInt(),
                substring[Component::Cooler::CoolerSettings::Sockets],
                substring[Component::Cooler::CoolerSettings::CollingType],
                substring[Component::Cooler::CoolerSettings::Formfactor],
                substring[Component::Cooler::CoolerSettings::Power].toInt()
            );

            stockList.emplace_back(std::move(cooler));

            break;
        }
        default:
            break;
        }
    }

}