#ifndef AMODEL_HH
# define AMODEL_HH

# include <QStringList>
# include <QTest>
# include <QPair>
# include <QVariant>
# include <QSqlQuery>
# include <QSqlError>
# include <QSqlRecord>
# include <initializer_list>

# include "Debug.hh"

/**
 * Typedef on QPair used for argumentList => syntaxic sugar
 */
using QArg = QPair<QString, QVariant>;

template<typename T>
class AModel
{
protected:
    QString             m_tableName;
    QStringList         m_columns;
    qint32              m_id = -1;
    bool                m_persisted = false;

public:
    virtual QList<QArg> attributes() const = 0;
    virtual void        copyAttributes(const T & other) = 0;

public:
    /**
     * @brief Base of every model
     * @param table Name of the table
     * @param columns List of columns in the table
     */
    AModel(const QString & table, const QStringList & columns)
        : m_tableName(table),
          m_columns(columns)
    {
    }
    virtual ~AModel() { }

    /**
     * @brief Create a new model, save it in database and return it. Return an invalid model if fail
     * @param queryArguments Value to construct the model
     * @return model The newly created model
     */
    T create(const QList<QArg> & queryArguments) const
    {
        QSqlQuery   q;
        QString     insertQuery;
        QStringList columns;
        QStringList values;

        for (const QArg & queryArg : queryArguments)
        {
            columns += queryArg.first;
            values += QString(":%1").arg(queryArg.first);
        }

        insertQuery = QString("INSERT INTO %1(%2) values(%3)")
                      .arg(m_tableName, columns.join(", "), values.join(", "));

        q.prepare(insertQuery);

        for (const QArg & queryArg : queryArguments)
        {
            q.bindValue(QString(":%1").arg(queryArg.first), queryArg.second);
        }

        if ( ! q.exec())
        {
            DEBUG("Unable to execute insertion query :" << q.lastError().text(), true);
            return T();
        }

        QVariant    variant = q.lastInsertId();

        if ( ! q.isActive())
        {
            return T();
        }

        return T().findBy({ QArg("id", variant) });
    }

    /**
     * @brief Find a model by his id. Return an invalid model if fail
     * @param id Model uniq id
     * @return The model
     */
    T find(qint32 id)
    {
        QSqlQuery   q;
        QString     selectQuery;

        selectQuery = QString("SELECT * FROM %1 WHERE id = :id LIMIT 1").arg(m_tableName);

        if ( ! q.prepare(selectQuery))
        {
            DEBUG("Unable to prepare selection query :" << q.lastError().text(), true);
            return T();
        }

        q.bindValue(":id", id);

        if ( ! q.exec() || ! q.isSelect())
        {
            DEBUG("Unable to execute selection query :" << q.lastError().text(), true);
            return T();
        }

        if ( ! q.first())
        {
            return T();
        }

        return T().buildFromQuery(q);
    }

    /**
     * @brief Find a model by columns value. Return an invalid model if fail
     * @param queryArguments List of <column, value> couple
     * @return The model
     */
    T findBy(const QList<QArg> & queryArguments) const
    {
        QSqlQuery   q;
        QString     selectQuery;
        QStringList selects;

        selectQuery = QString("SELECT * FROM %1 WHERE ").arg(m_tableName);

        for (const QArg & queryArg : queryArguments)
        {
            selects += QString("%1 = :%2").arg(queryArg.first, queryArg.first);
        }

        selectQuery += selects.join(" AND ");
        selectQuery += " LIMIT 1";

        q.prepare(selectQuery);

        for (const QArg & queryArg : queryArguments)
        {
            q.bindValue(QString(":%1").arg(queryArg.first), queryArg.second);
        }

        if ( ! q.exec() || ! q.isSelect())
        {
            DEBUG("Unable to execute findBy query :" << q.lastError().text(), true);
            return T();
        }

        if ( ! q.first())
        {
            return T();
        }

        return T().buildFromQuery(q);
    }

    /**
     * @brief Find a collection of models matching columns values
     * @param queryArguments List of <column, value> couple
     * @return A list of matching models
     */
    QList<T> where(const QList<QArg> & queryArguments) const
    {
        QSqlQuery   q;
        QString     whereQuery;
        QStringList wheres;
        QList<T>    results;

        whereQuery = QString("SELECT * FROM %1 WHERE ").arg(m_tableName);

        for (const QArg & queryArg : queryArguments)
        {
            wheres += QString("%1 = :%2").arg(queryArg.first, queryArg.first);
        }

        whereQuery += wheres.join(" AND ");

        q.prepare(whereQuery);

        for (const QArg & queryArg : queryArguments)
        {
            q.bindValue(QString(":%1").arg(queryArg.first), queryArg.second);
        }

        if ( ! q.exec() || ! q.isSelect())
        {
            DEBUG("Unable to execute where query :" << q.lastError().text(), true);
            return results;
        }

        while (q.next())
        {
            results.push_back(T().buildFromQuery(q));
        }

        return results;
    }

    /**
     * @brief Delete a model from database
     * @param id Uniq id of the model to delete
     */
    void remove(qint32 id)
    {
        QSqlQuery   q;
        QString     deleteQuery;

        deleteQuery = QString("DELETE FROM %1 WHERE id = :id").arg(m_tableName);

        if ( ! q.prepare(deleteQuery))
        {
            DEBUG("Unable to prepare deletion query :" << q.lastError().text(), true);
            return;
        }

        q.bindValue(":id", id);

        if ( ! q.exec())
        {
            DEBUG("Unable to execute deletion query :" << q.lastError().text(), true);
            return;
        }

        m_id = -1;
        m_persisted = false;

        return;
    }

    /**
     * @brief Delete the current model in database
     */
    void remove()
    {
        if (m_persisted)
            remove(m_id);
    }

    /**
     * @brief Remove all models from the table
     */
    void removeAll()
    {
        QSqlQuery   q;
        QString     deleteQuery;

        deleteQuery = QString("DELETE FROM %1").arg(m_tableName);

        if ( ! q.prepare(deleteQuery))
        {
            DEBUG("Unable to prepare deletion query :" << q.lastError().text(), true);
            return;
        }

        if ( ! q.exec())
        {
            DEBUG("Unable to execute deletion query :" << q.lastError().text(), true);
            return;
        }

        return;
    }

    /**
     * @brief Return the number of model present in the table
     * @return Number of models present in table
     */
    quint32 count()
    {
        QSqlQuery   q;
        QString     countQuery;

        countQuery = QString("SELECT COUNT(*) FROM %1").arg(m_tableName);

        if ( ! q.prepare(countQuery))
        {
            DEBUG("Unable to prepare count query :" << q.lastError().text(), true);
            return -1;
        }

        if ( ! q.exec() || ! q.isActive() || ! q.first())
        {
            DEBUG("Unable to execute count query :" << q.lastError().text(), true);
            return -1;
        }

        return q.value(0).toInt();
    }

    /**
     * @brief Save the current model. Create it if it doesn't exist in db or update existing model.
     * @return true if succeed, false otherwise
     */
    bool save()
    {
        // Select before to know if id still exist in db ? (remove(quint32) problem)
        if (m_persisted)
        {
            // If update fail, user is not persisted in database
            m_persisted = this->update(this->attributes());

            return m_persisted;
        }
        else
        {
            this->copyAttributes(T().create(this->attributes()));

            return m_persisted;
        }
    }

    /**
     * @brief Return true if the model is persisted in database
     * @return true or false
     */
    bool persisted() const
    {
        return m_persisted;
    }

    qint32 id() const
    {
        return m_id;
    }

protected:

    /**
     * @brief Update model in database with couples of <column, value> passed in parameter.
     * @param queryArguments List of couple <column, value> to update
     * @return true if succeed, false otherwise
     */
    bool update(const QList<QArg> & queryArguments)
    {
        QSqlQuery   q;
        QString     updateQuery;
        QStringList values;

        for (const QArg & queryArg : queryArguments)
        {
            values += QString("%1 = :%1").arg(queryArg.first);
        }

        updateQuery = QString("UPDATE %1 SET %2 WHERE id = :id")
                      .arg(m_tableName,
                           values.join(", "));

        if ( ! q.prepare(updateQuery))
        {
            DEBUG("Unable to prepare update query :" << q.lastError().text(), true);
            return false;
        }

        for (const QArg & queryArg : queryArguments)
        {
            q.bindValue(QString(":%1").arg(queryArg.first), queryArg.second);
        }

        q.bindValue(":id", m_id);

        if ( ! q.exec() || ! q.isActive())
        {
            DEBUG("Unable to execute update query :" << q.lastError().text(), true);
            return false;
        }

        return true;
    }

private:

    /**
     * @brief Retrieve attributes list from query and create a new model
     * @param q current QSqlQuery
     * @return <T> the new model
     */
    T buildFromQuery(QSqlQuery & q) const
    {
        QVariantList    values;
        QStringList     columns = m_columns;

        values.push_back(q.value(q.record().indexOf("id")));

        for (const QString & column : columns)
        {
            qint32  index = q.record().indexOf(column);
            values.push_back(q.value(index));
        }
        return T(values);
    }
};

#endif // AMODEL_HH
