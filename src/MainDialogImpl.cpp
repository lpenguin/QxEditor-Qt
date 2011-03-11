#include <QtGui>
#include "MainDialogImpl.h"
//
MainDialogImpl::MainDialogImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
    QCoreApplication::setOrganizationName("pr123");
    QCoreApplication::setOrganizationDomain("pr123.anywhere");
    QCoreApplication::setApplicationName("QxEditor");
	setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);


     createActions();
     createMenus();
     (void)statusBar();

     setWindowFilePath(QString());
     updateRecentFileActions();
     
   	QObject::connect(graphView, SIGNAL( VerClicked( VerItem * , Qt::MouseButton ) ),
					 this, SLOT( VerClicked( VerItem * , Qt::MouseButton ) ));

	QObject::connect(graphView, SIGNAL( EdgeClicked( EdgeItem *, Qt::MouseButton ) ),
					 this, SLOT( EdgeClicked( EdgeItem *, Qt::MouseButton ) ));

	QObject::connect(graphView, SIGNAL( AreaClicked( QPointF , Qt::MouseButton) ),
					 this, SLOT( AreaClicked( QPointF, Qt::MouseButton) ));

	QObject::connect(graphView, SIGNAL( VersConnected( VerItem *, VerItem *) ),
					 this, SLOT( VersConnected( VerItem *, VerItem *)));

        verDialog = new VerDialogImpl( this );
        edgeDialog= new EdgeDialogImpl( this );
        questActionsDialog = new QuestActionsDialog( this );
        questSettingsDialog = new QuestSettingsDialog( this );

        setCentralWidget( graphView );

        if( qApp->argc() > 1 )
            loadFile(QString(qApp->argv()[1]) );
}
//
void MainDialogImpl::on_actionSettings_triggered(){
    questSettingsDialog->ShowGraph( graphView->graph() );
}

void MainDialogImpl::on_actionActions_triggered(){
    questActionsDialog->ShowGraph( graphView->graph() );
}


void MainDialogImpl::on_actionOpen_triggered()
{
	// TODO
}

void MainDialogImpl::on_actionSave_triggered()
{
	// TODO
}

void MainDialogImpl::on_actionSave_as_triggered()
{
	// TODO
}

void MainDialogImpl::newFile()
 {
    graphView->CleanGraph();
    graphView->graph()->Clean();
    curFile = QString();
 }

 void MainDialogImpl::open()
 {
     QString fileName = QFileDialog::getOpenFileName(this);
     if (!fileName.isEmpty())
         loadFile(fileName);
 }

 void MainDialogImpl::save()
 {
     if (curFile.isEmpty())
         saveAs();
     else
         saveFile(curFile);
 }

 void MainDialogImpl::saveAs()
 {
     QString fileName = QFileDialog::getSaveFileName(this);
     if (fileName.isEmpty())
         return;

     saveFile(fileName);
 }

 void MainDialogImpl::openRecentFile()
 {
     QAction *action = qobject_cast<QAction *>(sender());
     if (action)
         loadFile(action->data().toString());
 }

 void MainDialogImpl::about()
 {
    QMessageBox::about(this, tr("About Recent Files"),
             tr("The <b>Recent Files</b> example demonstrates how to provide a "
                "recently used file menu in a Qt application."));
 }

 void MainDialogImpl::createActions()
 {
     connect(actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
     connect(actionOpen, SIGNAL(triggered()), this, SLOT(open()));
     connect(actionSave, SIGNAL(triggered()), this, SLOT(save()));
     connect(actionSave_as, SIGNAL(triggered()), this, SLOT(saveAs()));

     for (int i = 0; i < MaxRecentFiles; ++i) {
         recentFileActs[i] = new QAction(this);
         recentFileActs[i]->setVisible(false);
         connect(recentFileActs[i], SIGNAL(triggered()),
                 this, SLOT(openRecentFile()));
     }

     connect(actionExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
     connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
 }

 void MainDialogImpl::createMenus()
 {
     for (int i = 0; i < MaxRecentFiles; ++i)
         menuRecent->addAction(recentFileActs[i]);
 }

void MainDialogImpl::loadFile(const QString &fileName)
{

//	QFile file(fileName);
//	if (!file.open(QFile::ReadOnly | QFile::Text)) {
//		QMessageBox::warning(this, tr("Recent Files"),
//			tr("Cannot read file %1:\n%2.")
//			.arg(fileName)
//			.arg(file.errorString()));
//		return;
//	}

//	QXmlStreamReader in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);


        //graphView->Load(in);
        if( fileName.endsWith(".json")){
            graphView->Load( fileName, JSONGraphReaderType );
        }else if(fileName.endsWith(".qm")){
            graphView->Load( fileName, QMGraphReaderType );
        }else{
            QApplication::restoreOverrideCursor();
            statusBar()->showMessage(tr("Unknown extention"), 2000);
            QMessageBox::warning(this, "Warning", tr("Unknown extention: %1").arg(fileName));
            return;
        }
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
 }

 void MainDialogImpl::saveFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Recent Files"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return;
     }

     QTextStream out(&file);
     QApplication::setOverrideCursor(Qt::WaitCursor);

     graphView->Save(fileName);
     //out << textEdit->toPlainText();
     QApplication::restoreOverrideCursor();

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File saved"), 2000);
 }

 void MainDialogImpl::setCurrentFile(const QString &fileName)
 {
     curFile = fileName;
     setWindowFilePath(curFile);

     QSettings settings;
     QStringList files = settings.value("recentFileList").toStringList();
     files.removeAll(fileName);
     files.prepend(fileName);
     while (files.size() > MaxRecentFiles)
         files.removeLast();

    settings.setValue("recentFileList", files);
	updateRecentFileActions();
     //foreach (QWidget *widget, QApplication::topLevelWidgets()) {
         //MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
         //if (mainWin)
             //mainWin->updateRecentFileActions();
     //}
 }

 void MainDialogImpl::updateRecentFileActions()
 {
     QSettings settings;
     QStringList files = settings.value("recentFileList").toStringList();

     int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

     for (int i = 0; i < numRecentFiles; ++i) {
         QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
         recentFileActs[i]->setText(text);
         recentFileActs[i]->setData(files[i]);
         recentFileActs[i]->setVisible(true);
     }
     for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
         recentFileActs[j]->setVisible(false);

     //separatorAct->setVisible(numRecentFiles > 0);
 }
 
QString MainDialogImpl::strippedName(const QString &fullFileName){
	return QFileInfo(fullFileName).fileName();
}
void MainDialogImpl::VerClicked( VerItem * ver , Qt::MouseButton button ){
    if( button & Qt::LeftButton ){
        verDialog->ShowVer(ver->ver());
        ver->update();
    }
	else if(button & Qt::RightButton )
		graphView->RemoveVer(ver);
}

void MainDialogImpl::EdgeClicked( EdgeItem * edge, Qt::MouseButton button ){
	if( button & Qt::LeftButton )
		edgeDialog->ShowEdge( edge->edge() );
	else if( button & Qt::RightButton )
		graphView->RemoveEdge(edge);
}

void MainDialogImpl::AreaClicked( QPointF point, Qt::MouseButton){
        Ver * ver = new Ver;
        ver->info()->id() = graphView->graph()->GetNewVerId();
        if( graphView->graph()->vers().count())
            ver->info()->setType( odinary );
        else
            ver->info()->setType( start );

	QSettings settings;
	if( settings.value("openNewDialog").toBool() ){
		if( verDialog->ShowVer( ver ) == QDialog::Accepted )
			graphView->AddVer( ver, point );
		else
			delete ver;
	}else
		graphView->AddVer( ver, point );
}

void MainDialogImpl::VersConnected( VerItem * ver1, VerItem * ver2){
	Edge * edge = new Edge( ver1->ver(), ver2->ver() );
        edge->info()->setId( graphView->graph()->GetNewEdgeId() );
	QSettings settings;
	if( settings.value("openNewDialog").toBool() ){
		if( edgeDialog->ShowEdge( edge ) == QDialog::Accepted )
			graphView->AddEdge( edge, ver1->pos(), ver2->pos() );
		else
			delete edge;
	}else
		graphView->AddEdge( edge, ver1->pos(), ver2->pos() );
}




