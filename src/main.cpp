#include <QApplication>
#include "dialogimpl.h"
#include "MainDialogImpl.h"
#include "Transliter.h"
#include "stringoper.h"
#include "QmEqToBsConverter.h"
#include "BsToESMAScriptConverter.h"

int main(int argc, char ** argv)
{
    initTransliter();
    QApplication app( argc, argv );
    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Star Runner");
    MainDialogImpl win;
    win.show();
    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}

