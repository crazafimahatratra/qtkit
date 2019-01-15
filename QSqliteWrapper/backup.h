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
    };
}
#endif // BACKUP_H
