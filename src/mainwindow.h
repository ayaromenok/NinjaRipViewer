#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QSettings;
class YTestScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void createMenus();
    void createToolbars();
    void createDockWidgets();
    void createCentralWidget();

    QSettings   *_settings;
    YTestScene  *_testScene;
};

#endif // MAINWINDOW_H
