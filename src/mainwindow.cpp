#include "mainwindow.h"

#include <QtWidgets>
#include <Qt3DCore>

#include "view.h"
#include "yripparser.h"
#include "ytestscene.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(0,0,960,540);

    createCentralWidget();
    createActions();
    createDockWidgets();
    statusBar()->showMessage(tr("StatusBar message"));
    _settings = new QSettings(this);
    restoreGeometry(_settings->value("geometry").toByteArray());
    restoreState(_settings->value("windowState").toByteArray());

    //restoreState();
}

MainWindow::~MainWindow()
{
    //saveState();
    _settings->setValue("geometry", saveGeometry());
    _settings->setValue("windowState", saveState());
}

void
MainWindow::createDockWidgets()
{
    QDockWidget *dockWidget = new QDockWidget(tr("Dock Widget"), this);
    dockWidget->setObjectName("Dock Widget");
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
    QGroupBox *gbLeft = new QGroupBox(tr("gbLeft"), this);
    dockWidget->setWidget(gbLeft);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    QDockWidget *dockWidgetR = new QDockWidget(tr("Dock Widget Right"), this);
    dockWidgetR->setObjectName("Dock Widget Right");
    dockWidgetR->setAllowedAreas(Qt::LeftDockWidgetArea |
                                Qt::RightDockWidgetArea);
    QGroupBox *gbRight = new QGroupBox(tr("gbRight"), this);
    dockWidgetR->setWidget(gbRight);
    addDockWidget(Qt::RightDockWidgetArea, dockWidgetR);
}

void
MainWindow::createCentralWidget()
{
    QWidget     *wdCentral = new QWidget(this);
    QGridLayout *loutCentral = new QGridLayout(wdCentral);


    _viewP = new View(this);
    //_viewP->setCamPersp();
    _viewP->setCamFront();

    //loutCentral->addWidget(new QGroupBox(tr("Front"), this), 0, 0);
    loutCentral->addWidget(_viewP, 0, 0);
    wdCentral->setLayout(loutCentral);

    setCentralWidget(wdCentral);
}

void
MainWindow::openFile()
{
    QStringList fNames = QFileDialog::getOpenFileNames(this, tr("Open Ninja RIP file"),
                                         "~", tr("Ninja RIP (*.rip);;Wavefront OBJ (*.obj);;All Files (*.*)"));
    qInfo() << "open files:" << fNames.length() << "\n" << fNames;
    Qt3DCore::QEntity *root = new Qt3DCore::QEntity();
    _parser = new YRipParser(root);
    if (_parser->parseFile(fNames.at(0))) {
        _parser->fileInfo();
    } else {
        _testScene = new YTestScene(root);
    }
    _viewP->setRootEntity(root);
}

void
MainWindow::createActions()
{
    auto fileMenu = menuBar()->addMenu(tr("&File"));

    auto fileToolBar = addToolBar(tr("&File"));
    fileToolBar->setObjectName("FileToolBar");


    QAction *actOpen = new QAction("&Open", this);
    connect(actOpen, &QAction::triggered, this, &MainWindow::openFile );
    fileMenu->addAction(actOpen);
    fileToolBar->addAction(actOpen);
    fileMenu->addSeparator();


    QAction *actExit = new QAction("E&xit", this);
    connect(actExit, &QAction::triggered, qApp, &QApplication::quit );
    fileMenu->addAction(actExit);
    fileToolBar->addAction(actExit);
    fileMenu->addSeparator();

    QAction *actCapture = new QAction("Capture", this);
    connect(actCapture, &QAction::triggered, _viewP, &View::captureToFile);    
    fileMenu->addAction(actCapture);
    fileToolBar->addSeparator();
    fileToolBar->addAction(actCapture);
}
