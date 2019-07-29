#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

namespace Qt3DExtras {
    class Qt3DWindow;
    class QOrbitCameraController;
};
namespace Qt3DCore {
    class QEntity;
};

class YTestScene;

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

signals:

public slots:
    void                            setCamPersp();
    void                            setCamFront();
    void                            setCamTop();
    void                            setCamLeft();
    void                            setRootEntity(Qt3DCore::QEntity *root);

private:

    Qt3DExtras::Qt3DWindow              *_view;
    Qt3DCore::QEntity                   *_root;
    Qt3DExtras::QOrbitCameraController  *_camCtrl;
};

#endif // VIEW_H
