#ifndef BACKUP_H
#define BACKUP_H
#include <QWidget>
namespace QSqliteWrapper
{
    class Backup
    {
    public:
        Backup();
        static void exportDb(QWidget *parent);
        static void importDb(QWidget* parent, int exitCodeReboot);
    };
}
#endif // BACKUP_H
