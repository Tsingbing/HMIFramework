#ifndef TOOL_H
#define TOOL_H

#include <QObject>

class Toolbox;

/*
所有工具都必须是Toolbox的父级，并经历两个阶段的创建。在构造函数中，
工具箱只应传递给Tool构造函数以进行正确的父子关系。不应在受保护成员中引用或设置它。
然后在setToolbox调用的第二阶段中，您可以引用工具箱。
*/
class Tool : public QObject
{
    Q_OBJECT
public:
    Tool(Toolbox* toolbox);

    virtual void setToolbox(Toolbox* toolbox);

signals:

protected:
    Toolbox* _toolbox;
};

#endif // TOOL_H
