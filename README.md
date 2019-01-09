# qtkit
Utilities for Qt

## Configuration
Add sql support in pro file:

```
QT += sql
```

## Usage (client.h)
```
#include "qtkit/QSqliteWrapper/table.h"

class Client : public QSqliteWrapper::Table
{
public:
    Client();

    // Table interface
public:
    QString pkName()
    {
        return "id";
    }
    QVariant pkValue()
    {
        return this->id;
    }
    void setPkValue(QVariant pk)
    {
        this->id = pk.toInt();
    }
    void fromRecord(QSqlRecord record)
    {
        this->id = record.value("id").toInt();
        this->name = record.value("name").toString();
    }
    QList<QSqliteWrapper::Parameter> prepareParameters()
    {
        QList<QSqliteWrapper::Parameter> parameters;
        parameters.append(QSqliteWrapper::Parameter("name", this->name));
        return parameters;
    }

    int id;
    QString name;
};
```

## Usage (main.cpp)
```
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqliteWrapper::DbConnector::setDbName("baba.db");
    QList<Client *> clients = Client::getAll<Client>();

    return a.exec();
}
```
