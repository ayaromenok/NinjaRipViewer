#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QSettings;
class YTestScene;
class View;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    void createDockWidgets();
    void createCentralWidget();
    void createActions();

    QSettings   *_settings;
    YTestScene  *_testScene;
    View*       _viewP;
};

#endif // MAINWINDOW_H
