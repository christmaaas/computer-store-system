#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabWidget = nullptr;
    stockTab = nullptr;
    cartTab = nullptr;
    configuratorTab = nullptr;
    ordersTab = nullptr;
    userInfoTab = nullptr;

    stockLayout = nullptr;
    stockButtonLayout = nullptr;
    stockSortLayout = nullptr;
    cartLayout = nullptr;
    cartButtonsLayout = nullptr;
    cartSortLayout = nullptr;
    verticalConfiguratorLayout1 = nullptr;
    verticalConfiguratorLayout2 = nullptr;
    horizontalConfiguratorLayout = nullptr;
    orderLayout = nullptr;
    userInfoLayout = nullptr;

    employee = new Employee;
    stock = new Stock;
    cart = new Cart;
    order = new Order;
    configurator = new Configurator;

    connect(stock, &Stock::AddToCart, cart, &Cart::AddComponent);
    connect(configurator, &Configurator::AddConfigurationToCart, cart, &Cart::AddConfiguration);
    connect(cart, &Cart::DeletePurchasedComponents, stock, &Stock::DeletePurchasedComponentsFromList);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete employee;
    delete cart;
    delete stock;
    delete order;
    delete configurator;

    delete stockSortLayout;
    delete stockButtonLayout;
    delete stockLayout;
    delete cartSortLayout;
    delete cartButtonsLayout;
    delete cartLayout;
    delete verticalConfiguratorLayout1;
    delete verticalConfiguratorLayout2;
    delete horizontalConfiguratorLayout;
    delete orderLayout;
    delete userInfoLayout;

    delete stockTab;
    delete cartTab;
    delete configuratorTab;
    delete ordersTab;
    delete userInfoTab;
    delete tabWidget;
}

void MainWindow::CreateMenu()
{
    tabWidget = new QTabWidget(this);

    stockTab = new QWidget;
    tabWidget->addTab(stockTab, "Склад");

    stock->CreateTab(stockTab, stockLayout, stockButtonLayout, stockSortLayout);

    cartTab = new QWidget;
    tabWidget->addTab(cartTab, "Корзина");

    cart->CreateTab(cartTab, cartLayout, cartButtonsLayout, cartSortLayout);
    connect(cart->GetOrderButton(), &QPushButton::clicked, this, &MainWindow::OnMakeOrderButtonClicked);

    configuratorTab = new QWidget;
    tabWidget->addTab(configuratorTab, "Конфигуратор");

    configurator->CreateTab(configuratorTab, verticalConfiguratorLayout1, verticalConfiguratorLayout2, horizontalConfiguratorLayout);
    connect(configurator->GetCpuButton(), &QPushButton::clicked, this, &MainWindow::OnConfiguratorSelectButtonClicked);
    connect(configurator->GetMotherboardButton(), &QPushButton::clicked, this, &MainWindow::OnConfiguratorSelectButtonClicked);
    connect(configurator->GetGpuButton(), &QPushButton::clicked, this, &MainWindow::OnConfiguratorSelectButtonClicked);
    connect(configurator->GetRamButton(), &QPushButton::clicked, this, &MainWindow::OnConfiguratorSelectButtonClicked);
    connect(configurator->GetRomButton(), &QPushButton::clicked, this, &MainWindow::OnConfiguratorSelectButtonClicked);
    connect(configurator->GetCoolerButton(), &QPushButton::clicked, this, &MainWindow::OnConfiguratorSelectButtonClicked);
    connect(configurator->GetPowerUnitButton(), &QPushButton::clicked, this, &MainWindow::OnConfiguratorSelectButtonClicked);
    connect(configurator->GetCaseButton(), &QPushButton::clicked, this, &MainWindow::OnConfiguratorSelectButtonClicked);

    ordersTab = new QWidget;
    tabWidget->addTab(ordersTab, "Список заказов");

    order->CreateTab(ordersTab, orderLayout);

    userInfoTab = new QWidget;
    tabWidget->addTab(userInfoTab, "Пользователь");

    employee->CreateTab(userInfoTab, userInfoLayout);

    setCentralWidget(tabWidget);
}

void MainWindow::OnMakeOrderButtonClicked()
{
    if(cart->GetCart().isEmpty())
        QMessageBox::information(nullptr, "Корзина", "Корзина пуста");
    else
    {
        order->FillReceiverData(cart->GetTotalCost());

        int amountOfComponentsAtOrder = cart->GetAmountOfComponents();

        if (order->GetOrderDetailDialog()->result() != QDialog::Rejected)
        {
            order->FillFile(cart->GetCart());
            order->FillTable(cart->GetCart());

            cart->MakeAnOrder(stock->GetStock());
            stock->FillTable(stock->GetStockTable(), stock->GetStock());
            cart->ClearTable();

            delete order->GetOrderDetailDialog();
            order->SetOrderDetailDialog(nullptr);

            QMessageBox::information(nullptr, "Заказ", "Заказ успешно оформлен. Cумма заказа: " + QString::number(order->GetOrderCost()) + "$ ; " + "Количество заказанных товаров: " + QString::number(amountOfComponentsAtOrder) + "шт.");
        }
    }
}

void MainWindow::OnConfiguratorSelectButtonClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if (clickedButton)
    {
        if (clickedButton == configurator->GetCpuButton() && configurator->CheckForComponentInCommonList(Component::CPU))
        {
            configurator->CreateDialogForSelect(stock->GetStock(), sortByTypeComponentList(stock->GetStock(), Component::CPU), Component::CPU);
        }
        else if (clickedButton == configurator->GetMotherboardButton() && configurator->CheckForComponentInCommonList(Component::MOTHERBOARD))
        {
            configurator->CreateDialogForSelect(stock->GetStock(), sortByTypeComponentList(stock->GetStock(), Component::MOTHERBOARD), Component::MOTHERBOARD);
        }
        else if (clickedButton == configurator->GetGpuButton() && configurator->CheckForComponentInCommonList(Component::GPU))
        {
            configurator->CreateDialogForSelect(stock->GetStock(), sortByTypeComponentList(stock->GetStock(), Component::GPU), Component::GPU);
        }
        else if (clickedButton == configurator->GetRamButton() && configurator->CheckForComponentInCommonList(Component::RAM))
        {
            configurator->CreateDialogForSelect(stock->GetStock(), sortByTypeComponentList(stock->GetStock(), Component::RAM), Component::RAM);
        }
        else if (clickedButton == configurator->GetRomButton() && configurator->CheckForComponentInCommonList(Component::ROM))
        {
            configurator->CreateDialogForSelect(stock->GetStock(), sortByTypeComponentList(stock->GetStock(), Component::ROM), Component::ROM);
        }
        else if (clickedButton == configurator->GetCoolerButton() && configurator->CheckForComponentInCommonList(Component::COOLER))
        {
            configurator->CreateDialogForSelect(stock->GetStock(), sortByTypeComponentList(stock->GetStock(), Component::COOLER), Component::COOLER);
        }
        else if (clickedButton == configurator->GetPowerUnitButton() && configurator->CheckForComponentInCommonList(Component::POWER_UNIT))
        {
            configurator->CreateDialogForSelect(stock->GetStock(), sortByTypeComponentList(stock->GetStock(), Component::POWER_UNIT), Component::POWER_UNIT);
        }
        else if (clickedButton == configurator->GetCaseButton() && configurator->CheckForComponentInCommonList(Component::CASE))
        {
            configurator->CreateDialogForSelect(stock->GetStock(), sortByTypeComponentList(stock->GetStock(), Component::CASE), Component::CASE);
        }
    }
}

