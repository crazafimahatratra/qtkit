#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace QSqliteWrapper
{
/**
     * @brief The DbConnector class
     * base class for connection to Sqlite Database
     */
    class DbConnector
    {
        public:
            DbConnector();
            ~DbConnector();
            /**
             * @brief executes a sql query
             */
            void execute(QString);

            /**
             * @brief getQuery gets an instance of a QSqlQuery object
             * @return
             */
            static QSqlQuery getQuery();

            /**
             * @brief getDbName get the database name
             * @return the database name
             */
            static QString getDbName();

            /**
             * @brief getInstance get an instance of DbConnector
             * @return
             */
            static DbConnector *getInstance();

            /**
             * @brief close Closes the connection
             */
            static void close();

            /**
             * @brief setDbName Sets the database name (or path)
             * @param name the database name
             */
            static void setDbName(QString name);

            /**
             * @brief useAppData whether to use AppData path or not
             * @param use if true, use the AppData path
             */
            static void useAppData(bool use = false);
        private:
            QSqlDatabase database;
            static QString m_dbname;
            static bool m_useAppData;
            static DbConnector *instance;
    };
}


#endif // DBCONNECTOR_H
