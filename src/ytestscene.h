#ifndef YTESTSCENE_H
#define YTESTSCENE_H

#include <QObject>
#include <Qt3DCore/QEntity>


class YTestScene : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    explicit YTestScene(Qt3DCore::QEntity *parent = nullptr);

signals:

public slots:
    void                            addTorusTo(Qt3DCore::QEntity *entity);
    void                            addConeTo(Qt3DCore::QEntity *entity);
};

#endif // YTESTSCENE_H
