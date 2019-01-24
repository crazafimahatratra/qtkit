#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

class TextEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = nullptr);
private:
    void keyReleaseEvent(QKeyEvent *e) override;

signals:
    void enterKeyPressed();

public slots:
};

#endif // TEXTEDITOR_H
