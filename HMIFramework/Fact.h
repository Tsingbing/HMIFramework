#ifndef FACT_H
#define FACT_H

#include <QObject>

class Fact : public QObject
{
    Q_OBJECT
public:
    explicit Fact(QObject *parent = nullptr);

signals:

};

#endif // FACT_H
