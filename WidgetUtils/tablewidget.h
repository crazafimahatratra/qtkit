#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>

/**
 * @namespace WidgetUtils Utilities for QWidgets
 */
namespace WidgetUtils {
/**
     * @brief Utilities for QTableWidget objects
     */
    class TableWidget
    {
    public:
        TableWidget();
        /**
         * @brief sets all cells of the table to read only
         * @param widget the table widget to be set as read only
         */
        static void setReadonly(QTableWidget *widget);
    };
}

#endif // TABLEWIDGET_H
