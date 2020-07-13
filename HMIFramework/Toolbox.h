#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

class Toolbox : public QObject
{
    Q_OBJECT
public:
    explicit Toolbox(QObject *parent = nullptr);

signals:

};

#endif // TOOLBOX_H
