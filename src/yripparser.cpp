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
            << "\nf:"   << 0
            << "v:"     << 0
            << "n:"     << 0
            << "tc:"    << 0;
}

bool
YRipParser::parseRipFileBody(QFile &file)
{
    bool result = false;
    QByteArray baFaceCount = file.read(4);
    std::reverse(baFaceCount.begin(), baFaceCount.end());
    QByteArray baVertexCount = file.read(4);
    std::reverse(baVertexCount.begin(), baVertexCount.end());
    QByteArray baVertexSize = file.read(4);
    QByteArray baNumOfTex = file.read(4);
    QByteArray baNumShaders = file.read(4);
    QByteArray baNumOfVA = file.read(4);
    bool ok;
    qInfo() << "baFC" << baFaceCount << baFaceCount.toUInt(&ok,16) << (int)baFaceCount.at(3) ;
    qInfo() << "ok?" << ok;
    qInfo() << "baVC" << baVertexCount << baVertexCount.toLong(&ok);
    qInfo() << "ok?" << ok;
    return result;
}
