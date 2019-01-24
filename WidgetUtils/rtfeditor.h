#ifndef RTFEDITOR_H
#define RTFEDITOR_H

#include <QWidget>
#include <QToolBar>
#include <QMenu>
#include <QToolButton>
#include <QFontComboBox>
#include <QFont>
#include <QLabel>

namespace Ui {
class RtfEditor;
}

/**
 * @brief Rtf Editor widget
 */
class RtfEditor : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent : the parent widget
     */
    explicit RtfEditor(QWidget *parent = 0);

    /**
     * @brief sets html content to the editor
     * @param html : the html content
     */
    void setHtml(QString html);

    /**
     * @brief retrieves html content
     * @return the html content
     */
    QString toHtml();

    ~RtfEditor();

private slots:
    void on_actionBold_triggered(bool checked);

    void on_textEdit_cursorPositionChanged();

    void on_actionItalic_triggered(bool checked);

    void on_actionUnderline_triggered(bool checked);

    void on_actionHeading1_triggered();

    void on_actionHeading2_triggered();

    void on_actionHeading3_triggered();

    void on_actionParagraph_triggered();

    void on_actionColorChanged();

    void on_actionHighlightChanged();

    void on_currentFontChanged(QFont);

    void on_actionSizeUp_triggered();

    void on_actionSizeDown_triggered();

    void on_enterPressed();

private:
    const int fontSizes[4] = {10, 16, 14, 12};
    const QStringList colors = {"#000000", "#707070", "#CCCCCC", "#FFFFFF", "#205081",
                                "#59AFE1", "#14892C", "#8EB021", "#D04437",
                                "#F79232", "#F6C342", "#654982", "#F691B2"};
    const QStringList colorHighlights = {"#FFFF00", "#00FF00", "#00FFFF",
                                "#FF00FF", "#0000FF", "#FF0000", "transparent"};
    Ui::RtfEditor *ui;
    QToolBar *m_toolbar;
    QMenu *m_menuHeadings;
    QMenu *m_menuTextColors;
    QMenu *m_menuHighlights;
    QToolButton *m_toolButtonTextColors;
    QToolButton *m_toolButtonHighlight;
    QFontComboBox *m_fontComboBox;
    QLabel *m_labelfontsize;
    void setParagraphStyle(int h);
    QIcon createIconFromColorname(QString color);
    QIcon createIconTextColor(QString color, QString iconfile);
    void updateLabelFontSize();
    QList<QPoint> selectedParagraphs();

};

#endif // RTFEDITOR_H
