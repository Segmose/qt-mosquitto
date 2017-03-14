#ifndef QTMOSQ_H
#define QTMOSQ_H

#include "QObject"
#include "mosquittopp.h"

using namespace mosqpp;

class qtmosq : public QObject, public mosquittopp
{
    Q_OBJECT

public:
    qtmosq(const char *id = NULL, bool clean_session = true) : mosquittopp (id, clean_session) {MID = 0;}
    virtual ~qtmosq() {}

    void on_connect(int result) final
    {
        if (!result)
        {
            //subscribe(NULL, "$SYS/#", 2);
            emit connected();
        }
        else
            emit connectEnable();
    }

    void on_publish(int /*id*/) final
    {
        MID++;
        emit messageSent(true);
    }

    void on_subscribe(int mid, int qos_count, const int *granted_qos) final
    {
        if (MID != 0)
            emit subscribed();
        MID++;
    }

    void on_unsubscribe(int mid) final {
      emit unsubscribed();
    }

    void on_message(const mosquitto_message *message) final
    {
        if (message->payloadlen)
        {
            QString s(message->topic);
            s += '>';
            s += (char*) message->payload;
            emit messageReceived(s);
        }
    }

    virtual void on_disconnect(int rc) final {
      emit disconnected(rc);
    }

    int* getMID() {return &MID;}

private:
    int MID;

signals:
    void connected();
    void disconnected(int rc);
    void messageSent(bool);
    void messageReceived(QString);
    void connectEnable();
    void subscribed();
    void unsubscribed();
};

#endif // QTMOSQ_H
