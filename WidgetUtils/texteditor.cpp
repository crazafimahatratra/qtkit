#include "texteditor.h"
#include <QDebug>

TextEditor::TextEditor(QWidget *parent) : QTextEdit(parent)
{

}

void TextEditor::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
    {
        emit this->enterKeyPressed();
    }
    e->accept();
}
