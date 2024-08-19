#include "mainwindow.h"

#include <QMessageBox>

#include "ui_mainwindow.h"

#include "userData/user.h"

#include "components/case.h"
#include "components/cooler.h"
#include "components/cpu.h"
#include "components/gpu.h"
#include "components/motherboard.h"
#include "components/powerUnit.h"
#include "components/ram.h"
#include "components/rom.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    stockInfoDialog(new StockInfoDialog(this))
{
    ui->setupUi(this);

    UpdateStockTable(StockData::StockRepository::GetStockList());

    UpdateUserInfo();

    connect(ui->infoButton, &QPushButton::clicked, this, &MainWindow::OnStockInfoButtonClicked);
    connect(ui->stockFilterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::OnStockFilterChanged);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::OnSearchButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete stockInfoDialog;
}

void MainWindow::UpdateStockTable(const StockData::StockRepository::stockListType& list) noexcept
{
    ui->stockTable->clearContents();
    ui->stockTable->setRowCount(0);

    int row = 0;
    for (const auto& component : list)
    {
        ui->stockTable->insertRow(row);
        ui->stockTable->setItem(row, 0, new QTableWidgetItem(QString::number(component->GetArticle())));
        ui->stockTable->setItem(row, 2, new QTableWidgetItem(component->GetName()));
        ui->stockTable->setItem(row, 4, new QTableWidgetItem(QString::number(component->GetCost()) + "$"));
        ui->stockTable->setItem(row, 5, new QTableWidgetItem(QString::number(component->GetAmount())));

        Component::ComponentType type = component->GetType();


        switch (type)
        {
        case Component::ComponentType::Gpu:
        {
            const Component::Gpu* gpu = dynamic_cast<const Component::Gpu*>(component.get());
            if (gpu)
            {
                ui->stockTable->setItem(row, 1, new QTableWidgetItem("Видеокарта"));
                ui->stockTable->setItem(row, 3, new QTableWidgetItem(QString::number(gpu->GetMemory()) + "ГБ/" +
                    gpu->GetMemoryType() + "/" + QString::number(gpu->GetFrequency()) + "МГц/" + gpu->GetTireType()));
            }

            break;
        }
        case Component::ComponentType::Cpu:
        {
            const Component::Cpu* cpu = dynamic_cast<const Component::Cpu*>(component.get());
            if (cpu)
            {
                ui->stockTable->setItem(row, 1, new QTableWidgetItem("Процессор"));
                ui->stockTable->setItem(row, 3, new QTableWidgetItem(QString::number(cpu->GetCores()) + " ядер/" +
                    QString::number(cpu->GetStreams()) + " потоков/" + cpu->GetSocket() + "/" + cpu->GetArchitecture()));
            }

            break;
        }
        case Component::ComponentType::Ram:
        {
            const Component::Ram* ram = dynamic_cast<const Component::Ram*>(component.get());
            if (ram)
            {
                ui->stockTable->setItem(row, 1, new QTableWidgetItem("Оперативная память"));
                ui->stockTable->setItem(row, 3, new QTableWidgetItem(QString::number(ram->GetCapacity()) + "ГБ/" +
                    ram->GetType() + "/" + QString::number(ram->GetFrequency()) + "ГГц/" + QString::number(ram->GetSlats()) + " планки"));
            }

            break;
        }
        case Component::ComponentType::Rom:
        {
            const Component::Rom* rom = dynamic_cast<const Component::Rom*>(component.get());
            if (rom)
            {
                ui->stockTable->setItem(row, 1, new QTableWidgetItem("Накопитель"));
                ui->stockTable->setItem(row, 3, new QTableWidgetItem(rom->GetType() + "/" + QString::number(rom->GetCapacity()) +
                    "МБ/" + QString::number(rom->GetSpeed()) + "МБ/с|" + rom->GetSlot()));
            }

            break;
        }
        case Component::ComponentType::Motherboard:
        {
            const Component::Motherboard* motherboard = dynamic_cast<const Component::Motherboard*>(component.get());
            if (motherboard)
            {
                ui->stockTable->setItem(row, 1, new QTableWidgetItem("Материнская плата"));
                ui->stockTable->setItem(row, 3, new QTableWidgetItem(motherboard->GetSocket() + "/" +
                    motherboard->GetChipset() + "/" + motherboard->GetMemoryType() + "/" + motherboard->GetFormFactor()));
            }

            break;
        }
        case Component::ComponentType::PowerUnit:
        {
            const Component::PowerUnit* power_unit = dynamic_cast<const Component::PowerUnit*>(component.get());
            if (power_unit)
            {
                ui->stockTable->setItem(row, 1, new QTableWidgetItem("Блок питания"));
                ui->stockTable->setItem(row, 3, new QTableWidgetItem(QString::number(power_unit->GetPower()) + "Вт/" +
                    QString::number(power_unit->GetPins()) + "pin/" + power_unit->GetFormFactor() + "/" + power_unit->GetCertificate()));
            }

            break;
        }
        case Component::ComponentType::Case:
        {
            const Component::Case* frame = dynamic_cast<const Component::Case*>(component.get());
            if (frame)
            {
                ui->stockTable->setItem(row, 1, new QTableWidgetItem("Корпус"));
                ui->stockTable->setItem(row, 3, new QTableWidgetItem(frame->GetFormFactor() + "/" +
                    frame->GetColor() + "/" + frame->GetWindow() + "/" + frame->GetMaterial()));
            }

            break;
        }
        case Component::ComponentType::Cooler:
        {
            const Component::Cooler* cooler = dynamic_cast<const Component::Cooler*>(component.get());
            if (cooler)
            {
                ui->stockTable->setItem(row, 1, new QTableWidgetItem("Охлаждение"));
                ui->stockTable->setItem(row, 3, new QTableWidgetItem(cooler->GetSockets() + "/" +
                    cooler->GetCoolingType() + "/" + cooler->GetFormFactor() + "/" + QString::number(cooler->GetCoolingPower()) + "Вт"));
            }

            break;
        }
        case Component::ComponentType::Unknown:
            break;
        }

        for (int col = 0; col < ui->stockTable->columnCount(); ++col)
        {
            QTableWidgetItem* item = ui->stockTable->item(row, col);

            if (item)
            {
                item->setFlags((item->flags() & ~Qt::ItemIsEditable));
            }
        }

        ui->stockTable->setRowHeight(row, QPaintDevice::PdmHeightMM);

        row++;
    }
}

void MainWindow::UpdateUserInfo() noexcept
{
    ui->loginLabel->setText("Логин: " + UserData::User::GetLogin());
    ui->positionLabel->setText("Роль: " + UserData::User::GetPosition());
    ui->phoneNumberLabel->setText("Контактный номер: " + UserData::User::GetPhoneNumber());
    ui->idLabel->setText("ID: " + UserData::User::GetId());

    QPixmap image("./resources/images/" + UserData::User::GetImageName());
    image = image.scaled(600, 600, Qt::KeepAspectRatio);
    ui->imageLabel->setPixmap(image);
}

Component::ComponentType MainWindow::GetTypeByFilter(const QString& selectedFilter)
{
    if (selectedFilter == "Все")
        return Component::ComponentType::Unknown;
    else if (selectedFilter == "Видеокарты")
        return Component::ComponentType::Gpu;
    else if (selectedFilter == "Процессоры")
        return Component::ComponentType::Cpu;
    else if (selectedFilter == "Материнские платы")
        return Component::ComponentType::Motherboard;
    else if (selectedFilter == "Оперативная память")
        return Component::ComponentType::Ram;
    else if (selectedFilter == "Блоки питания")
        return Component::ComponentType::PowerUnit;
    else if (selectedFilter == "Накопители")
        return Component::ComponentType::Rom;
    else if (selectedFilter == "Корпуса")
        return Component::ComponentType::Case;
    else if (selectedFilter == "Охлаждение")
        return Component::ComponentType::Cooler;

    return Component::ComponentType::Unknown;
}

void MainWindow::OnStockInfoButtonClicked() noexcept
{
    stockInfoDialog->show();
}

void MainWindow::OnStockFilterChanged() noexcept
{
    QString selectedFilter = ui->stockFilterComboBox->currentText();

    Component::ComponentType type = GetTypeByFilter(selectedFilter);

    const StockData::StockRepository::stockListType components = StockData::StockRepository::GetListOfType(type);

    if (type == Component::ComponentType::Unknown)
    {
        UpdateStockTable(StockData::StockRepository::GetStockList());
        return;
    }
    else if (components.empty())
    {
        QMessageBox::information(nullptr, "Выбранный тип", "Нет комплектующих выбранного типа");
        return;
    }

    UpdateStockTable(components);
}

void MainWindow::OnSearchButtonClicked() noexcept
{
    //TODO:
}