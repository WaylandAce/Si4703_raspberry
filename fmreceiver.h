#ifndef FMRECEIVER_H
#define FMRECEIVER_H

#include <stdint.h>
#include <I2Cdev.h>
#include <QObject>

class FMReceiver: public QObject
{
    Q_OBJECT

public:
    FMReceiver(QObject* parent = 0, uint8_t addr = 0x10);
    ~FMReceiver();

    void checkRDS();
    int readChannel();

public slots:
    void goToChannel(const unsigned int value = 999);
    void setVolume(const quint8 value = 10);
    void stop();
    void start();
    bool seek(quint8 seekDirection);
    void startAlarm();

signals:
    void frequencyChanged(int freq);

private:
    // put SI4703 into 2 wire mode (I2C)
    void set2WireMode();
    void initSI4703();
    //Read the entire register control set from 0x00 to 0x0F
    void readRegisters();
    void updateRegisters();

private:
    int m_frequency;
    quint8 m_volume;
    bool m_started;
    uint8_t m_devAddr;
    uint16_t si4703_registers[16]; //There are 16 registers, each 16 bits large
    char m_decodedRadioStation[16];
    char m_decodedSong[16];
};

#endif // FMRECEIVER_H
