#ifndef FILE_HH
# define FILE_HH

# include "User.hh"

class File : public AModel<File>
{
private:
    static QStringList  COLUMNS;

private:
    User            m_user;

public:
    qint32          user_id;
    QString         filename;
    QString         filepath;

public:
    File(quint32 user_id_, const QString & filename_, const QString & filepath_);
    File();
    File(const QVariantList & attributes); // Should only be called in AModel (don't know how to do it..)
    virtual ~File();

    QList<QArg>     attributes() const;
    void            copyAttributes(const File & other);

    File            createFile(qint32 user_id_, const QString & filename_, const QString & filepath_);

    User&           user();
    void            user(const User & user);
};

#endif // FILE_HH
