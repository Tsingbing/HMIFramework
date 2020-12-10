#ifndef LINKINTERFACE_H
#define LINKINTERFACE_H

#include <QObject>
#include <QThread>

/**
* @brief 定义了用于通信的所有链路的接口
* 例如CanLink, TcpLink都可以继承此接口
*
**/

class LinkInterface : public QThread
{
    Q_OBJECT

public:
    //virtual void requestReset() = 0;

    virtual bool isConnected() const = 0;

    /* Connection characteristics */
    //virtual qint64 getConnectionSpeed() const = 0;

    /**
     * @brief Connect this interface logically
     *
     * @return True if connection could be established, false otherwise
     **/
    virtual bool _connect(void) = 0;
    virtual void _disconnect(void) = 0;

protected:
    LinkInterface();

private slots:
    virtual void _writeBytes(const QByteArray) = 0;

signals:
    void bytesRecived(LinkInterface* link, QByteArray data);
    void connected();
    void disconnected();
};

#endif // LINKINTERFACE_H
