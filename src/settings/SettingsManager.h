#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include "Tool.h"
#include "Toolbox.h"

class SettingsManager : public Tool
{
    Q_OBJECT
public:
    SettingsManager(Toolbox* toolbox);

    // Override from Tool
    virtual void setToolbox(Toolbox *toolbox);
};

#endif // SETTINGSMANAGER_H
