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
