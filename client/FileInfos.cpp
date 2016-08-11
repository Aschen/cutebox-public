#include "FileInfos.hh"

#include "Debug.hh"

FileInfos::FileInfos()
{
}

FileInfos::FileInfos(const QString & filepath, quint64 chunkSize)
    : m_filepath(filepath),
      m_chunkSize(chunkSize)
{
    computeHashs();
}

const QVector<QByteArray> &FileInfos::hashs() const
{
    return m_chunkHashs;
}

const QString &FileInfos::filepath() const
{
    return m_filepath;
}

quint64 FileInfos::chunkSize() const
{
    return m_chunkSize;
}

void FileInfos::computeHashs()
{
    QFile       file(m_filepath);
    QByteArray  chunk;

    if ( ! file.open(QIODevice::ReadOnly))
    {
        DEBUG("FileInfos::computeHashs() : Can't open file" << m_filepath, true);
        return;
    }

    while ( ! file.atEnd())
    {
        chunk = file.read(m_chunkSize);
        m_chunkHashs.push_back(QCryptographicHash::hash(chunk, QCryptographicHash::Md5));
    }
}

