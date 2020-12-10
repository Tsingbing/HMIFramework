#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <QObject>
#include "Tool.h"
#include "CanLink.h"
#include "CanLinkProtocol.h"

/// @说明 管理通讯连接
///
/// 链接管理器组织物理链接。它可以管理任意链接，并负责连接它们，以及分配正确的协议实例以将链接数据传输到应用程序中。

class LinkManager : public Tool
{
    Q_OBJECT
public:
    LinkManager(Toolbox* toolbox);
    ~LinkManager();
    CanLink* canlink() {return _canlink;}

    LinkInterface* createConnectedLink(CanLinkConfiguration* config);
    bool connectLink(LinkInterface* link);
    void disconnectLink(LinkInterface* link);

    ///< 覆写Tool函数
    virtual void setToolbox(Toolbox *toolbox);
private:

private:
    CanLink *_canlink = nullptr;
    CanLinkProtocol *_canlinkProtocol = nullptr;
};

#endif // LINKMANAGER_H
