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
public slots:
    void openFile();

private:

    void createDockWidgets();
    void createCentralWidget();
    void createActions();

    QSettings   *_settings;
    YTestScene  *_testScene;
    View        *_viewP;
    QString     _fName;
};

#endif // MAINWINDOW_H
