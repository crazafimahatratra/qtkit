#ifndef BACKUP_H
#define BACKUP_H
#include <QWidget>
namespace QSqliteWrapper
{
/**
* \brief The class Backup contains utilities to export and import SQlite database
*
*/
    class Backup
    {
    public:
        Backup();
        /**
         * @brief exportDb opens a file dialog for choosing the destination directory, then
         * saves a copy of the current database in the choosen directory
         * @param parent the widget calling the method
         */
        static void exportDb(QWidget *parent);

        /**
         * @brief importDb opens a file dialog for choosing the file to be imported
         * @param parent the calling widget
         * @param exitCodeReboot a exit code for restarting the App
         */
        static void importDb(QWidget* parent, int exitCodeReboot);

        static QString backup(QString path, QString suffix);
    };
}
#endif // BACKUP_H
