#include "version.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Version::Version():
    Table("version")
{

}

int Version::currentVersion()
{
    QList<Version *> rows = Table::get<Version>();
    int v = 0;
    for(int i = 0; i < rows.count(); i++)
    {
        v = rows[i]->version;
        delete rows[i];
    }
    return v;
}

void Version::upgrade(QString upgradeFile)
{
    int dbver = currentVersion();
    QFile file(upgradeFile);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        qDebug() << "No such file upgrade.sql";
        return;
    }
    QTextStream in(&file);
    QString mytext = in.readAll();
    QStringList sqls = mytext.split(";");
    for(int i = 0; i < sqls.size(); i++)
    {
        if(sqls.at(i).isEmpty())
            continue;
        QStringList list = sqls.at(i).split("|");
        if(list.count() < 2)
            continue;
        int v = list.at(0).toInt();
        if(v < dbver) {
            continue;
        }
        exec(list.at(1));
    }
    file.close();
}

void Version::fromRecord(QSqlRecord record)
{
    this->version = record.value("version").toInt();
}

QList<Parameter> Version::prepareParameters()
{
    QList<Parameter> parameters;
    parameters.append(Parameter("version", this->version));
    return parameters;
}
