#ifndef PATTERNHIGHLIGHTER_H
#define PATTERNHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QTextDocument>

class PatternHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit PatternHighlighter(QTextDocument *parent, QString pattern);

protected:
    void highlightBlock(const QString &text) override;

signals:

public slots:

private:
    QString m_pattern;
};

#endif // PATTERNHIGHLIGHTER_H
