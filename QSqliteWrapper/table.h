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

/**
 * \package QSqliteWrapper holds wrapper objects to the qt sql library.
 * @author Christophe RAZAFIMAHATRATRA
 * @date 2019 January
 */
namespace QSqliteWrapper
{
    /**
     * @brief The Table class represents an sql physical table
     * @author Christophe RAZAFIMAHATRATRA
     * @date 2019 January
     */
    class Table
    {
    public:
        /**
         * @brief Table Constructor
         * @param name is the name of the physical table
         */
        Table(QString name);
        virtual ~Table();

        /**
         * @brief pkName is the name of primary key of the table
         * @return primary key name
         */
        virtual QString pkName() = 0;

        /**
         * @brief pkValue is the value of the primary key
         * @return the value of the primary key
         */
        virtual QVariant pkValue() = 0;

        /**
         * @brief setPkValue sets the value of primary key
         */
        virtual void setPkValue(QVariant) = 0;

        /**
         * @brief fromRecord maps records to the members of the class
         * @param record an QSqlRecord object
         */
        virtual void fromRecord(QSqlRecord record) = 0;

        /**
         * @brief prepareParameters maps the members to the Parameter object
         * @return
         */
        virtual QList<Parameter> prepareParameters() = 0;

        /**
         * @brief select generates a select clause
         * @param columns holds the columns to be selected
         * @return the Table object back
         */
        Table *select(QString columns = "*");

        /**
         * @brief where generates a where clause.
         * @param key the column name (or a sql expression)
         * @param value the value of the column
         * @param op the operator. Can be `AND` or `OR`
         * @return the Table object
         */
        Table *where(QString key, QVariant value, QString op="AND");

        /**
         * @brief order generates an order by clause
         * @param orderby the order clause
         * @return the Table object
         */
        Table *order(QString orderby);

        /**
         * @brief groupBy generates a group by clause
         * @param group : the group by clause
         * @return the Table object
         */
        Table *groupBy(QString group);

        /**
         * @brief join Adds a join clause
         * @param table the table name
         * @param condition the condition
         * @param type the join type @see Join
         * @return the Table object
         */
        Table *join(QString table, QString condition, QString type="INNER");

        /**
         * @brief startGroup starts a group for where condition
         * @param op the operator to be used **AND** or **OR**
         * @return the Table object
         */
        Table *startGroup(QString op="AND");

        /**
         * @brief endGroup Ends the current group in a where clause
         * @return the Table object
         */
        Table *endGroup();

        /**
         * @brief insert Creates an insert statement
         * @return the last inserted id
         */
        QVariant insert();

        /**
         * @brief update Creates an update statement
         */
        void update();

        /**
         * @brief remove Creates a delete statement
         */
        void remove();

        /**
         * @brief exists Checks if a record already exists.
         * It uses the value of Table::pkValue()
         * @return
         */
        bool exists();

        /**
         * @brief sql Generates the final sql to be executed
         * @return the SQL statement
         */
        QString sql();

        /**
         * @brief exec Executes the SQL returned by sql() statement
         * @return
         */
        QList<QSqlRecord> exec();

        /**
         * @brief exec Executes an arbitrary SQL statement
         * @param sql : the SQL to be executed
         * @return a list of QSqlRecord returned by the sql parameter (if any)
         */
        QList<QSqlRecord> exec(QString sql);

        /**
         * @brief exec Executes an arbitrary SQL statement with parameters
         * @param sql : the SQL to be executed
         * @param parameters : some parameters
         * @return a list of QSqlRecord returned by the sql parameter (if any)
         */
        QList<QSqlRecord> exec(QString sql, QList<Parameter> parameters);

        /**
         * @brief Values bound when calling where()
         */
        QMap<QString, QVariant> boundValues;

        template<class T>
        /**
         * @brief executes the select statement
         * @return a list of T
         */
        QList<T *> get();

        template<class T>
        /**
         * @brief getAll get all rows (SELECT * FROM tablename)
         * @return  a list of T
         */
        static QList<T *> getAll();

        template<class T>
        /**
         * @brief findById select one row (SELECT * FROM tablename WHERE pkname=id)
         * @param id : to be compared with pkname
         * @return a T
         */
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
