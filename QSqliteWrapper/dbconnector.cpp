#include "dbconnector.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QtWidgets/QMessageBox>

using namespace QSqliteWrapper;

DbConnector* DbConnector::instance = NULL;
bool DbConnector::m_useAppData = false;
QString DbConnector::m_dbname = "";

DbConnector::DbConnector()
{
    database = QSqlDatabase::addDatabase("QSQLITE", "mydb");
    QString path;
    if(DbConnector::m_useAppData)
    {
        path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
        QDir dir(path);
        if(!dir.exists())
        {
            if(!dir.mkpath(path))
            {
                qDebug() << QString("Error while creating path\n%1").arg(path);
                exit(EXIT_FAILURE);
            }
        }
        path += "/" + DbConnector::m_dbname;
    }
    else
    {
        path = DbConnector::m_dbname;
    }
    qDebug() << "path is" << path;
    database.setDatabaseName(path);
    if(!database.open())
    {
        qDebug() << QString("Error while opening database : \n%1").arg(database.lastError().text());
        exit(EXIT_FAILURE);
    }
    QSqlQuery query(database);
    if(!query.exec("PRAGMA foreign_keys=ON;"))
    {
        qDebug() << query.lastError().text();
    }
    query.clear();
}

DbConnector::~DbConnector()
{
    database.commit();
    database.close();
    instance = NULL;
}

void DbConnector::execute(QString sql)
{
    QSqlQuery query(database);
    if(!query.exec(sql))
    {
        qDebug() << query.lastError().text();
    }
    query.clear();
}

DbConnector *DbConnector::getInstance()
{
    if(instance == NULL)
    {
        instance = new DbConnector();
    }
    return instance;
}

QSqlQuery DbConnector::getQuery()
{
    QSqlQuery query(getInstance()->database);
    return query;
}

QString DbConnector::getDbName()
{
    return getInstance()->database.databaseName();
}

void DbConnector::close()
{
    getInstance()->database.close();
}

void DbConnector::setDbName(QString name)
{
    qDebug() << "set db name "<< name;
    DbConnector::m_dbname = name;
}

void DbConnector::useAppData(bool use)
{
    DbConnector::m_useAppData = use;
}
