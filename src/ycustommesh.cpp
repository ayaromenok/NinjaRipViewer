#include "ycustommesh.h"

#include <Qt3DCore>
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DExtras>

YCustomMesh::YCustomMesh(Qt3DCore::QEntity *parent)
{
    if (parent){
        _parent = parent;
        createEntity();
    } else {
        qErrnoWarning(-10, "requred Parent QEntity node");
        exit(-10);
    }
}

YCustomMesh::~YCustomMesh()
{

}

bool
YCustomMesh::createEntity()
{
    bool result = false;
    Qt3DRender::QMaterial
            *material = new Qt3DExtras::QPerVertexColorMaterial(_parent);
    Qt3DCore::QEntity
            *mesh = new Qt3DCore::QEntity(_parent);
    Qt3DCore::QTransform
            *transform = new Qt3DCore::QTransform;
    Qt3DRender::QGeometryRenderer
            *meshRenderer = new Qt3DRender::QGeometryRenderer;
    Qt3DRender::QGeometry
            *geom = new Qt3DRender::QGeometry(mesh);

    Qt3DRender::QBuffer
            *vBuf = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, geom);
    Qt3DRender::QBuffer
            *iBuf = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, geom);
    return  result;
}
