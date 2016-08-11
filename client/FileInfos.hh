#ifndef FILEINFOS_HH
# define FILEINFOS_HH

# include <QFile>
# include <QDataStream>
# include <QVector>
# include <QCryptographicHash>

class FileInfos
{
private:
    QString               m_filepath;
    quint64               m_chunkSize;
    QVector<QByteArray>   m_chunkHashs;

public:
    FileInfos();
    FileInfos(const QString & filepath, quint64 chunkSize);

    const QVector<QByteArray>&  hashs() const;
    const QString&              filepath() const;
    quint64                     chunkSize() const;


private:
    void                        computeHashs();
};

#endif // FILEINFOS_HH
