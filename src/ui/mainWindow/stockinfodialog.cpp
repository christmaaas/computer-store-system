#include "components/case.h"
#include "components/component.h"
#include "components/cooler.h"
#include "components/cpu.h"
#include "components/gpu.h"
#include "components/motherboard.h"
#include "components/powerUnit.h"
#include "components/ram.h"
#include "components/rom.h"
#include "stockinfodialog.h"
#include "ui_stockinfodialog.h"

#include "stockData/stockRepository.h"

StockInfoDialog::StockInfoDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::StockInfoDialog)
{
    ui->setupUi(this);

    setWindowTitle("Информация о товарах склада");

    ui->totalLabel->setText("Количество всех товаров на складе: " + QString::number(StockData::StockRepository::GetTotalCount()) + " шт.");

    UpdateStockInfo();
}

StockInfoDialog::~StockInfoDialog()
{
    delete ui;
}

void StockInfoDialog::UpdateStockInfo() noexcept
{
    const int totalCpuCount = StockData::StockRepository::GetCountOfType<Component::Cpu>();
    ui->cpuProgressBar->setRange(0, 100);
    ui->cpuProgressBar->setValue(totalCpuCount);
    ui->cpuLabel->setText("Процессоры: " + QString::number(totalCpuCount));

    const int totalGpuCount = StockData::StockRepository::GetCountOfType<Component::Gpu>();
    ui->gpuProgressBar->setRange(0, 100);
    ui->gpuProgressBar->setValue(totalGpuCount);
    ui->gpuLabel->setText("Видеокарты: " + QString::number(totalCpuCount));


    //TODO и так далее
}
