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
                    if (parseRipFileMagicNum(file)){
                        qInfo() << "Found Ninja RIP file with" << file.size() << "bytes";
                        parseRipFileHeader(file);
                        parseRipFileVAttribHeader(file);
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
    QByteArray baZero;
    baZero.resize(1);
    baZero[0] = 0x00;
    QByteArray baV("POSITION"); //V for Vertex
    QByteArray baN("NORMAL");
    baN.insert(0,baZero);
    baN.append(baZero);
    QByteArray baTC("TEXCOORD"); //may be necessary to bake texture to color
    //QByteArray baTNG("TANGENT"); //not necessary for now
    //QByteArray baBN("BINORMAL"); //not necessary for now

    QString string;
    if (readStringNullTerm(file, string)) {
        qInfo() << string;
    }
            /*
    QByteArray chunk;
    chunk = file.read(8);
    if (chunk.contains(baV)){
        quint32 _vIndex = byte4LEtoUInt32(file.read(4));
        quint32 _vOffset = byte4LEtoUInt32(file.read(4));
        quint32 _vSize =  byte4LEtoUInt32(file.read(4));
        quint32 _vNumOfElem =  byte4LEtoUInt32(file.read(4));
        qInfo() << baV << _vIndex << _vOffset << _vSize << _vNumOfElem;
        result = true;
    }

    //need clarification from spec
    chunk = file.read(12);

    chunk = file.read(8);
    if (chunk.contains(baN)){
        quint32 _nIndex = byte4LEtoUInt32(file.read(4));
        quint32 _nOffset = byte4LEtoUInt32(file.read(4));
        quint32 _nSize =  byte4LEtoUInt32(file.read(4));
        quint32 _nNumOfElem =  byte4LEtoUInt32(file.read(4));
        qInfo() << baN << _nIndex << _nOffset << _nSize << _nNumOfElem;
        result = true;
    }

    //need clarification from spec
    chunk = file.read(12);

    chunk = file.read(8);
    if (chunk.contains(baTC)){
        quint32 _tcIndex = byte4LEtoUInt32(file.read(4));
        quint32 _tcOffset = byte4LEtoUInt32(file.read(4));
        quint32 _tcSize =  byte4LEtoUInt32(file.read(4));
        quint32 _tcNumOfElem =  byte4LEtoUInt32(file.read(4));
        qInfo() << baTC << _tcIndex << _tcOffset << _tcSize << _tcNumOfElem;
        result = true;
    }
    //qInfo() << baV << baN << baTC;
            */
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

bool
YRipParser::readStringNullTerm(QFile &file, QString &string)
{
    char ch;
    while (file.getChar(&ch)){
        if (ch != 0x00) {
            string.append(ch);
            qInfo() << ch;
        } else {
            return true;
        }
    }
    return false;
}
