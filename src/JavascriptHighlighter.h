#ifndef JAVASCRIPTHIGHLIGHTER_H
#define JAVASCRIPTHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QtCore>
class JavascriptHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    JavascriptHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat nameFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif // JAVASCRIPTHIGHLIGHTER_H
