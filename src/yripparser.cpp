#include "yripparser.h"

#include <Qt3DCore>
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DExtras>

#include "ycustommesh.h"

YRipParser::YRipParser(Qt3DCore::QEntity *parent)
{
    if (parent){
        _parent = parent;       
    } else {
        qErrnoWarning(-10, "requred Parent QEntity node");
        exit(-10);
    }
    _textures = new QStringList();
    _shaders = new QStringList();
    _baVBuffData = new QByteArray();
    _baIBuffData = new QByteArray();
    _isNormalPresent = false;
    _isTC0Present = false;
    _isColorPresent = false;
}

YRipParser::~YRipParser()
{
    _textures->clear();
    if(_textures->isEmpty()){
        delete _textures;
    }
    _shaders->clear();
    if(_shaders->isEmpty()){
        delete _shaders;
    }

    _baVBuffData->clear();
    if(_baVBuffData->isEmpty()){
        delete _baVBuffData;
    }

    _baIBuffData->clear();
    if(_baIBuffData->isEmpty()){
        delete _baIBuffData;
    }
}

bool
YRipParser::parseFile(const QString &fileName)
{
    bool result = false;
    if (fileName.length() > 0) {
        _fileName = fileName;
        QFileInfo fi(_fileName);
        if (fi.exists()){
            QFile file(_fileName);
            if (file.open(QIODevice::ReadOnly)){
                    if (parseRipFileMagicNum(file)){
                        qInfo() << "Found Ninja RIP file with" << file.size() << "bytes";
                        parseRipFileHeader(file);
                        parseRipFileVAttribHeader(file);
                        parseRipFileIndexData(file);
                        parseRipFileVertexData(file);
                        result = true;
                    } else {
                        qWarning() << "file" << fileName << "is not a Ninja RIP";
                    }
            } else {
                qWarning() << "file" << fileName << "can't be open";
            }
        }
    } else {
        qWarning() << "required file name as string";
        _fileName = ":/res/stub/cube.rip";
    }

    createEntity();
    return result;
}

void
YRipParser::fileInfo()
{
    qInfo() << ">> Ninja RIP file info:" << _fileName
            << "\nf:"   << _fcNum
            << "v:"     << _vtxNum
            << "vAttr:" << _vAttrNum
            << "tex:"   << _texNum;
}

bool
YRipParser::parseRipFileMagicNum(QFile &file)
{
    bool result = false;

    QByteArray ripMagickNumber;
    ripMagickNumber.resize(4);
    ripMagickNumber[0] = 0xDE;
    ripMagickNumber[1] = 0xC0;
    ripMagickNumber[2] = 0xAD;
    ripMagickNumber[3] = 0xDE;
    QByteArray chunk;
    chunk = file.read(4);
    if (chunk.contains(ripMagickNumber)){
        result = true;
    }
    return result;
}

bool
YRipParser::parseRipFileHeader(QFile &file)
{
    bool result = false;

    _fVersion = byte4LEtoUInt32(file.read(4));
    _fcNum = byte4LEtoUInt32(file.read(4));
    _vtxNum =  byte4LEtoUInt32(file.read(4));
    _vtxSize =  byte4LEtoUInt32(file.read(4));
    _texNum =  byte4LEtoUInt32(file.read(4));
    _shaderNum =  byte4LEtoUInt32(file.read(4));
    _vAttrNum =  byte4LEtoUInt32(file.read(4));

    if ((_fcNum > 0) &  (_vtxNum > 0)) {
        result = true;
    }
    return result;
}

bool
YRipParser::parseRipFileVAttribHeader(QFile &file)
{
    bool result = false;
    // "POSITION", "NORMAL", "TEXCOORD","TANGENT", "BINORMAL"
    QString string;
    _vTemp = 0;
    _nTemp = 0;
    _tcTemp = 0;
    _cTemp = 0;
    quint32 index, offset, size, numOfElem;
    for (quint32 i=0; i<_vAttrNum; i++){
        string.clear();
        if (readStringNullTerm(file, string)) {
            index = byte4LEtoUInt32(file.read(4));
            offset = byte4LEtoUInt32(file.read(4));
            size =  byte4LEtoUInt32(file.read(4));
            numOfElem =  byte4LEtoUInt32(file.read(4));
            qInfo() << string << index << offset << size << numOfElem;
            for (quint32 j=0; j<numOfElem; j++){
                quint32 elem = byte4LEtoUInt32(file.read(4));
                qInfo() << elem;
            }

            if (string.contains("POSITION")){
                if (0 == _vTemp){
                    _vX = offset/4;
                    _vY = _vX + 1;
                    _vZ = _vX + 2;
                    _vTemp++;
                    if (1 == _vY){ //any mesh should contain _vX=0, _vY=1, _vZ=2
                        result = true;
                    }
                }
            }
            if (string.contains("NORMAL")){
                if (0 == _nTemp){
                    _nX = offset/4;
                    _nY = _nX + 1;
                    _nZ = _nX + 2;
                    _nTemp++;
                    _isNormalPresent = true;
                }

            }
            if (string.contains("TEXCOORD")){
                if (0 == _tcTemp){
                    _tcU = offset/4;
                    _tcV = _tcU + 1;
                    _tcTemp++;
                    _isTC0Present = true;
                }
            }
            if (string.contains("COLOR")){
                if (0 == _cTemp){
                    _cR = offset/4;
                    _cG = _cR + 1;
                    _cB = _cR + 2;
                    _cA = _cR + 3;
                    _cTemp++;
                    _isColorPresent = true;
                }

            }
        }
    }
    qInfo() << "v" << _vX << _vY << _vZ;
    if (_isNormalPresent) {
        qInfo() << "n" << _nX << _nY << _nZ;
    }
    if (_isColorPresent) {
        qInfo() << "c" << _cR << _cG << _cB << _cA;
    }
    if (_isTC0Present) {
        qInfo() << "tc" << _tcU << _tcV;
    }


    //textures
    if (_texNum >0) {
        for (quint32 i=0; i<_texNum; i++){
            QString string;
            readStringNullTerm(file, string);
            _textures->append(string);
        }
        qInfo() << "textures:" << _textures->toStdList();
    }

    //shaders
    if (_shaderNum >0) {
        for (quint32 i=0; i<_shaderNum; i++){
            QString string;
            readStringNullTerm(file, string);
            _shaders->append(string);
        }
        qInfo() << "shaders: " << _shaders->toStdList();
    }

    return result;
}

bool
YRipParser::parseRipFileIndexData(QFile &file)
{
    bool result = false;
    _baIBuffData->resize(_fcNum * 3 * sizeof(quint32));
    _baIBuffData->fill(0x00);
    quint32 *rawIndexArray = reinterpret_cast<quint32*>(_baIBuffData->data());

    for (quint32 i=0; i<_fcNum; i++){
        quint32 i0 = byte4LEtoUInt32(file.read(4));
        quint32 i1 = byte4LEtoUInt32(file.read(4));
        quint32 i2 = byte4LEtoUInt32(file.read(4));
        qInfo() << "face:" << i << "[" << i0 << i1 << i2 << "]";
        rawIndexArray[i*3] = i0;
        rawIndexArray[i*3+1] = i1;
        rawIndexArray[i*3+2] = i2;
    }

    result = true;
    return result;
}

bool
YRipParser::parseRipFileVertexData(QFile &file)
{
    bool result = false;
    _baVBuffData->resize(_vtxNum * (3+3+3) * sizeof(float));
    _baVBuffData->fill(0x00);
    float *rawVertexArray = reinterpret_cast<float*>(_baVBuffData->data());

    for (quint32 i=0; i<_vtxNum; i++){
        float vx = byte4LEtoFloat32(file.read(4));
        float vy = byte4LEtoFloat32(file.read(4));
        float vz = byte4LEtoFloat32(file.read(4));
        float nx = byte4LEtoFloat32(file.read(4));
        float ny = byte4LEtoFloat32(file.read(4));
        float nz = byte4LEtoFloat32(file.read(4));
        float tcU = byte4LEtoFloat32(file.read(4));
        float tcV = byte4LEtoFloat32(file.read(4));

        qInfo() << "v:" << i << "pos:" << vx << vy << vz <<
                   "n:" << nx << ny << nz << "tc0:" << tcU << tcV;

        rawVertexArray[i*3] = vx;
        rawVertexArray[i*3+1] = vy;
        rawVertexArray[i*3+2] = vz;
        rawVertexArray[i*3+3] = nx;
        rawVertexArray[i*3+4] = ny;
        rawVertexArray[i*3+5] = nz;
        rawVertexArray[i*3+6] = tcU;
        rawVertexArray[i*3+7] = tcV;
        rawVertexArray[i*3+8] = 0.0f;
    }
    result = true;
    return result;
}

bool
YRipParser::createEntity()
{
    bool result = false;

// add YCustomMesh here
    QByteArray vBuffData;
    QByteArray iBuffData;
    _mesh = new YCustomMesh(_parent);
    _mesh->setMeshData(*_baVBuffData, *_baIBuffData);
    qInfo() << "mesh" << _mesh->childNodes();

    result = true;
    return result;
}

quint32
YRipParser::byte4LEtoUInt32(QByteArray byte4)
{
    quint32 result = 0;
    if (byte4.length() == 4){
        result =  (((quint32)byte4.at(3) << 24) & 0xFF000000)
                + (((quint32)byte4.at(2) << 16) &0x00FF0000)
                + (((quint32)byte4.at(1) << 8) & 0x0000FF00)
                + ((quint32)byte4.at(0) & 0x000000FF);
    }
    else {
        qWarning() << "Input byte sequence is not equal to4 bytes";
    }
    return result;
}

float
YRipParser::byte4LEtoFloat32(QByteArray byte4)
{
    union {
        float f;
        quint32 i;
    } result;
    if (byte4.length() == 4){
        result.i =  (((quint32)byte4.at(3) << 24) & 0xFF000000)
                + (((quint32)byte4.at(2) << 16) &0x00FF0000)
                + (((quint32)byte4.at(1) << 8) & 0x0000FF00)
                + ((quint32)byte4.at(0) & 0x000000FF);
    }
    else {
        qWarning() << "Input byte sequence is not equal to4 bytes";
    }
    return result.f;
}

bool
YRipParser::readStringNullTerm(QFile &file, QString &string)
{
    char ch;
    while (file.getChar(&ch)){
        if (ch != 0x00) {
            string.append(ch);
        } else {
            return true;
        }
    }
    return false;
}
