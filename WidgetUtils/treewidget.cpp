#include "treewidget.h"

using namespace WidgetUtils;
TreeWidget::TreeWidget()
{

}

void TreeWidget::resizeColumns(QTreeWidget *widget)
{
    for(int i = 0; i < widget->columnCount(); i++)
        widget->resizeColumnToContents(i);
}
