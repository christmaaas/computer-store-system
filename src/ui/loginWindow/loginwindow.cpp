#include "loginwindow.h"

#include <QMessageBox>

#include "ui_loginwindow.h"

#include "userData/user.h"

loginWindow::loginWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::loginWindow)
{
    ui->setupUi(this);

    ui->loginLineEdit->setPlaceholderText("Логин:");
    ui->passwordLineEdit->setPlaceholderText("Пароль:");

    connect(ui->loginButton, &QPushButton::clicked, this, &loginWindow::OnLoginButtonClicked);
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::OnLoginButtonClicked()
{
    const bool isInFile = UserData::User::IsUserExist(ui->loginLineEdit->text(), ui->passwordLineEdit->text());

    if (isInFile)
        this->accept();
    else
        QMessageBox::warning(nullptr, "Авторизация", "Неверное имя пользователя или пароль");
}
