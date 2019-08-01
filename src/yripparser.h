#ifndef YRIPPARSER_H
#define YRIPPARSER_H

#include <QObject>
#include <QFile>
#include <Qt3DCore/QEntity>

class YRipParser : public Qt3DCore::QEntity
{
public:
    YRipParser(Qt3DCore::QEntity *parent);
    ~YRipParser();
    bool parseFile(const QString &fileName);
    void fileInfo();

private:
    bool parseRipFileMagicNum(QFile &file);
    bool parseRipFileHeader(QFile &file);
    bool parseRipFileVAttribHeader(QFile &file);
    quint32 byte4LEtoUInt32(QByteArray byte4);
    float byte4LEtoUFloat32(QByteArray byte4);
    bool readStringNullTerm(QFile &file, QString &string);
    Qt3DCore::QEntity           *_parent;
    QString                     _fileName;

    quint32                     _fVersion;
    quint32                     _fcNum;
    quint32                     _vtxNum;
    quint32                     _vtxSize;
    quint32                     _texNum;
    quint32                     _shaderNum;
    quint32                     _vAttrNum;
};

#endif // YRIPPARSER_H
