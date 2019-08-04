#include "ycustommesh.h"

#include <Qt3DCore>
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DExtras>

YCustomMesh::YCustomMesh(Qt3DCore::QEntity *parent)
{
    _numOfVtxInFace = 3;        //usually 3
    _numOfFaces     = 4;            //for default object it's 4
    _numOfVtx       = 4;
    if (parent){
        _parent = parent;
        _mtl = new Qt3DExtras::QPerVertexColorMaterial(_parent);
        _meshEntity = new Qt3DCore::QEntity(_parent);
        _transform = new Qt3DCore::QTransform;
        _meshRenderer = new Qt3DRender::QGeometryRenderer;
        _geom = new Qt3DRender::QGeometry(_meshEntity);

        _vBuf = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, _geom);
        _iBuf = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, _geom);

        //createEntity();
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
    createAttribs();

    _meshRenderer->setInstanceCount(1);
    _meshRenderer->setIndexOffset(0);
    _meshRenderer->setFirstInstance(0);
    _meshRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Triangles);
    _meshRenderer->setGeometry(_geom);
    _meshRenderer->setVertexCount(_numOfVtx*_numOfVtxInFace);

    _meshEntity->addComponent(_meshRenderer);
    _meshEntity->addComponent(_transform);
    _meshEntity->addComponent(_mtl);

    result = true;

    return  result;
}

bool
YCustomMesh::createAttribs()
{
    bool result = false;
    // Attributes
    _attrPos = new Qt3DRender::QAttribute();
    _attrPos->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    _attrPos->setBuffer(_vBuf);
    _attrPos->setVertexBaseType(Qt3DRender::QAttribute::Float);
    _attrPos->setVertexSize(3);
    _attrPos->setByteOffset(0);
    _attrPos->setByteStride(9 * sizeof(float));
    _attrPos->setCount(_numOfVtx);
    _attrPos->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());

    _attrNormal = new Qt3DRender::QAttribute();
    _attrNormal->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    _attrNormal->setBuffer(_vBuf);
    _attrNormal->setVertexBaseType(Qt3DRender::QAttribute::Float);
    _attrNormal->setVertexSize(3);
    _attrNormal->setByteOffset(3 * sizeof(float));
    _attrNormal->setByteStride(9 * sizeof(float));
    _attrNormal->setCount(_numOfVtx);
    _attrNormal->setName(Qt3DRender::QAttribute::defaultNormalAttributeName());

    _attrColor = new Qt3DRender::QAttribute();
    _attrColor->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    _attrColor->setBuffer(_vBuf);
    _attrColor->setVertexBaseType(Qt3DRender::QAttribute::Float);
    _attrColor->setVertexSize(3);
    _attrColor->setByteOffset(6 * sizeof(float));
    _attrColor->setByteStride(9 * sizeof(float));
    _attrColor->setCount(_numOfVtx);
    _attrColor->setName(Qt3DRender::QAttribute::defaultColorAttributeName());

    Qt3DRender::QAttribute *_attrIndex = new Qt3DRender::QAttribute();
    _attrIndex->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    _attrIndex->setBuffer(_iBuf);
    _attrIndex->setVertexBaseType(Qt3DRender::QAttribute::UnsignedShort);
    _attrIndex->setVertexSize(1);
    _attrIndex->setByteOffset(0);
    _attrIndex->setByteStride(0);
    _attrIndex->setCount(_numOfVtx*_numOfVtxInFace);

    _geom->addAttribute(_attrPos);
    _geom->addAttribute(_attrNormal);
    _geom->addAttribute(_attrColor);
    _geom->addAttribute(_attrIndex);
    return result;
}
bool
YCustomMesh::createTestMesh()
{
    bool result = false;
    QByteArray vertexBufferData;
    vertexBufferData.resize(_numOfVtx * (3 + 3 + 3) * sizeof(float));

    // Vertices
    QVector3D v0(-1.0f, 0.0f, -1.0f);
    QVector3D v1(1.0f, 0.0f, -1.0f);
    QVector3D v2(0.0f, 1.0f, 0.0f);
    QVector3D v3(0.0f, 0.0f, 1.0f);

    // Faces Normals
    QVector3D n023 = QVector3D::normal(v0, v2, v3);
    QVector3D n012 = QVector3D::normal(v0, v1, v2);
    QVector3D n310 = QVector3D::normal(v3, v1, v0);
    QVector3D n132 = QVector3D::normal(v1, v3, v2);

    // Vector Normals
    QVector3D n0 = QVector3D(n023 + n012 + n310).normalized();
    QVector3D n1 = QVector3D(n132 + n012 + n310).normalized();
    QVector3D n2 = QVector3D(n132 + n012 + n023).normalized();
    QVector3D n3 = QVector3D(n132 + n310 + n023).normalized();

    // Colors
    QVector3D red(1.0f, 0.0f, 0.0f);
    QVector3D green(0.0f, 1.0f, 0.0f);
    QVector3D blue(0.0f, 0.0f, 1.0f);
    QVector3D white(1.0f, 1.0f, 1.0f);

    QVector<QVector3D> vertices = QVector<QVector3D>()
            << v0 << n0 << red
            << v1 << n1 << blue
            << v2 << n2 << green
            << v3 << n3 << white;

    float *rawVertexArray = reinterpret_cast<float *>(vertexBufferData.data());
    int idx = 0;

    Q_FOREACH (const QVector3D &v, vertices) {
        rawVertexArray[idx++] = v.x();
        rawVertexArray[idx++] = v.y();
        rawVertexArray[idx++] = v.z();
    }

    // Indices (12)
    QByteArray indexBufferData;
    indexBufferData.resize(_numOfVtx * _numOfVtxInFace * sizeof(ushort));
    ushort *rawIndexArray = reinterpret_cast<ushort *>(indexBufferData.data());

    // Front
    rawIndexArray[0] = 0;
    rawIndexArray[1] = 1;
    rawIndexArray[2] = 2;
    // Bottom
    rawIndexArray[3] = 3;
    rawIndexArray[4] = 1;
    rawIndexArray[5] = 0;
    // Left
    rawIndexArray[6] = 0;
    rawIndexArray[7] = 2;
    rawIndexArray[8] = 3;
    // Right
    rawIndexArray[9] = 1;
    rawIndexArray[10] = 3;
    rawIndexArray[11] = 2;

    _vBuf->setData(vertexBufferData);
    _iBuf->setData(indexBufferData);

    return  result;
}

bool
YCustomMesh::setMeshData(const QByteArray &vBufData, const QByteArray &iBufData)
{
    bool result = false;
    if ((vBufData.length() > 0) & (iBufData.length() > 0)){
        qInfo() << "Correct CustomMesh input data";
        _vBuf->setData(vBufData);
        _iBuf->setData(iBufData);
    } else {
        qWarning() << "WRONG CustomMesh input data, using default";
        createTestMesh();
    }
    createEntity();
    return  result;
}
