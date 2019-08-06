#ifndef YRIPPARSER_H
#define YRIPPARSER_H

#include <QObject>
#include <QFile>
#include <Qt3DCore/QEntity>

class YCustomMesh;

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

    bool                        _isNormalPresent;
    quint32                     _nX;
    quint32                     _nY;
    quint32                     _nZ;
    quint32                     _nTemp;

    bool                        _isTC0Present;
    quint32                     _tcU;
    quint32                     _tcV;
    quint32                     _tcTemp;

    bool                        _isColorPresent;
    quint32                     _cR;
    quint32                     _cG;
    quint32                     _cB;
    quint32                     _cA;
    quint32                     _cTemp;

   //bool                        _isTC1Present;
   // bool                        _isTBNPresent;
    QStringList                 *_textures;
    QStringList                 *_shaders;

    YCustomMesh                 *_mesh;
    QByteArray                  *_baVBuffData;
    QByteArray                  *_baIBuffData;
};

#endif // YRIPPARSER_H
