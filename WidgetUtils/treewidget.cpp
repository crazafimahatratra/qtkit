#include "treewidget.h"

using namespace WidgetUtils;
int TreeWidget::_filterTreeItems(QTreeWidgetItem *root, QString text)
{
    int nb = 0;
    if(root->childCount() == 0)
    {
        QString filter = text.toUpper();
        if(root->text(0).toUpper().contains(filter) || root->text(1).toUpper().contains(filter))
        {
            root->setHidden(false);
            nb++;
        }
        else
        {
            root->setHidden(true);
        }
        return nb;
    }
    for(int i = 0; i < root->childCount(); i++)
    {
        nb += _filterTreeItems(root->child(i), text);
    }
    root->setHidden(nb == 0);
    return nb;
}

TreeWidget::TreeWidget()
{

}

void TreeWidget::resizeColumns(QTreeWidget *widget)
{
    for(int i = 0; i < widget->columnCount(); i++)
        widget->resizeColumnToContents(i);
}

void TreeWidget::filterTreeItems(QTreeWidget *widget, QString text)
{
    for(int i = 0; i < widget->topLevelItemCount(); i++)
    {
        _filterTreeItems(widget->topLevelItem(i), text);
    }
}

void TreeWidget::hideEmptyTopTree(QTreeWidget *widget)
{
    for(int i = 0; i < widget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *top = widget->topLevelItem(i);
        top->setHidden(top->childCount() == 0);
    }
}
