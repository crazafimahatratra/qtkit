#include "backup.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QCoreApplication>
#include <QDebug>
#include "dbconnector.h"

using namespace QSqliteWrapper;
Backup::Backup()
{

}

void Backup::exportDb(QWidget *parent)
{
    QString mesdocs = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString path = QFileDialog::getExistingDirectory(parent, "Choisissez la destination", mesdocs);
    QString dest = Backup::backup(path, QDateTime::currentDateTime().toString("yyyyMMdd_HHmm"));
    if(!dest.isEmpty())
    {
        QMessageBox::information(parent, "Export", QString("Export effectué, sous le nom:\n%1").arg(dest));
    }
}

void Backup::importDb(QWidget* parent, int exitCodeReboot)
{
    int res = QMessageBox::warning(parent, "Confirmation", "Attention !!!\nCette action va remplacer la base de données actuelle.\n"
                                                         "En etes-vous sur ?", QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::No)
        return;
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString filename = QFileDialog::getOpenFileName(parent, "Choisissez un fichier", defaultPath, "Bolide Database (*.db)");
    if(filename.isEmpty())
    {
        return;
    }
    QString dest = DbConnector::getDbName();
    DbConnector *instance = DbConnector::getInstance();
    if (instance)
    {
        delete instance;
    }
    if(!QFile::remove(dest))
    {
        QMessageBox::warning(parent, "Erreur", "La base en cours n'a pas pu être effacé.");
        return;
    }
    if(!QFile::copy(filename, dest))
    {
        QMessageBox::critical(parent, "Erreur", "Erreur lors de la copie de la nouvelle base\n.Restauration échouée. Veuillez copier manuellement le fichier");
        return;
    }
    QMessageBox::information(parent, "Base restaurée", QString("La base a été remplacée par le fichier\n%1\n"
                                                     "L'application va redémarrer.").arg(filename));
    QCoreApplication::instance()->exit(exitCodeReboot);
}

QString Backup::backup(QString path, QString suffix)
{
    QString source = DbConnector::getDbName();
    QFileInfo info(source);
    QString name = info.baseName() + "_" + suffix + ".db";
    QString dest = QDir::cleanPath(path + QDir::separator() + name);
    qDebug() << source << ">>" << dest;
    if(QFile::copy(source, dest))
        return dest;
    return "";
}
