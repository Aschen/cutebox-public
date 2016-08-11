#include "FileChange.hh"

#include <QFile>

#include "Debug.hh"

FileChange::FileChange()
{
}

FileChange::FileChange(const QString & filepath, quint64 offset)
    : m_offset(offset),
      m_filepath(filepath)
{
    DEBUG("FileChange::FileChange() : File" << filepath << " offset" << offset, true);
    QFile   file(filepath);

    if ( ! file.open(QIODevice::ReadWrite))
    {
        DEBUG("FileChange::FileChange() : Unable to open file" << filepath, true);
    }
    else if ( ! file.seek(m_offset))
    {
        DEBUG("FileChange::FileChange() : Unable to seek file" << filepath << " to offset" << m_offset, true);
    }
    else
    {
        m_filesize = file.size();
        m_data = file.readAll();
    }
}

quint64 FileChange::offset() const
{
    return m_offset;
}

const QByteArray &FileChange::data() const
{
    return m_data;
}

const QString &FileChange::filepath() const
{
    return m_filepath;
}

quint64 FileChange::filesize() const
{
    return m_filesize;
}

