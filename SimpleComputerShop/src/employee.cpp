#include "employee.h"

Employee::Employee()
{
    login = QString();
    password = QString();
    identificationNumber = QString();
    phoneNumber = QString();

    loginLineEdit = nullptr;
    passwordLineEdit = nullptr;
    loginDialog = nullptr;
    titleLabel = nullptr;
    nameLabel = nullptr;
    lastNameLabel = nullptr;
    positionLabel = nullptr;
    phoneNumberLabel = nullptr;
    idLabel = nullptr;
    imageLabel = nullptr;
}

Employee::~Employee()
{
    delete loginLineEdit;
    delete passwordLineEdit;
    delete titleLabel;
    delete nameLabel;
    delete lastNameLabel;
    delete positionLabel;
    delete phoneNumberLabel;
    delete idLabel;
    delete imageLabel;
    delete loginDialog;
}

QString Employee::GetLogin()
{
    return login;
}

QString Employee::GetPassword()
{
    return password;
}

QString Employee::GetIdentificationNumber()
{
    return identificationNumber;
}

QString Employee::GetPosition()
{
    return position;
}

QString Employee::GetPhoneNumber()
{
    return phoneNumber;
}

QString Employee::GetImageName()
{
    return imageName;
}

void Employee::SetLogin(QString login)
{
    this->login = login;
}

void Employee::SetPassword(QString password)
{
    this->password = password;
}

void Employee::SetIdentificationNumber(QString identificationNumber)
{
    this->identificationNumber = identificationNumber;
}

void Employee::SetPosition(QString position)
{
    this->position = position;
}

void Employee::SetPhoneNumber(QString phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Employee::SetImageName(QString imageName)
{
    this->imageName = imageName;
}

bool Employee::CheckEmployee(QString login, QString password)
{
    QFile file(EMPLOYES_FILE);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString str = in.readLine();
        QStringList substrings = str.split(";");

        if(login == substrings[LOGIN] && password == substrings[PASSWORD])
        {
            SetIdentificationNumber(substrings[ID]);
            SetLogin(substrings[LOGIN]);
            SetPassword(substrings[PASSWORD]);
            SetPosition(substrings[TITLE]);
            SetPhoneNumber(substrings[PHONE_NUMBER]);
            SetImageName(substrings[PICTURE]);
            return true;
        }
    }

    file.close();

    return false;
}

void Employee::OnLoginButtonClicked()
{
    bool isInFile = CheckEmployee(loginLineEdit->text(), passwordLineEdit->text());

    if(isInFile)
        loginDialog->accept();
    else
        QMessageBox::warning(nullptr, "Авторизация", "Неверное имя пользователя или пароль");
}

void Employee::ShowLoginDialog()
{
    loginDialog = new QDialog();
    loginDialog->setWindowTitle("Авторизация в систему");

    loginDialog->resize(300, 100);

    QLabel* imageLabel = new QLabel;
    QPixmap image(LOGIN_IMAGE);
    image = image.scaled(350, 300, Qt::KeepAspectRatio);
    imageLabel->setPixmap(image);

    QVBoxLayout* layout = new QVBoxLayout;

    QLabel* titleLabel = new QLabel("Пожалуйста, войдите в систему");
    titleLabel->setFont(QFont("Arial", 14));

    loginLineEdit = new QLineEdit;
    loginLineEdit->setPlaceholderText("Логин:");
    loginLineEdit->setFont(QFont("Arial", 14));

    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setPlaceholderText("Пароль:");
    passwordLineEdit->setFont(QFont("Arial", 14));
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton* loginButton = new QPushButton("Войти");
    loginButton->setFont(QFont("Arial", 14));

    layout->addWidget(imageLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(loginLineEdit);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    loginDialog->setLayout(layout);

    connect(loginButton, &QPushButton::clicked, this, &Employee::OnLoginButtonClicked);

    loginDialog->exec();

    delete imageLabel;
    delete titleLabel;
    delete loginButton;
    delete layout;
}

void Employee::CreateTab(QWidget* userInfoTab, QVBoxLayout* userInfoLayout)
{
    userInfoLayout = new QVBoxLayout(userInfoTab);

    QString name_and_surname = GetLogin();
    QStringList name_and_surname_list = name_and_surname.split(" ");

    titleLabel = new QLabel("ИНФОРМАЦИЯ О ПОЛЬЗОВАТЕЛЕ", userInfoTab);
    titleLabel->setFont(QFont("Arial", 35));

    nameLabel = new QLabel("Имя: " + name_and_surname_list[0], userInfoTab);
    nameLabel->setFont(QFont("Arial", 20));

    lastNameLabel = new QLabel("Фамилия: " + name_and_surname_list[1], userInfoTab);
    lastNameLabel->setFont(QFont("Arial", 20));

    positionLabel = new QLabel("Должность: " + GetPosition(), userInfoTab);
    positionLabel->setFont(QFont("Arial", 20));

    phoneNumberLabel = new QLabel("Контактный номер: " + GetPhoneNumber(), userInfoTab);
    phoneNumberLabel->setFont(QFont("Arial", 20));

    idLabel = new QLabel("ID: " + GetIdentificationNumber(), userInfoTab);
    idLabel->setFont(QFont("Arial", 20));

    imageLabel = new QLabel(userInfoTab);
    QPixmap image(EMPLOYEE_IMAGE_NAME + GetImageName());
    image = image.scaled(600, 600, Qt::KeepAspectRatio);
    imageLabel->setPixmap(image);

    userInfoLayout->addWidget(titleLabel);

    userInfoLayout->addWidget(imageLabel);

    userInfoLayout->addWidget(nameLabel);
    userInfoLayout->addWidget(lastNameLabel);
    userInfoLayout->addWidget(positionLabel);
    userInfoLayout->addWidget(phoneNumberLabel);
    userInfoLayout->addWidget(idLabel);

    userInfoLayout->setAlignment(Qt::AlignTop);
}

QDialog* Employee::GetLoginDialog()
{
    return loginDialog;
}
