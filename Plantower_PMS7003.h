/*********************************************************************
An Arduino library for interfacing with the Plantower PMS7003 laser
particle counter. This should also work the the PMS5003 sensor,
as they share the same protocol.

For more information about the PMS7003, see README.md.

Written by Jason Striegel.
BSD license. See license.txt for details.
**********************************************************************/

#ifndef _Plantower_PMS7003_H_
#define _Plantower_PMS7003_H_

#include <Arduino.h>

#define PMS7003_DATA_SIZE 32   // 0x42 + 0x4d  + 28 bytes data + 2 bytes checksum = 32 bytes

typedef struct pms7003_struct {
  uint8_t start_1;          // Start char 1 0x42 (fixed)
  uint8_t start_2;          // Start char 2 0x4d (fixed)
  uint16_t frame_length;    // Frame length = 2x13 + 2 (data + parity)

  uint16_t pm_1_0;          // PM1.0 concentration (CF = 1, standard particles) Unit ug/m^3
  uint16_t pm_2_5;          // PM2.5 concentration (CF = 1, standard particulates) Unit ug/m^3
  uint16_t pm_10_0;         // PM10 concentration (CF = 1, standard particulate matter) Unit ug/m^3
  
  uint16_t pm_1_0_atmos;    // PM1.0 concentration (in the atmosphere) Unit ug/m^3
  uint16_t pm_2_5_atmos;    // PM2.5 concentration (in the atmosphere) Unit ug/m^3
  uint16_t pm_10_0_atmos;   // PM10 concentration (in the atmosphere) Unit ug/m^3

  uint16_t raw_gt_0_3;      // Particles in 0.1 liter of air > 0.3um 
  uint16_t raw_gt_0_5;      // Particles in 0.1 liter of air > 0.5um 
  uint16_t raw_gt_1_0;      // Particles in 0.1 liter of air > 1.0um 
  uint16_t raw_gt_2_5;      // Particles in 0.1 liter of air > 2.5um 
  uint16_t raw_gt_5_0;      // Particles in 0.1 liter of air > 5.0um 
  uint16_t raw_gt_10_0;     // Particles in 0.1 liter of air > 10um 
  
  uint8_t version_number;   // Version number
  uint8_t error_code;       // Error code

  uint16_t checksum;        // Sum of each byte from start_1 ... error_code 
} PMS7003_STRUCT;

typedef union pms7003_data {
  unsigned char bytes[PMS7003_DATA_SIZE];
  uint16_t words[PMS7003_DATA_SIZE/2];
  PMS7003_STRUCT values;
} PMS7003_DATABUF;


class Plantower_PMS7003 {
  public:
    bool debug;
    Plantower_PMS7003();
    void init();
    void init(Stream *serial);
    void updateFrame();
    bool hasNewData();

    uint16_t getPM_1_0();
    uint16_t getPM_2_5();
    uint16_t getPM_10_0();
    uint16_t getPM_1_0_atmos();
    uint16_t getPM_2_5_atmos();
    uint16_t getPM_10_0_atmos();

    uint16_t getRawGreaterThan_0_3();
    uint16_t getRawGreaterThan_0_5();
    uint16_t getRawGreaterThan_1_0();
    uint16_t getRawGreaterThan_2_5();
    uint16_t getRawGreaterThan_5_0();
    uint16_t getRawGreaterThan_10_0();
    
    uint8_t getHWVersion();
    uint8_t getErrorCode();

  private:
    PMS7003_DATABUF sensorData;
    bool dataReady;
    bool initialized;
    Stream *serial;
    unsigned char lastByte,
                  nextByte;
    int bufferIndex;

    void dumpBytes();
    void convertSensorData();
    bool isValidChecksum();
    uint16_t uint16FromBufferData(unsigned char *buff, int loc);
};

#endif /*_Plantower_PMS7003_H_*/
