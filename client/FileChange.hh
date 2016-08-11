#ifndef FILECHANGE_HH
# define FILECHANGE_HH

# include <QByteArray>
# include <QString>

class FileChange
{
private:
    quint64             m_offset;
    QString             m_filepath;
    quint64             m_filesize;
    QByteArray          m_data;

public:
    FileChange();
    FileChange(const QString & filepath, quint64 offset);

    quint64             offset() const;
    const QByteArray    &data() const;
    const QString       &filepath() const;
    quint64             filesize() const;
};

#endif // FILECHANGE_HH
