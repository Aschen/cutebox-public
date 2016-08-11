#include "User.hh"

#include <QStringList>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

QStringList User::COLUMNS = { "email", "password" };

User::User(const QString & email_, const QString & password_)
    : AModel<User>("users", User::COLUMNS),
      email(email_),
      password(password_)
{
}

User::User()
    : AModel<User>("users", User::COLUMNS),
      email(""),
      password("")
{
}

User::User(const User & other)
    : AModel<User>("users", User::COLUMNS),
      email(other.email),
      password(other.password)
{
    m_id = other.id();
}

User::User(const QVariantList & attributes)
    : AModel<User>("users", User::COLUMNS),
      email(attributes[1].toString()),
      password(attributes[2].toString())
{
    m_id = attributes[0].toInt();
    m_persisted = true;
}

User::~User()
{
}

QList<QArg> User::attributes() const
{
    return { QArg("email", email), QArg("password", password) };
}

void User::copyAttributes(const User & other)
{
    *this = other;
}

User User::createUser(const QString & email_, const QString & password_) const
{
    return User().create({ QArg("email", email_), QArg("password", password_) });
}
