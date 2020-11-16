#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <QObject>
#include "Tool.h"

/// @说明 管理通讯连接
///
/// 链接管理器组织物理链接。它可以管理任意链接，并负责连接它们，以及分配正确的协议实例以将链接数据传输到应用程序中。

class LinkManager : public Tool
{
    Q_OBJECT
public:
    LinkManager(Toolbox* toolbox);
    ~LinkManager();

};

#endif // LINKMANAGER_H
