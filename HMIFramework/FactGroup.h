#ifndef FACTGROUP_H
#define FACTGROUP_H

#include <QObject>

class FactGroup : public QObject
{
    Q_OBJECT
public:
    explicit FactGroup(QObject *parent = nullptr);

signals:

};

#endif // FACTGROUP_H
