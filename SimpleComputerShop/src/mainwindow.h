#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QMenu>

#include "employee.h"
#include "stock.h"
#include "cart.h"
#include "order.h"
#include "configurator.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    QTabWidget* tabWidget;

    QWidget* stockTab;
    QWidget* cartTab;
    QWidget* configuratorTab;
    QWidget* ordersTab;
    QWidget* userInfoTab;

    QVBoxLayout* stockLayout;
    QHBoxLayout* stockButtonLayout;
    QVBoxLayout* stockSortLayout;
    QVBoxLayout* cartLayout;
    QHBoxLayout* cartButtonsLayout;
    QVBoxLayout* cartSortLayout;
    QVBoxLayout* verticalConfiguratorLayout1;
    QVBoxLayout* verticalConfiguratorLayout2;
    QHBoxLayout* horizontalConfiguratorLayout;
    QVBoxLayout* orderLayout;
    QVBoxLayout* userInfoLayout;

private slots:
    void OnMakeOrderButtonClicked();
    void OnConfiguratorSelectButtonClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void CreateMenu();

    Employee* employee;
    Stock* stock;
    Cart* cart;
    Order* order;
    Configurator* configurator;
};

#endif // MAINWINDOW_H
