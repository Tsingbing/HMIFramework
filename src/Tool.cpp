#include "Tool.h"
#include "Toolbox.h"

Tool::Tool(XApplication* app, Toolbox* toolbox)
    : QObject(toolbox)
    , _app(app)
    , _toolbox(nullptr)
{
    //qDebug() << QString(APPLICATION_NAME);
}

void Tool::setToolbox(Toolbox* toolbox)
{
    _toolbox = toolbox;
}
