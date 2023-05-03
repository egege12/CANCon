#include<QByteArray>
#include <QCanBus>
#include <QCanBusDevice>
#include <QDebug>
#include <QTimer>
#include <QMap>
#ifndef CANSOCKET_H
#define CANSOCKET_H
struct Senders{
    QByteArray dataToSend;
    int baudRate;
    int timeout;
};
class canSocket{
    struct Senders;
    QMap<QString,QTimer*> timers;

    int function();

};
#endif // CANSOCKET_H

inline int canSocket::function()
{
    QString pluginName = "vectorcan";
    QString interfaceName = "can0"; // VN1610 arayüzüne bağlı olan arayüz ismi
    int baudRate = 500000; // CAN hızı
    int timeout = 100; // zaman aşımı
    QByteArray dataToSend = QByteArray::fromHex("0102030405060708"); // örnek veri

    // CAN arayüzünü oluşturma
    QCanBusDevice *device = QCanBus::instance()->createDevice(pluginName, interfaceName);
    if (!device) {
        qDebug() << "Error: Failed to create CAN device";
        return -1;
    }

    // CAN arayüzünü başlatma
    if (!device->connectDevice()) {
        qDebug() << "Error: Failed to connect CAN device";
        return -1;
    }

    // QTimer kullanarak sürekli veri okuma
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&](){
        while (device->framesAvailable()) {
            QCanBusFrame frame = device->readFrame();
            qDebug() << "Received data:" << frame.payload().toHex();
        }
    });
    timer.start(100);

    // QTimer kullanarak sürekli veri yazma
    QTimer writerTimer;
    writerTimer.start(500);
    QObject::connect(&writerTimer, &QTimer::timeout, [&](){
        // örnek veri yazma
        QCanBusFrame frame;
        frame.setPayload(dataToSend);
        frame.setFrameId(0x123);
        frame.setExtendedFrameFormat(false);
        frame.setFlexibleDataRateFormat(false);
        device->writeFrame(frame);
        qDebug() << "Data sent";
    });
}
