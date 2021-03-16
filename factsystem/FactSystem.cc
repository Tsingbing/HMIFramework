/// @file
///

#include "FactSystem.h"
#include "FactGroup.h"

#include <QtQml>

const char* FactSystem::_factSystemQmlUri = "HMI.FactSystem";

FactSystem::FactSystem(XApplication* app, Toolbox* toolbox)
    : Tool(app, toolbox)
{
}

void FactSystem::setToolbox(Toolbox* toolbox)
{
    Tool::setToolbox(toolbox);

    qmlRegisterType<Fact>(_factSystemQmlUri, 1, 0, "Fact");
    qmlRegisterType<FactMetaData>(_factSystemQmlUri, 1, 0, "FactMetaData");
    qmlRegisterUncreatableType<FactGroup>(_factSystemQmlUri, 1, 0, "FactGroup", "ReferenceOnly");
}
