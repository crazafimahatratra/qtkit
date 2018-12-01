#ifndef JOIN_H
#define JOIN_H

#include <QString>

namespace QSqliteWrapper
{
    class Join
    {
    public:
        Join(QString table, QString cond, QString type = "INNER");

        QString tablename, condition, type;
    };
}

#endif // JOIN_H
