#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace QSqliteWrapper
{
    class DbConnector
    {
        public:
            DbConnector();
            ~DbConnector();
            void execute(QString);
            static QSqlQuery getQuery();
            static QString getDbName();
            static DbConnector *getInstance();
            static void close();
            static void setDbName(QString name);
            static void useAppData(bool use = false);
        private:
            QSqlDatabase database;
            static QString m_dbname;
            static bool m_useAppData;
            static DbConnector *instance;
    };
}


#endif // DBCONNECTOR_H
