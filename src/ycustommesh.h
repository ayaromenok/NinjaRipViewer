#ifndef YCUSTOMMESH_H
#define YCUSTOMMESH_H

#include <QObject>
#include <Qt3DCore/QEntity>

namespace Qt3DCore {
    class QTransform;
}
namespace Qt3DRender {
    class QBuffer;
    class QAttribute;
    class QGeometry;
    class QGeometryRenderer;
    class QMaterial;
}

class YCustomMesh : public Qt3DCore::QEntity
{
public:
    YCustomMesh(Qt3DCore::QEntity *parent);
    ~YCustomMesh();

    bool setMeshData(const QByteArray &vBufData, const QByteArray &iBufData);

private:
    bool createEntity();
    bool createTestMesh();
    bool createAttribs();

    Qt3DCore::QEntity               *_parent;
    Qt3DCore::QEntity               *_meshEntity;
    Qt3DRender::QGeometry           *_geom;
    Qt3DRender::QGeometryRenderer   *_meshRenderer;
    Qt3DCore::QTransform            *_transform;
    Qt3DRender::QMaterial           *_mtl;

    Qt3DRender::QBuffer             *_vBuf;
    Qt3DRender::QBuffer             *_iBuf;

    Qt3DRender::QAttribute          *_attrPos;
    Qt3DRender::QAttribute          *_attrNormal;
    Qt3DRender::QAttribute          *_attrColor;
    Qt3DRender::QAttribute          *_attrIndex;

    quint32                         _numOfFaces;
    quint32                         _numOfVtx;
    quint32                         _numOfVtxInFace;
};

#endif // YCUSTOMMESH_H
