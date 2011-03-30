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

    loadSettings();
    verDialog = new VerDialog( this );
    edgeDialog= new EdgeDialog( this );
    graphDialog = new GraphDialog( this );
    questSettingsDialog = new QuestSettingsDialog( this );
    equationDialog = new QmEquationDialog( this );
    playerDialog = new PlayerDialog( this );

    setGraphType( Simple );

    setCentralWidget( graphView );

    if( qApp->argc() > 1 )
        loadFile(QString(qApp->argv()[1]) );


}
//
void MainDialogImpl::on_actionSettings_triggered(){
    questSettingsDialog->ShowGraph( graphView->graph() );
}

void MainDialogImpl::on_actionActions_triggered(){
    graphDialog->ShowGraph( graphView->graph() );
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
        JSONGraphReader * reader = new JSONGraphReader;
        if( m_graphType == Simple )
            reader->setInfoReader( new SimpleJSONInfoReader );
        else if( m_graphType == QuestLogic )
            reader->setInfoReader( new QlJSONInfoReader );
        graphView->Load( fileName, reader );
    }else if(fileName.endsWith(".qm")){
        QMGraphReader * reader = new QMGraphReader;
        reader->setReader( new QlQMInfoReader );
        graphView->Load( fileName, reader );
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
    JSONGraphWriter * writer = new JSONGraphWriter;

    if( m_graphType == Simple )
        writer->setInfoWriter( new SimpleJSONInfoWriter );
    else if( m_graphType == QuestLogic )
        writer->setInfoWriter( new QlJSONInfoWriter );

    graphView->Save(fileName, writer);
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
    //    SimpleVerInfo * info = new SimpleVerInfo;
    //    info->setId( graphView->graph()->GetNewVerId() );
    //BaseVer * ver = new BaseVer( new SimpleVerInfo( graphView->graph()->GetNewVerId() ) );
    Ver * ver = createVer();
    //    ver->setInfo( new SimpleVerInfo(graphView->graph()->GetNewVerId()));
    //        if( graphView->graph()->vers().count())
    //            ver->info()->setType( odinary );
    //        else
    //            ver->info()->setType( start );

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
    Edge * edge = createEdge( ver1->ver(), ver2->ver() );
    QSettings settings;
    if( settings.value("openNewDialog").toBool() ){
        if( edgeDialog->ShowEdge( edge ) == QDialog::Accepted )
            graphView->AddEdge( edge, ver1->pos(), ver2->pos() );
        else
            delete edge;
    }else
        graphView->AddEdge( edge, ver1->pos(), ver2->pos() );
}

void MainDialogImpl::setGraphType(MainDialogImpl::GraphType graphType)
{
    m_graphType = graphType;
    verDialog->setVerWidget( verWidget() );
    edgeDialog->setEdgeWidget( edgeWidget() );
    graphDialog->setGraphWidget( graphWidget() );
    graphView->CleanGraph();
    if( graphType == Simple )
        graphView->graph()->setInfo( new SimpleGraphInfo() );
    else
        graphView->graph()->setInfo( new QlGraphInfo( ));

}

Ver * MainDialogImpl::createVer()
{
    Ver * ver;
    if( m_graphType == Simple )
        ver = new Ver( new SimpleVerInfo( graphView->graph()->GetNewVerId() ) );
    else if(m_graphType == QuestLogic )
        ver = new Ver( new QlVerInfo( graphView->graph()->GetNewVerId() ) );
    else
     return 0;

    if( graphView->graph()->vers().count())
        ver->info()->setVerType( VerInfo::odinary );
    else
        ver->info()->setVerType( VerInfo::start );

    return ver;
}

Edge * MainDialogImpl::createEdge( Ver * v0, Ver * v1)
{
    if( m_graphType == Simple )
        return new Edge( new SimpleEdgeInfo( graphView->graph()->GetNewEdgeId() ), v0, v1  );
    else  if(m_graphType == QuestLogic )
        return new Edge( new QlEdgeInfo( graphView->graph()->GetNewEdgeId() ), v0, v1  );
    else
        return 0;
}

BaseVerWidget * MainDialogImpl::verWidget() const
{
    if( m_graphType == Simple ){
        return new SimpleVerWidget( verDialog );
    }else if(m_graphType == QuestLogic ){
        return new QlVerWidget( verDialog );
    } else
        return 0;

}

BaseEdgeWidget * MainDialogImpl::edgeWidget() const
{
    if( m_graphType == Simple ){
        return new SimpleEdgeWidget( edgeDialog );
    }else if(m_graphType == QuestLogic ){
        return new QlEdgeWidget( edgeDialog );
    } else
        return 0;
}

BaseGraphWidget * MainDialogImpl::graphWidget() const
{
    if( m_graphType == Simple ){
        return new SimpleGraphWidget( graphDialog );
    }else if(m_graphType == QuestLogic ){
        return new QlGraphWidget( graphDialog );
    } else
        return 0;
}

void MainDialogImpl::on_actionParse_Qm_Equation_triggered(){
    equationDialog->show();
}

void MainDialogImpl::on_actionQl_Graph_triggered(){
    setGraphType( QuestLogic );
}

void MainDialogImpl::on_actionSimple_triggered(){
    setGraphType( Simple );
}

void MainDialogImpl::on_actionPlay_triggered(){
    playerDialog->Play( curFile , m_playerPath );
}

void MainDialogImpl::loadSettings()
{
    QSettings settings;
    m_playerPath = settings.value("playerPath").toString();
    if( m_playerPath.isEmpty() ){
        m_playerPath = QFileDialog::getExistingDirectory(this, "Player path", QCoreApplication::applicationDirPath());
        settings.setValue("playerPath", m_playerPath);
    }
    m_playerPath+="/Main.qml";
}
