#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QMap>
#include <QVariant>
#include <QList>
#include <QSqlRecord>
#include <QSqlQuery>

#include "dbconnector.h"
#include "parameter.h"
#include "join.h"


namespace QSqliteWrapper
{
    class Table
    {
    public:
        Table(QString name);
        virtual ~Table();
        virtual QString pkName() = 0;
        virtual QVariant pkValue() = 0;
        virtual void setPkValue(QVariant) = 0;
        virtual void fromRecord(QSqlRecord record) = 0;
        virtual QList<Parameter> prepareParameters() = 0;

        Table *select(QString columns = "*");
        Table *where(QString key, QVariant value, QString op="AND");
        Table *order(QString orderby);
        Table *groupBy(QString group);
        Table *join(QString table, QString condition, QString type="INNER");
        Table *startGroup(QString op="AND");
        Table *endGroup();
        QVariant insert();
        void update();
        void remove();
        bool exists();

        QString sql();
        QList<QSqlRecord> exec();
        QList<QSqlRecord> exec(QString sql);
        QList<QSqlRecord> exec(QString sql, QList<Parameter> parameters);

        QMap<QString, QVariant> boundValues;

        template<class T>
        QList<T *> get();

        template<class T>
        static QList<T *> getAll();

        template<class T>
        static T *findById(QVariant id);

    private:
        enum queryMode {
            NONE,
            SELECT,
            INSERT,
            UPDATE,
            DELETE
        };

        QString m_name;
        QStringList m_selectClause;
        QList<Parameter> m_whereClause;
        QList<Parameter> m_insertValues;
        QList<Parameter> m_updateValues;
        QList<Join> m_joins;
        QStringList m_orderClause;
        QStringList m_groupClause;
        queryMode mode;
        bool start = true;

        QString selectClause();
        QString fromClause();
        QString joinClause();
        QString whereClause();
        QString orderClause();
        QString groupClause();
        QString insertClause();
        QString updateClause();
        QString deleteClause();

        QString _whereClause = "";
    };

    template<class T>
    QList<T *> Table::get()
    {
        QList<QSqlRecord> records = this->exec();
        QList<T *> list;
        for(int i = 0; i < records.length(); i++)
        {
            T *row = (new T);
            row->fromRecord(records[i]);
            list.append(row);
        }
        return list;
    }

    template<class T>
    T *Table::findById(QVariant id)
    {
        T t;
        t.select()->where(t.pkName() + "=", id);
        QList<QSqlRecord> rows = t.exec();
        if(rows.count() == 0)
            return nullptr;
        T *row = (new T);
        row->fromRecord(rows[0]);
        return row;
    }

    template<class T>
    QList<T *> Table::getAll()
    {
        T model;
        QList<QSqlRecord> records = model.exec();
        QList<T *> list;
        for(int i = 0; i < records.length(); i++)
        {
            T *row = (new T);
            row->fromRecord(records[i]);
            list.append(row);
        }
        return list;
    }
}

#endif // TABLE_H
