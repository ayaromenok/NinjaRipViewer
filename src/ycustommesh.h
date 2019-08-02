#ifndef YCUSTOMMESH_H
#define YCUSTOMMESH_H

#include <QObject>
#include <Qt3DCore/QEntity>

namespace Qt3DRender {
    class QBuffer;
}

class YCustomMesh : public Qt3DCore::QEntity
{
public:
    YCustomMesh(Qt3DCore::QEntity *parent);
    ~YCustomMesh();

private:
    bool createEntity();
    bool createTestMesh();

    Qt3DCore::QEntity       *_parent;
    Qt3DRender::QBuffer     *_vBuf;
    Qt3DRender::QBuffer     *_iBuf;
};

#endif // YCUSTOMMESH_H
