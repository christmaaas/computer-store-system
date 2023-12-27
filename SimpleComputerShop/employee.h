#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "component.h"

#define EMPLOYES_FILE "./holders/employes.txt"
#define LOGIN_IMAGE "./holders/images/login_img.jpg"
#define EMPLOYEE_IMAGE_NAME "./holders/images/"

#define ID 0
#define LOGIN 1
#define PASSWORD 2
#define TITLE 3
#define PHONE_NUMBER 4
#define PICTURE 5

class Employee : public QObject
{
    Q_OBJECT

private:
    QString login;
    QString password;
    QString identificationNumber;
    QString phoneNumber;
    QString position;
    QString imageName;

    QLineEdit* loginLineEdit;
    QLineEdit* passwordLineEdit;

    QDialog* loginDialog;

    QLabel* titleLabel;
    QLabel* nameLabel;
    QLabel* lastNameLabel;
    QLabel* positionLabel;
    QLabel* phoneNumberLabel;
    QLabel* idLabel;
    QLabel* imageLabel;

private slots:
    void OnLoginButtonClicked();

public:
    Employee();
    ~Employee();

    void CreateTab(QWidget* userInfoTab, QVBoxLayout* userInfoLayout);
    void ShowLoginDialog();
    bool CheckEmployee(QString login, QString password);
    void SetLogin(QString);
    void SetPassword(QString);
    void SetIdentificationNumber(QString);
    void SetPosition(QString);
    void SetImageName(QString);
    void SetPhoneNumber(QString);
    QString GetLogin();
    QString GetPassword();
    QString GetIdentificationNumber();
    QString GetPosition();
    QString GetImageName();
    QString GetPhoneNumber();
    QDialog* GetLoginDialog();
};

#endif // EMPLOYEE_H
