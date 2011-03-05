#include <QApplication>
#include "dialogimpl.h"
#include "MainDialogImpl.h"
#include "Transliter.h"
//
int main(int argc, char ** argv)
{
    initTransliter();
    QApplication app( argc, argv );
    MainDialogImpl win;
    win.show();
    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );


    return app.exec();
}

