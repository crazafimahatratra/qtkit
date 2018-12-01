#include "join.h"

namespace QSqliteWrapper
{
    Join::Join(QString table, QString cond, QString type):
        tablename(table),
        condition(cond),
        type(type)
    {

    }
}
