#ifndef FMRECEIVER_H
#define FMRECEIVER_H

#include <stdint.h>
#include <I2Cdev.h>
#include <QTime>

class FMReceiver
{
public:
    FMReceiver(uint8_t addr);
    ~FMReceiver();

    void stop();
    void start();
    void setVolume(const uint8_t value = 10);
    void goToChannel(const unsigned int value = 892);
    void readRds(int timeout);
    bool seek(int seekDirection);
    int readChannel();

private:
    // put SI4703 into 2 wire mode (I2C)
    void set2WireMode();
    void initSI4703();
    //Read the entire register control set from 0x00 to 0x0F
    void readRegisters();
    void updateRegisters();

private:
    uint8_t m_devAddr;
    uint16_t si4703_registers[16]; //There are 16 registers, each 16 bits large

    struct {
	uint16_t pi;
	uint16_t programType;
	char psName[9];
        char radioText[64];
	bool trafficProgram;
	bool trafficAnnouncement;
	bool isMusic;
	bool isStereo;
	bool isArtificialHead;
	bool isCompressed;
	bool isDynamicProgramType;
    } rdsInfo;
};

#endif // FMRECEIVER_H
