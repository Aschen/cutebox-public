#include "Database.hh"

#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>

#include "Debug.hh"

Database::Database()
{
}

Database::~Database()
{
    if (m_db.isOpen())
        m_db.close();
}

bool Database::initDatabase(const QString & databaseName)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName(databaseName);

    if ( ! m_db.open())
    {
        DEBUG("Unable to open database", true);
        return false;
    }

    return true;
}

bool Database::createTables()
{
    using Table = QPair<QString, QString>;

    bool            ret = true;
    QList<Table>    tables;
    QStringList     existingTables = m_db.tables();

    tables.push_back(Table("users", "(id integer primary key, email varchar, password varchar)"));
    tables.push_back(Table("files", "(id integer primary key, user_id integer, filename varchar, filepath varchar)"));

    QSqlQuery       q;

    for (const Table & table : tables)
    {
        if (existingTables.contains(table.first))
            continue;

        if ( ! q.exec ("create table " + table.first + table.second))
        {
            DEBUG("Query error :" << q.lastError().text(), true);
            ret = false;
        }
    }

    return ret;
}

