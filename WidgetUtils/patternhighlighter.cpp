#include "patternhighlighter.h"
#include <QRegularExpressionMatchIterator>
#include <QDebug>

PatternHighlighter::PatternHighlighter(QTextDocument *parent, QString pattern) :
    QSyntaxHighlighter(parent),
    m_pattern(pattern)
{

}

void PatternHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myClassFormat;
    myClassFormat.setBackground(Qt::yellow);

    QRegularExpression expression(m_pattern, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), myClassFormat);
    }
}
