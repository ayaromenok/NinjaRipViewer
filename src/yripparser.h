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
    bool parseRipFileBody(QFile &file);
    Qt3DCore::QEntity           *_parent;
    QString                     _fileName;
};

#endif // YRIPPARSER_H
