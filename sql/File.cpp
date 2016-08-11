#include "File.hh"

#include <QStringList>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

QStringList File::COLUMNS = { "user_id", "filename", "filepath" };

File::File(quint32 user_id_, const QString & filename_, const QString & filepath_)
    : AModel<File>("files", File::COLUMNS),
      user_id(user_id_),
      filename(filename_),
      filepath(filepath_)
{
}

File::File()
    : AModel<File>("files", File::COLUMNS),
      user_id(-1),
      filename(""),
      filepath("")
{
}

File::File(const QVariantList & attributes)
    : AModel<File>("files", File::COLUMNS),
      user_id(attributes[1].toInt()),
      filename(attributes[2].toString()),
      filepath(attributes[3].toString())
{
    m_id = attributes[0].toInt();
    m_persisted = true;
}

File::~File()
{
}

QList<QArg> File::attributes() const
{
    return { QArg("user_id", user_id), QArg("filename", filename), QArg("filepath", filepath) };
}

void File::copyAttributes(const File & other)
{
    *this = other;
}

File File::createFile(qint32 user_id_, const QString & filename_, const QString & filepath_)
{
    return File().create({ QArg("user_id", user_id_), QArg("filename", filename_), QArg("filepath", filepath_) });
}

User &File::user()
{
    // Lazy loading of user
    if ( ! m_user.persisted())
    {
        m_user = User().find(user_id);
    }

    return m_user;
}

void File::user(const User & user)
{
    // Don't set user if he is not persisted in db
    if (user.persisted())
    {
        m_user = user;
        user_id = user.id();
    }
}

