#include "VideoManager.h"
#include <QCameraInfo>
#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>

VideoManager::VideoManager(XApplication* app, Toolbox* toolbox)
    : Tool(app, toolbox)
{
}

void VideoManager::setToolbox(Toolbox* toolbox)
{
    Tool::setToolbox(toolbox);
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    qmlRegisterUncreatableType<VideoManager>("HMI.VideoManager", 1, 0, "VideoManager", "Reference only");
    _toolbox = toolbox;

    _updateUVC();
}

void VideoManager::_updateUVC()
{

    //QString            videoSource = _videoSettings->videoSource()->rawValue().toString();
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo& cameraInfo : cameras)
    {
        //if (cameraInfo.description() == videoSource)
        {
            _videoSourceID = cameraInfo.deviceName();
            //emit videoSourceIDChanged();
            qCDebug(VideoManagerLog) << "Found USB source:" << _videoSourceID << " Name:" << cameraInfo.description();
            //break;
        }
    }
}
