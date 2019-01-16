#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>
#include <QVariant>

namespace QSqliteWrapper
{
/**
     * @brief The Parameter class represents a couple of key value.
     *
     * Used in where clause, set clause or insert statement
     */
    class Parameter
    {
    public:
        /**
         * @brief Parameter Constructor
         * @param k the key name (usually, it is the column name)
         * @param v the value of the key
         */
        Parameter(QString k, QVariant v);

        /**
         * @brief i.e : column name
         */
        QString key;

        /**
         * @brief value of the column
         */
        QVariant value;
    };
}

#endif // PARAMETER_H
