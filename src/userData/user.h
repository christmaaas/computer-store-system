#ifndef USER_H
#define USER_H

#include <QString>

namespace UserData
{
    class User final
    {
    public:
        [[nodiscard]] static inline void SetId(const QString& id) noexcept { User::id = id; }
        [[nodiscard]] static inline void SetLogin(const QString& login) noexcept { User::login = login; }
        [[nodiscard]] static inline void SetPassword(const QString& password) noexcept { User::password = password; }
        [[nodiscard]] static inline void SetPosition(const QString& position) noexcept { User::position = position; }
        [[nodiscard]] static inline void SetPhoneNumber(const QString& phoneNumber) noexcept { User::phoneNumber = phoneNumber; }
        [[nodiscard]] static inline void SetImageName(const QString& imageName) noexcept { User::imageName = imageName; }

        [[nodiscard]] static inline const QString& GetId() noexcept { return id; }
        [[nodiscard]] static inline const QString& GetLogin() noexcept { return login; }
        [[nodiscard]] static inline const QString& GetPassword() noexcept { return password; }
        [[nodiscard]] static inline const QString& GetPosition() noexcept { return position; }
        [[nodiscard]] static inline const QString& GetPhoneNumber() noexcept { return phoneNumber; }
        [[nodiscard]] static inline const QString& GetImageName() noexcept { return imageName; }

        [[nodiscard]] static bool IsUserExist(const QString& login, const QString& password) noexcept;

    private:
        static inline QString id;
        static inline QString login;
        static inline QString password;
        static inline QString position;
        static inline QString phoneNumber;
        static inline QString imageName;
    };
}

#endif // USER_H