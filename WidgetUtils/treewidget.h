#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>

namespace WidgetUtils {
    class TreeWidget
    {
    public:
        TreeWidget();
        static void resizeColumns(QTreeWidget *widget);
    };
}

#endif // TREEWIDGET_H
