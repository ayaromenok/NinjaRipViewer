#include "ytestscene.h"

#include <Qt3DCore>
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DExtras>

YTestScene::YTestScene(Qt3DCore::QEntity *parent) : Qt3DCore::QEntity(parent)
{
    addTorusTo(this);
    addConeTo(this);
}

void
YTestScene::addTorusTo(Qt3DCore::QEntity *entity) {

    Qt3DCore::QEntity *torusEntity = new Qt3DCore::QEntity(entity);
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh();

    torusMesh->setRadius(1.0f);
    torusMesh->setMinorRadius(0.1f);
    torusMesh->setRings(40);
    torusMesh->setSlices(16);

    Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform();
    torusTransform->setScale3D(QVector3D(1.0f, 1.0f, 0.5f));
    //torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
    //torusTransform->setTranslation(QVector3D(5.0f, 0.0f, 0.0f));
    //torusTransform->setScale(2.0f);

    Qt3DExtras::QPhongMaterial *torusMat = new Qt3DExtras::QPhongMaterial();
    torusMat->setDiffuse(QColor(QRgb(0x0FFF0F)));

    torusEntity->addComponent(torusMesh);
    torusEntity->addComponent(torusMat);
    torusEntity->addComponent(torusTransform);
}

void
YTestScene::addConeTo(Qt3DCore::QEntity *entity) {

    Qt3DCore::QEntity *coneEntity = new Qt3DCore::QEntity(entity);
    Qt3DExtras::QConeMesh *coneMesh = new Qt3DExtras::QConeMesh();

    coneMesh->setTopRadius(0.1f);
    coneMesh->setBottomRadius(1.0f);
    coneMesh->setLength(3);
    coneMesh->setRings(40);
    coneMesh->setSlices(16);

    Qt3DCore::QTransform *coneTransform = new Qt3DCore::QTransform();
    coneTransform->setTranslation(QVector3D(0.0f, 0.0f, -2.0f));

    Qt3DExtras::QPhongMaterial *coneMat = new Qt3DExtras::QPhongMaterial();
    coneMat->setDiffuse(QColor(QRgb(0x0F0FFF)));

    coneEntity->addComponent(coneMesh);
    coneEntity->addComponent(coneMat);
    coneEntity->addComponent(coneTransform);
}
