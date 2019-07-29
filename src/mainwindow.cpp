#include "mainwindow.h"

#include <QtWidgets>
#include <Qt3DCore>

#include "view.h"
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

    Qt3DCore::QEntity *root = new Qt3DCore::QEntity();
   _testScene = new YTestScene(root);

    _viewP = new View(this);
    _viewP->setRootEntity(root);
    _viewP->setCamPersp();

    //loutCentral->addWidget(new QGroupBox(tr("Front"), this), 0, 0);
    loutCentral->addWidget(_viewP, 0, 0);
    wdCentral->setLayout(loutCentral);

    setCentralWidget(wdCentral);
}

void
MainWindow::createActions()
{
    auto fileMenu = menuBar()->addMenu(tr("&File"));

    auto fileToolBar = addToolBar(tr("&File"));
    fileToolBar->setObjectName("FileToolBar");

    QAction *actExit = new QAction("E&xit", this);
    connect(actExit, &QAction::triggered, qApp, &QApplication::quit );
    fileMenu->addAction(actExit);
    fileToolBar->addAction(actExit);

    QAction *actCapture = new QAction("Capture", this);
    connect(actCapture, &QAction::triggered, _viewP, &View::captureToFile);
    fileMenu->addSeparator();
    fileMenu->addAction(actCapture);
    fileToolBar->addSeparator();
    fileToolBar->addAction(actCapture);
}
