#include "yripparser.h"

#include <Qt3DCore>
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DExtras>

YRipParser::YRipParser(Qt3DCore::QEntity *parent)
{
    if (parent){
        _parent = parent;
    } else {
        qErrnoWarning(-10, "requred Parent QEntity node");
        exit(-10);
    }

}

YRipParser::~YRipParser()
{

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
                    QByteArray ripMagickNumber;
                    ripMagickNumber.resize(4);
                    ripMagickNumber[0] = 0xDE;
                    ripMagickNumber[1] = 0xC0;
                    ripMagickNumber[2] = 0xAD;
                    ripMagickNumber[3] = 0xDE;
                    QByteArray chunk;
                    chunk = file.read(4);
                    if (chunk.contains(ripMagickNumber)){
                        qInfo() << "Found Ninja RIP file with" << file.size() << "bytes";
                        parseRipFileBody(file);
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

    return result;
}

void
YRipParser::fileInfo()
{
    qInfo() << "Ninja RIP file:" << _fileName
            << "\nf:"   << _fcNum
            << "v:"     << _vtxNum
            << "vAttr:" << _vAttrNum
            << "tex:"   << _texNum;
}

bool
YRipParser::parseRipFileBody(QFile &file)
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
