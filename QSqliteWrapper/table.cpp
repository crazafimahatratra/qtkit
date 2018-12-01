#include "table.h"
#include <QDebug>
#include <QSqlField>

using namespace QSqliteWrapper;
Table::Table(QString name):
    m_name(name),
    mode(NONE)
{
}

Table::~Table()
{

}

Table *Table::select(QString columns)
{
    this->mode = Table::SELECT;
    m_selectClause << columns;
    return this;
}

Table *Table::where(QString key, QVariant value)
{
    m_whereClause.append(Parameter(key, value));
    return this;
}

Table *Table::order(QString orderby)
{
    m_orderClause.append(orderby);
    return this;
}

Table *Table::join(QString table, QString condition, QString type)
{
    m_joins.append(Join(table, condition, type));
    return this;
}

QVariant Table::insert()
{
    this->mode = Table::INSERT;
    this->m_insertValues = this->prepareParameters();
    QList<QSqlRecord> recs = this->exec(this->sql(), this->m_insertValues);
    if(recs.length())
    {
        this->setPkValue(recs[0].value("id"));
        return recs[0].value("id");
    }
    return QVariant();
}

void Table::update()
{
    this->mode = Table::UPDATE;
    if(this->m_whereClause.count() == 0)
        this->where(this->pkName() + "=", this->pkValue());
    this->m_updateValues = this->prepareParameters();
    this->exec(this->sql(), this->m_updateValues);
}

void Table::remove()
{
    this->mode = Table::DELETE;
    this->where(this->pkName() + "=", this->pkValue());
    this->exec(this->sql());
}

bool Table::exists()
{
    this->select("count(*)")->where(this->pkName() + "=", this->pkValue());
    QList<QSqlRecord> records = this->exec();
    if(records.length() > 0)
        return records[0].value(0).toInt() > 0;
    return false;
}

QString Table::sql()
{
    if(this->mode == SELECT || this->mode == NONE)
        return this->selectClause()
                + this->fromClause()
                + this->joinClause()
                + this->whereClause()
                + this->orderClause();

    if(this->mode == INSERT)
        return this->insertClause();
    if(this->mode == UPDATE)
        return this->updateClause()
                + this->whereClause();
    if(this->mode == DELETE)
        return this->deleteClause()
                + this->whereClause();
    return "";
}

QList<QSqlRecord> Table::exec()
{
    return this->exec(this->sql());
}

QList<QSqlRecord> Table::exec(QString sql)
{
    QList<QSqlRecord> records;
    QSqlQuery query = DbConnector::getQuery();

    if(!query.prepare(sql))
    {
        qDebug() << "EXEC : " << query.lastError().text()  << ":" << sql;
    }
    for(int i = 0; i < m_whereClause.count(); i++)
    {
        query.bindValue(QString(":where_%1").arg(i), m_whereClause[i].value);
    }
    if(!query.exec())
    {
        qDebug() << "EXEC : " << query.lastError().text()  << ":" << sql;
        return records;
    }
    boundValues = query.boundValues();
    while(query.next()) { records.append(query.record());}
    return records;
}

QList<QSqlRecord> Table::exec(QString sql, QList<Parameter> parameters)
{
    boundValues.clear();
    QList<QSqlRecord> records;
    QSqlQuery query = DbConnector::getQuery();
    if(!query.prepare(sql))
    {
        qDebug() << "EXEC : " << query.lastError().text()  << ":" << sql;
    }
    for(int i = 0; i < parameters.count(); i++)
    {
        query.bindValue(QString(":param_%1").arg(i), parameters[i].value);
    }
    for(int i = 0; i < m_whereClause.count(); i++)
    {
        query.bindValue(QString(":where_%1").arg(i), m_whereClause[i].value);
    }
    if(!query.exec())
    {
        qDebug() << "EXEC : " << query.lastError().text()  << ":" << sql;
        return records;
    }
    boundValues = query.boundValues();
    if(mode == INSERT)
    {
        QSqlRecord rec;
        QVariant id = query.lastInsertId();
        rec.append(QSqlField("id"));
        rec.setValue("id", id);
        records.append(rec);
        return records;
    }
    while(query.next()) { records.append(query.record());}
    return records;
}

QString Table::selectClause()
{
    if(m_selectClause.length() == 0)
        m_selectClause << "*";
    return "SELECT " + m_selectClause.join(", ");
}

QString Table::fromClause()
{
    return " FROM " + m_name;
}

QString Table::joinClause()
{
    if(m_joins.empty())
        return "";
    QStringList joins;
    for(int i = 0; i < m_joins.count(); i++)
    {
        joins << QString(" %1 JOIN %2 ON (%3)").arg(m_joins[i].type, m_joins[i].tablename, m_joins[i].condition);
    }
    return joins.join(" ");
}

QString Table::whereClause()
{
    if(m_whereClause.isEmpty())
        return "";
    QStringList sql;
    int index = 0;
    for(int i = 0; i < m_whereClause.count(); i++)
    {
        sql << m_whereClause[i].key + QString(":where_%1").arg(index++);
    }
    if(sql.isEmpty())
        return "";
    return " WHERE " + sql.join(" AND ");
}

QString Table::orderClause()
{
    if(m_orderClause.isEmpty())
        return "";
    return " ORDER BY " + m_orderClause.join(", ");
}

QString Table::insertClause()
{
    QStringList keys, values;
    for(int i = 0; i < m_insertValues.count(); i++)
    {
        keys << m_insertValues[i].key;
        values << QString(":param_%1").arg(i);
    }
    QString s = QString("INSERT INTO %1(%2) VALUES(%3)").arg(m_name).arg(keys.join(", ")).arg(values.join(", "));
    return s;
}

QString Table::updateClause()
{
    QStringList values;
    for(int i = 0; i < m_updateValues.count(); i++)
    {
        values << QString("%1 = :param_%2").arg(m_updateValues[i].key).arg(i);
    }
    QString s = QString("UPDATE %1 SET %2").arg(m_name).arg(values.join(", "));
    return s;
}

QString Table::deleteClause()
{
    return QString("DELETE FROM %1").arg(m_name);
}
