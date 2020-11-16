#include "Tool.h"
#include "Toolbox.h"

Tool::Tool(Toolbox *toolbox)
    : QObject(toolbox)
    , _toolbox(0)
{
//qDebug() << QString(APPLICATION_NAME);
}

void Tool::setToolbox(Toolbox *toolbox)
{
    _toolbox = toolbox;
}
