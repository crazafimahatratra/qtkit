#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>
#include <QVariant>

namespace QSqliteWrapper
{
    class Parameter
    {
    public:
        Parameter(QString k, QVariant v);
        QString key;
        QVariant value;

        template<typename T>
        T add(T a, T b);
    };
}

#endif // PARAMETER_H
