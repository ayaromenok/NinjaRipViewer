#ifndef YRIPPARSER_H
#define YRIPPARSER_H

#include <QObject>
#include <Qt3DCore/QEntity>

class YRipParser : public Qt3DCore::QEntity
{
public:
    YRipParser(Qt3DCore::QEntity *parent = nullptr);

};

#endif // YRIPPARSER_H
