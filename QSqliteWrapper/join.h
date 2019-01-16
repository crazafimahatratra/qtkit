#ifndef JOIN_H
#define JOIN_H

#include <QString>

namespace QSqliteWrapper
{
/**
     * @brief The Join class is used to represent the JOIN clause of an SQL statement
     */
    class Join
    {
    public:
        /**
         * @brief Join Constructor
         * @param table the table name to be joint to
         * @param cond the condition
         * @param type is the type of join. Could be `INNER|OUTTER|LEFT|RIGHT`
         */
        Join(QString table, QString cond, QString type = "INNER");

        /**
         * @brief the name of the table to be joint
         *
         */
        QString tablename;

        /**
         * @brief condition of join
         */
        QString condition;

        /**
         * @brief type of join
         */
        QString type;
    };
}

#endif // JOIN_H
