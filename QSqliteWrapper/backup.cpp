#include "backup.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include "dbconnector.h"

using namespace QSqliteWrapper;
Backup::Backup()
{

}

void Backup::exportDb(QWidget *parent)
{
    QString mesdocs = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString path = QFileDialog::getExistingDirectory(parent, "Choisissez la destination", mesdocs);

    QString source = DbConnector::getDbName();
    QFileInfo info(source);
    QString name = info.baseName() + "_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmm") + ".db";
    QString dest = QDir::cleanPath(path + QDir::separator() + name);
    if(QFile::copy(source, dest))
    {
        QMessageBox::information(parent, "Export", QString("Export effectué, sous le nom:\n%1").arg(dest));
    }
}
