#include "user.h"

#include <QFile>
#include <QTextStream>

static constexpr const char employersFile[] = "./resources/employes.txt";

namespace UserData
{
    bool User::IsUserExist(const QString& login, const QString& password) noexcept
    {
        QFile file(employersFile);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        enum SubstringTokens
        {
            Id = 0,
            Login,
            Password,
            Title,
            PhoneNumber,
            Picture,
        };

        while (!in.atEnd())
        {
            QString str = in.readLine();
            QStringList substrings = str.split(";");

            if (login == substrings[Login] && password == substrings[Password])
            {
                SetId(substrings[Id]);
                SetLogin(substrings[Login]);
                SetPassword(substrings[Password]);
                SetPosition(substrings[Title]);
                SetPhoneNumber(substrings[PhoneNumber]);
                SetImageName(substrings[Picture]);

                file.close();

                return true;
            }
        }

        file.close();

        return false;
    }
}