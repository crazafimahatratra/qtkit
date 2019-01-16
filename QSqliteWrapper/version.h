#ifndef VERSION_H
#define VERSION_H

#include "table.h"

using namespace QSqliteWrapper;

/**
 * @brief The Version class handles the database version of the application
 * It creates a table named **version** in the current database to keep track of changes
 */
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

    /**
     * @brief currentVersion get the current version of the database installed
     * @return the current version
     */
    int currentVersion();

    /**
     * @brief upgrade does the upgrade of the database according to the version installed \see currentVersion()
     * @param upgradeFile the filename containing the SQL statements. It is a plain file, which format is :
     * `VERSION|SQL_STATEMENT;`
        ### Example :
\code
0|CREATE TABLE version(int version);
0|CREATE TABLE users(id INTEGER);
1|ALTER TABLE users ADD name VARCHAR(128);
\endcode
     */
    void upgrade(QString upgradeFile);

    void fromRecord(QSqlRecord record);
    QList<Parameter> prepareParameters();
};

#endif // VERSION_H
