#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

/**
 * @brief A class that extends QTextEdit
 */
class TextEditor : public QTextEdit
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent : the parent widget
     */
    explicit TextEditor(QWidget *parent = nullptr);
private:
    void keyReleaseEvent(QKeyEvent *e) override;

signals:
    /**
     * @brief raised when the ENTER KEY was pressed
     */
    void enterKeyPressed();

public slots:
};

#endif // TEXTEDITOR_H
