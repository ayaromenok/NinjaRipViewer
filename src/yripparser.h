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
    bool parseRipFileIndexData(QFile &file);
    bool parseRipFileVertexData(QFile &file);

    bool createEntity();
    //utils
    quint32     byte4LEtoUInt32(QByteArray byte4);
    float       byte4LEtoFloat32(QByteArray byte4);
    bool        readStringNullTerm(QFile &file, QString &string);

    Qt3DCore::QEntity           *_parent;
    QString                     _fileName;

    quint32                     _fVersion;
    quint32                     _fcNum;
    quint32                     _vtxNum;
    quint32                     _vtxSize;
    quint32                     _texNum;
    quint32                     _shaderNum;
    quint32                     _vAttrNum;

    quint32                     _vX;
    quint32                     _vY;
    quint32                     _vZ;
    quint32                     _vTemp;

    quint32                     _nX;
    quint32                     _nY;
    quint32                     _nZ;
    quint32                     _nTemp;

    quint32                     _tcU;
    quint32                     _tcV;
    quint32                     _tcTemp;

    QStringList                 *_textures;
    QStringList                 *_shaders;
};

#endif // YRIPPARSER_H
