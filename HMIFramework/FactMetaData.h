#ifndef FACTMETADATA_H
#define FACTMETADATA_H

#include <QObject>
#include <QWidget>

class FactMetaData : public QObject
{
    Q_OBJECT
public:
    explicit FactMetaData(QObject *parent = nullptr);

signals:

};

#endif // FACTMETADATA_H
