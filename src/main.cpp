#include <QApplication>
#include <QStyleFactory>

#include "ui/loginWindow/loginwindow.h"
#include "ui/mainWindow/mainwindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("./resources/images/title_img.png"));

    qApp->setStyle(QStyleFactory::create("Fusion"));

    loginWindow loginWindow;
    loginWindow.exec();

    if (loginWindow.result() == QDialog::Accepted)
    {
        MainWindow mainWindow;

        mainWindow.show();

        return app.exec();
    }


    return 0;
}
