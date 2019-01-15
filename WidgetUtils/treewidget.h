#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>

namespace WidgetUtils {
    class TreeWidget
    {
    private:
        static int _filterTreeItems(QTreeWidgetItem *root, QString text);
    public:
        TreeWidget();
        static void resizeColumns(QTreeWidget *widget);
        static void filterTreeItems(QTreeWidget *widget, QString text);
    };
}

#endif // TREEWIDGET_H
