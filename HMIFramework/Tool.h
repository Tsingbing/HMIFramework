#ifndef TOOL_H
#define TOOL_H

#include <QObject>

class Toolbox;

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
