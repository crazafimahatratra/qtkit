#include "parameter.h"

using namespace QSqliteWrapper;

Parameter::Parameter(QString k, QVariant v):
    key(k),
    value(v)
{

}
