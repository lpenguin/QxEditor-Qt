#ifndef SCRIPTEDIT_H
#define SCRIPTEDIT_H

#include <QTextEdit>
#include <QtCore>
#include <QKeyEvent>
#include <QTextBlock>
#include "JavascriptHighlighter.h"

class ScriptEdit : public QTextEdit
{
    Q_OBJECT
public:
    ScriptEdit( QWidget * parent = 0 );
protected:
    void keyPressEvent ( QKeyEvent * e );
private:
    void autoIndent( void );
    JavascriptHighlighter highlighter;
};

#endif // SCRIPTEDIT_H
