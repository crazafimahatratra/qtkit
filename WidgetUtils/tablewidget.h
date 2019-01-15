#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>

namespace WidgetUtils {
    class TableWidget
    {
    public:
        TableWidget();
        static void setReadonly(QTableWidget *widget);
    };
}

#endif // TABLEWIDGET_H
