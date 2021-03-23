#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "HMILoggingCategory.h"
#include "Tool.h"
#include "Toolbox.h"
#include <QObject>

class VideoManager : public Tool
{
    Q_OBJECT

public:
    VideoManager(XApplication* app, Toolbox* toolbox);
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString videoSourceID READ videoSourceID CONSTANT)
    QString id() { return "100id"; }
    // Override from Tool
    virtual void setToolbox(Toolbox* toolbox);

    QString videoSourceID() const { return _videoSourceID; }

protected slots:
    void _updateUVC();

protected:
    QString _videoSourceID;
};

#endif // VIDEOMANAGER_H
