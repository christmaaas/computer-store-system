// @ArtemSlinkoProduction Group

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("./holders/images/title_img.png"));

    qApp->setStyle(QStyleFactory::create("Fusion"));

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Система компьютерного магазина");

    mainWindow.employee->ShowLoginDialog();

    if(mainWindow.employee->GetLoginDialog()->result() == QDialog::Accepted)
    {
        mainWindow.stock->FillList();
        mainWindow.CreateMenu();
        mainWindow.stock->FillTable(mainWindow.stock->GetStockTable(), mainWindow.stock->GetStock());
        mainWindow.order->FillTable(mainWindow.cart->GetCart());

        mainWindow.show();

        return app.exec();
    }
    else
        return 0;
}
