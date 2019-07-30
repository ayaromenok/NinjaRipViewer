#ifndef YRIPPARSER_H
#define YRIPPARSER_H

#include <QObject>
#include <Qt3DCore/QEntity>

class YRipParser : public Qt3DCore::QEntity
{
public:
    YRipParser(Qt3DCore::QEntity *parent);
    ~YRipParser();
    bool parseFile(const QString &fileName);
    void fileInfo();

private:
    Qt3DCore::QEntity           *_parent;
    QString                     _fileName;
};

#endif // YRIPPARSER_H
