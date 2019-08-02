#ifndef YCUSTOMMESH_H
#define YCUSTOMMESH_H

#include <QObject>
#include <Qt3DCore/QEntity>

class YCustomMesh : public Qt3DCore::QEntity
{
public:
    YCustomMesh(Qt3DCore::QEntity *parent);
    ~YCustomMesh();

private:
    bool createEntity();

    Qt3DCore::QEntity       *_parent;
    QByteArray              *_vData;
    QByteArray              *_iData;
};

#endif // YCUSTOMMESH_H
