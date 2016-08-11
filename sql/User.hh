#ifndef USER_HH
# define USER_HH

# include <QString>
# include <QVariantList>

# include "AModel.hpp"

class User : public AModel<User>
{
public:
    static QStringList  COLUMNS;

public:
    QString         email;
    QString         password;

public:
    User(const QString & email_, const QString & password_);
    User();
    User(const User & other);
    User(const QVariantList & attributes); // Should only be called in AModel (don't know how to do it..)
    virtual ~User();

    QList<QArg>     attributes() const;
    void            copyAttributes(const User & other);

    User            createUser(const QString & email_, const QString & password_) const;
};

Q_DECLARE_METATYPE(User)

#endif // USER_HH
