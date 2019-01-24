#include "rtfeditor.h"
#include "ui_rtfeditor.h"
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextBlock>
#include <QTextDocumentFragment>
#include <QToolButton>
#include <QMenu>
#include <QDebug>
#include <QPainter>

RtfEditor::RtfEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtfEditor),
    m_toolbar(new QToolBar(this)),
    m_menuHeadings(new QMenu(this)),
    m_menuTextColors(new QMenu(this)),
    m_menuHighlights(new QMenu(this)),
    m_toolButtonTextColors(new QToolButton(this)),
    m_toolButtonHighlight(new QToolButton(this)),
    m_fontComboBox(new QFontComboBox(this)),
    m_labelfontsize(new QLabel(this))
{
    ui->setupUi(this);

    //*************** headings ******************/
    QToolButton *toolButtonHeadings = new QToolButton(this);

    QActionGroup *headerGroup = new QActionGroup(this);
    ui->actionHeading1->setActionGroup(headerGroup);
    ui->actionHeading2->setActionGroup(headerGroup);
    ui->actionHeading3->setActionGroup(headerGroup);
    ui->actionParagraph->setActionGroup(headerGroup);
    m_menuHeadings->addAction(ui->actionHeading1);
    m_menuHeadings->addAction(ui->actionHeading2);
    m_menuHeadings->addAction(ui->actionHeading3);
    m_menuHeadings->addAction(ui->actionParagraph);

    toolButtonHeadings->setIcon(QIcon(":/editor/icons/edit-heading.png"));
    toolButtonHeadings->setMenu(m_menuHeadings);
    toolButtonHeadings->setPopupMode(QToolButton::MenuButtonPopup);

    //**************** text colors ****************/
    QActionGroup *colorsGroup = new QActionGroup(this);
    m_toolButtonTextColors->setIcon(QIcon(":/editor/icons/edit-color.png"));
    m_toolButtonTextColors->setMenu(m_menuTextColors);
    m_toolButtonTextColors->setPopupMode(QToolButton::MenuButtonPopup);
    int index = 0;
    foreach(QString color, colors)
    {
        QAction *actionColor = new QAction(this);
        actionColor->setText(QString("Color %1").arg(++index));
        actionColor->setIcon(createIconFromColorname(color));
        actionColor->setData(color);
        actionColor->setActionGroup(colorsGroup);
        actionColor->setCheckable(true);
        m_menuTextColors->addAction(actionColor);
        connect(actionColor, SIGNAL(triggered(bool)), this, SLOT(on_actionColorChanged()));
    }

    //**************** highlight colors ****************/
    QActionGroup *highlightsGroup = new QActionGroup(this);
    m_toolButtonHighlight->setIcon(QIcon(":/editor/icons/highlighter-color.png"));
    m_toolButtonHighlight->setMenu(m_menuHighlights);
    m_toolButtonHighlight->setPopupMode(QToolButton::MenuButtonPopup);
    int index1 = 0;
    foreach(QString color, colorHighlights)
    {
        QAction *actionColor = new QAction(this);
        actionColor->setText(color == "transparent" ? "Aucun" : QString("Color %1").arg(++index1));
        actionColor->setIcon(createIconFromColorname(color));
        actionColor->setData(color);
        actionColor->setActionGroup(highlightsGroup);
        actionColor->setCheckable(true);
        if(color == "transparent")
        {
            m_menuHighlights->addSeparator();
        }
        m_menuHighlights->addAction(actionColor);
        connect(actionColor, &QAction::triggered, this, &RtfEditor::on_actionHighlightChanged);
    }

    /************ Font **********/
    ui->textEdit->setFont(QFont("Open Sans", 10));
    connect(m_fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(on_currentFontChanged(QFont)));

    ui->horizontalLayout->addWidget(m_toolbar);
    m_toolbar->addWidget(toolButtonHeadings);
    m_toolbar->addSeparator();
    m_toolbar->addAction(ui->actionBold);
    m_toolbar->addAction(ui->actionItalic);
    m_toolbar->addAction(ui->actionUnderline);
    m_toolbar->addSeparator();
    m_toolbar->addWidget(m_toolButtonTextColors);
    m_toolbar->addWidget(m_toolButtonHighlight);
    m_toolbar->addSeparator();
    m_toolbar->addWidget(m_fontComboBox);
    m_toolbar->addAction(ui->actionSizeUp);
    m_toolbar->addAction(ui->actionSizeDown);
    m_toolbar->addWidget(m_labelfontsize);

    connect(ui->textEdit, &TextEditor::enterKeyPressed, this, &RtfEditor::on_enterPressed);
}

void RtfEditor::setHtml(QString html)
{
    ui->textEdit->setHtml(html);
}

QString RtfEditor::toHtml()
{
    return ui->textEdit->toHtml();
}

RtfEditor::~RtfEditor()
{
    delete m_menuHeadings;
    delete m_menuTextColors;
    delete m_menuHighlights;
    delete m_toolButtonTextColors;
    delete m_toolButtonHighlight;
    delete m_fontComboBox;
    delete m_labelfontsize;
    delete m_toolbar;
    delete ui;
}

void RtfEditor::on_actionBold_triggered(bool checked)
{
     QTextCharFormat format = ui->textEdit->textCursor().charFormat();
     QFont font = format.font();
     font.setBold(checked);
     format.setFont(font);
     ui->textEdit->textCursor().mergeCharFormat(format);
}

void RtfEditor::on_actionItalic_triggered(bool checked)
{
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    QFont font = format.font();
    font.setItalic(checked);
    format.setFont(font);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

void RtfEditor::on_actionUnderline_triggered(bool checked)
{
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    QFont font = format.font();
    font.setUnderline(checked);
    format.setFont(font);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

void RtfEditor::on_textEdit_cursorPositionChanged()
{
    qDebug() << "cursor changed " << ui->textEdit->textCursor().position();
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    int state = ui->textEdit->textCursor().block().userState();
    QFont font = format.font();
    ui->actionBold->setChecked(font.bold());
    ui->actionItalic->setChecked(font.italic());
    ui->actionUnderline->setChecked(font.underline());

    /********* headers *********/
    switch(state)
    {
    case 1:
        ui->actionHeading1->setChecked(true);
        break;
    case 2:
        ui->actionHeading2->setChecked(true);
        break;
    case 3:
        ui->actionHeading3->setChecked(true);
        break;
    default:
        ui->actionParagraph->setChecked(true);
    }

    /********* text colors *********/
    QColor c1 = format.foreground().color();
    QList<QAction *> colorActions = m_menuTextColors->actions();
    int l1 = colorActions.length();
    for(int i = 0; i < l1; i++)
    {
        QString c = colorActions[i]->data().toString();
        if(c.toUpper() == c1.name().toUpper())
        {
            colorActions[i]->setChecked(true);
            m_toolButtonTextColors->setIcon(createIconTextColor(c, ":/editor/icons/edit-color.png"));
            break;
        }
    }

    /********* highlight colors *********/
    QString c2 = format.background().color().name();
    if(format.background().style() == Qt::NoBrush)
    {
        c2 = "transparent";
    }
    QList<QAction *> highlightActions = m_menuHighlights->actions();
    int l2 = highlightActions.length();
    for(int i = 0; i < l2; i++)
    {
        QString c = highlightActions[i]->data().toString();
        if(c.toUpper() == c2.toUpper())
        {
            highlightActions[i]->setChecked(true);
            m_toolButtonHighlight->setIcon(createIconTextColor(c2 == "transparent" ? "#EEEEEE" : c2, ":/editor/icons/highlighter-color.png"));
            break;
        }
    }

    /*********** Font combobox ***********/
    m_fontComboBox->blockSignals(true);
    m_fontComboBox->setCurrentFont(format.font());
    m_fontComboBox->blockSignals(false);

    updateLabelFontSize();
}

void RtfEditor::setParagraphStyle(int h)
{
    qDebug() << "set paragraph style " << h;
    QList<QPoint> paragraphs = selectedParagraphs();
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();
    for(QPoint p: paragraphs)
    {
        cursor.setPosition(p.x());
        cursor.setPosition(p.y(), QTextCursor::KeepAnchor);
        QTextCharFormat format = cursor.charFormat();
        format.setFont(QFont("Open Sans", fontSizes[h], h > 0 ? QFont::Bold: QFont::Normal));
        if(h > 0)
        {
            format.setForeground(QBrush(QColor(0, 0, 0)));
        }
        cursor.block().setUserState(h);
        QTextBlockFormat blockFormat = cursor.block().blockFormat();
        blockFormat.setLineHeight(h > 0 ? 150 : 100, QTextBlockFormat::ProportionalHeight);
        cursor.mergeBlockFormat(blockFormat);
        cursor.mergeCharFormat(format);
        cursor.setBlockCharFormat(format);
    }
    cursor.endEditBlock();
    updateLabelFontSize();
}

QIcon RtfEditor::createIconFromColorname(QString color)
{
    int size = 16;
    QColor bg(color);
    QColor fg = bg.darker(120);
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(QBrush(bg));
    painter.setPen(fg);
    painter.drawRect(1, 1, size - 2, size - 2);
    painter.end();
    return QIcon(pixmap);
}

QIcon RtfEditor::createIconTextColor(QString color, QString iconfile)
{
    int size = 16;
    QColor bg(color);
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);
    pixmap.load(iconfile);
    QPainter painter(&pixmap);
    painter.fillRect(0, 13, size, 3, bg);
    painter.end();
    return QIcon(pixmap);
}

void RtfEditor::updateLabelFontSize()
{
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    QString f = "px";
    int size = format.font().pixelSize();
    if(size < 0) {
        size = format.font().pointSize();
        f = "pt";
    }
    m_labelfontsize->setText(QString("%1 %2").arg(size).arg(f));
}

QList<QPoint> RtfEditor::selectedParagraphs()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCursor copyCursor(cursor);
    QList<QPoint> points;
    for(int i = cursor.selectionStart(); i <= cursor.selectionEnd(); i++)
    {
        copyCursor.setPosition(i);
        int start = copyCursor.block().position();
        int end = start + copyCursor.block().length() - 1;
        points.append(QPoint(start, end));
    }
    return points;
}

void RtfEditor::on_actionHeading1_triggered()
{
    setParagraphStyle(1);
}

void RtfEditor::on_actionHeading2_triggered()
{
    setParagraphStyle(2);
}

void RtfEditor::on_actionHeading3_triggered()
{
    setParagraphStyle(3);
}

void RtfEditor::on_actionParagraph_triggered()
{
    setParagraphStyle(0);
}

void RtfEditor::on_actionColorChanged()
{
    QAction *sender = qobject_cast<QAction *>(this->sender());
    if(!sender)
        return;
    QString c = sender->data().toString();
    QColor color(c);
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    format.setForeground(QBrush(color));
    ui->textEdit->textCursor().mergeCharFormat(format);
    m_toolButtonTextColors->setIcon(createIconTextColor(c, ":/editor/icons/edit-color.png"));
}

void RtfEditor::on_actionHighlightChanged()
{
    QAction *sender = qobject_cast<QAction *>(this->sender());
    if(!sender)
        return;
    QString c = sender->data().toString();
    QColor color(c);
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    if(c.toUpper() == "TRANSPARENT")
    {
        format.setBackground(QBrush(Qt::NoBrush));
    }
    else
    {
        format.setBackground(QBrush(color));
    }
    ui->textEdit->textCursor().mergeCharFormat(format);
    m_toolButtonHighlight->setIcon(createIconTextColor(c == "transparent" ? "#EEEEEE" : c, ":/editor/icons/highlighter-color.png"));
}

void RtfEditor::on_currentFontChanged(QFont font)
{
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    QFont currentFont = format.font();
    font.setStyle(currentFont.style());
    format.setFont(font);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

void RtfEditor::on_actionSizeUp_triggered()
{
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    QFont font = format.font();
    if(font.pointSize() < 0)
    {
        font.setPixelSize(font.pixelSize() + 1);
    }
    else
    {
        font.setPointSize(font.pointSize() + 1);
    }
    format.setFont(font);
    ui->textEdit->textCursor().mergeCharFormat(format);
    updateLabelFontSize();
}

void RtfEditor::on_actionSizeDown_triggered()
{
    QTextCharFormat format = ui->textEdit->textCursor().charFormat();
    QFont font = format.font();
    if(font.pointSize() < 0)
    {
        font.setPixelSize(font.pixelSize() - 1);
    }
    else
    {
        font.setPointSize(font.pointSize() - 1);
    }
    format.setFont(font);
    ui->textEdit->textCursor().mergeCharFormat(format);
    updateLabelFontSize();
}

void RtfEditor::on_enterPressed()
{
    setParagraphStyle(0);
}
