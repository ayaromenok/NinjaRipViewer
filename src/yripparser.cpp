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
