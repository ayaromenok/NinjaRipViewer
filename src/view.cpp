#include "view.h"

#include <QtWidgets>

#include <Qt3DCore>
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DExtras>

View::View(QWidget *parent) : QWidget(parent) {
    _view  = new Qt3DExtras::Qt3DWindow();
    _view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x8F0F0F)));
    QWidget *container = QWidget::createWindowContainer(_view);
    QSize scrnSize = _view->screen()->size();
    qDebug() << "screensize" << scrnSize;
    container->setMinimumSize(QSize(640,450));
    container->setMaximumSize(scrnSize);

    QVBoxLayout* loutV = new QVBoxLayout(this);
    loutV->setAlignment(Qt::AlignTop);
    loutV->addWidget(container);

    Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect();
    _view->registerAspect(input);

    _root = new Qt3DCore::QEntity();
    _view->setRootEntity(_root);

    _camCtrl = new Qt3DExtras::QOrbitCameraController(_root);
    _camCtrl->setCamera(_view->camera());

    _capture = new Qt3DRender::QRenderCapture;
    _view->activeFrameGraph()->setParent(_capture);
    _view->setActiveFrameGraph(_capture);

}

void
View::setRootEntity(Qt3DCore::QEntity *root){
    if(root) {
        root->setParent(_root);
     }
    else {
        qDebug() << "wrong setting View::RootEntity";
    }

}

void
View::setCamPersp() {
    Qt3DRender::QCamera *cameraEntity = _view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(3.0f, 5.0f, 5.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));


}

void
View::setCamFront() {
    Qt3DRender::QCamera *cameraEntity = _view->camera();

    cameraEntity->lens()->setOrthographicProjection(-8.0f, 8.0f, -4.5f, 4.5f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
}

void
View::setCamTop() {
    Qt3DRender::QCamera *cameraEntity = _view->camera();
    cameraEntity->lens()->setOrthographicProjection(-8.0f, 8.0f, -4.5f, 4.5f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 20.0f, 0));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
}

void
View::setCamLeft() {
    Qt3DRender::QCamera *cameraEntity = _view->camera();
    cameraEntity->lens()->setOrthographicProjection(-8.0f, 8.0f, -4.5f, 4.5f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(20.0f, 0, 0));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
}

void
View::captureToFile()
{
    _captureReply = _capture->requestCapture();
    QObject::connect(_captureReply, &Qt3DRender::QRenderCaptureReply::completed,
                                              this, &View::onCaptureCompleted);
}

void
View::onCaptureCompleted() {
    QDateTime dt;
    _fNameScr.clear();
    _fNameScr.append("screenshot");
    _fNameScr.append(QString::number(_captureReply->captureId()));
    _fNameScr.append(".jpg");

    if (_captureReply->isComplete()) {
        if (_captureReply->saveImage(_fNameScr)) {
            qInfo() << "image saved" << _fNameScr;
        } else {
            qInfo() << "Can't save image";
        }
    } else {
        qInfo("Capture is NoK");
    };
    delete _captureReply;
    _captureReply = nullptr;
}
