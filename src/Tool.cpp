#include "Tool.h"
#include "Toolbox.h"

Tool::Tool(Toolbox *toolbox)
    : QObject(toolbox)
    , _toolbox(nullptr)
{
//qDebug() << QString(APPLICATION_NAME);
}

void Tool::setToolbox(Toolbox *toolbox)
{
    _toolbox = toolbox;
}
