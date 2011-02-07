#include "ScriptEdit.h"

ScriptEdit::ScriptEdit(QWidget * parent):QTextEdit( parent )
{
    highlighter.setDocument(document());
}

void ScriptEdit::keyPressEvent ( QKeyEvent * e ){
    //qDebug()<<"cursorPos: "<<textCursor().position();
    QTextEdit::keyPressEvent( e );
    if( e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return){
        autoIndent();
    }

}

void ScriptEdit::autoIndent()
{
    //COPIED FROM QDevelop :-)

    QTextBlock blocAIndenter;
    QTextBlock b = textCursor().block();
    if (  b.previous().isValid() && !b.previous().text().isEmpty() )
        blocAIndenter = b;
    else
        return;
    QTextBlock blocAvant = blocAIndenter.previous();
    if ( !blocAvant.isValid() )
        return;
    QString simple = blocAvant.text().simplified();
    QString blancs;
    for (int i=0; i< blocAvant.text().length(); i++)
    {
        if ( blocAvant.text().at(i) == ' ' || blocAvant.text().at(i) == '\t' )
        {
            QString s = blocAvant.text().at(i);
//            if ( m_tabSpaces )
//            {
//                int nbSpaces = tabStopWidth() / fontMetrics().width( " " );
//                QString spaces;
//                for (int i = 0; i<nbSpaces; i++)
//                    spaces += " " ;
//                s.replace("\t", spaces);
//            }
            blancs += s;
        }
        else
            break;
    }
    if ( simple.simplified().length() && ((simple.contains("(") && simple.contains(")")
            && QString("if:while:do:switch:foreach").contains( simple.section("(", 0, 0).simplified() )
            && (simple.contains('{') || simple.right(1) != ";" ) )
           || QString("else:case:default").indexOf( simple.simplified() ) == 0
           || simple.simplified().at(0) == '{' || simple.simplified().at( simple.simplified().length()-1 ) == '{' ))
    {
//        if ( m_tabSpaces )
//        {
//            int nbSpaces = tabStopWidth() / fontMetrics().width( " " );
//            for (int i = 0; i<nbSpaces; i++)
//                blancs +=  " " ;
//        }
//        else
            blancs += "\t";
    }
    textCursor().insertText( blancs );
    return;
}
