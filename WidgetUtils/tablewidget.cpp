#include "tablewidget.h"

using namespace WidgetUtils;
TableWidget::TableWidget()
{

}

void TableWidget::setReadonly(QTableWidget *widget)
{
    for(int i = 0; i < widget->rowCount(); i++)
    {
        for(int j = 0; j < widget->columnCount(); j++)
        {
            if(!widget->item(i, j))
                continue;
            Qt::ItemFlags flags = widget->item(i, j)->flags();
            widget->item(i, j)->setFlags(flags ^ Qt::ItemIsEditable);
        }
    }
}
