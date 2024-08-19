#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "stockinfodialog.h"

#include "stockData/stockRepository.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void UpdateStockTable(const StockData::StockRepository::stockListType& list) noexcept;
    void UpdateUserInfo() noexcept;

    Component::ComponentType GetTypeByFilter(const QString& selectedFilter);

private slots:
    void OnStockInfoButtonClicked() noexcept;
    void OnStockFilterChanged() noexcept;
    void OnSearchButtonClicked() noexcept;

private:
    Ui::MainWindow* ui = nullptr;
    StockInfoDialog* stockInfoDialog = nullptr;
};

#endif // MAINWINDOW_H
