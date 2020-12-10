#ifndef CANLINKDECODER_H
#define CANLINKDECODER_H

#include <QObject>
#include <QThread>

class CanLinkDecoder : public QThread
{
    Q_OBJECT
public:
    explicit CanLinkDecoder(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CANLINKDECODER_H
