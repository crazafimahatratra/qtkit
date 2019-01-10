#ifndef VERSION_H
#define VERSION_H

#include "table.h"

using namespace QSqliteWrapper;
class Version : public Table
{
public:
    Version();
    int version;
    QString pkName()
    {
        return "version";
    }
    QVariant pkValue()
    {
        return this->version;
    }
    void setPkValue(QVariant v)
    {
        this->version = v.toInt();
    }
    int currentVersion();
    void upgrade(QString upgradeFile);

    void fromRecord(QSqlRecord record);
    QList<Parameter> prepareParameters();
};

#endif // VERSION_H
