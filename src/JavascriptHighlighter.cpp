#include "JavascriptHighlighter.h"

JavascriptHighlighter::JavascriptHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bvar\\b" << "\\bArray\\b" << "\\bconst\\b"
                    << "\\bfor\\b" << "\\bString\\b" << "\\bObject\\b"
                    << "\\bwhile\\b" << "\\bfunction\\b" << "\\bforeach\\b"
                    << "\\bdo\\b" << "\\bnew\\b" << "\\breturn\\b" << "\\bin\\b";

    nameFormat.setForeground(Qt::darkBlue);
    //nameFormat.setFontWeight(QFont::Bold);
    QStringList namePatterns;
    namePatterns << "\\bArray\\b" << "\\bString\\b" << "\\bObject\\b";


    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    //functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\bfunction\\s+[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");

    foreach (QString pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    foreach (QString pattern, namePatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format =nameFormat;
        highlightingRules.append(rule);
    }

}

void JavascriptHighlighter::highlightBlock(const QString &text)
{
//qDebug()<<text;
    foreach (HighlightingRule rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = text.indexOf(expression);
  //      qDebug()<<index<<" "<<rule.pattern;
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = text.indexOf(expression, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        int endIndex = text.indexOf(commentEndExpression, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression,
                                                startIndex + commentLength);
    }
}
