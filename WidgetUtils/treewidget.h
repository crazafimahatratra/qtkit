#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>

namespace WidgetUtils {
/**
     * @brief Utilities for QTreeWidget objects
     */
    class TreeWidget
    {
    private:
        static int _filterTreeItems(QTreeWidgetItem *root, QString text);
    public:
        TreeWidget();
        /**
         * @brief resize all columns of a treeWidget to their contents
         * @param widget : the tree widget
         */
        static void resizeColumns(QTreeWidget *widget);

        /**
         * @brief filter the tree widget according to the text passed as parameter
         * @param widget : the tree widget to be filtered
         * @param text : the filter to be applied to the widget
         */
        static void filterTreeItems(QTreeWidget *widget, QString text);
    };
}

#endif // TREEWIDGET_H
