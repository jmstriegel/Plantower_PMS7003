# Plantower_PMS7003 Arduino Library

An Arduino library for interfacing with the Plantower PMS7003 laser
particle counter. This should also work the the PMS5003 sensor,
as they share the same protocol.

## PMS7003

The PMS7003 is a particle matter counter capable of detecting
particulates in the range of 0.3 to 10 microns.

This device uses a serial connection to send measurements to a
connected device roughly once a second. Concentration measurements
are provided for PM1.0 (0.3-1.0um), PM2.5 (1.0-2.5um), and PM10
(2.5-10.0um).

 - [Manufacturer Site](http://www.plantower.com/en/content/?110.html)
 - [Documentation (Mandarin)](http://aqicn.org/air/view/sensor/spec/pms7003.pdf)
 - [Review / Evaluation](http://aqicn.org/sensor/pms5003-7003/)
 - [English Documentation for the 5003 (same protocol)](http://www.aqmd.gov/docs/default-source/aq-spec/resources-page/plantower-pms5003-manual_v2-3.pdf)
 - [Amazon Search (Roughly $40)](https://www.amazon.com/s/keywords=pms7003)


## Interface

Interfacing with the device is via an atypical 1.27mm pitch 10-pin
(2x5 row) male header. I recommend using an SWD breakout board and
cable for easy prototyping--the pinout is totally different but they
are easy to source. Here's what I used:

 - [Female-to-Female SWD Cable](https://www.adafruit.com/product/1675)
 - [SWD Breakout Board](https://www.adafruit.com/product/2743)

All of the data pins require a 3.3v TTL level, but power must be
supplied to VCC at 5v, which is a requirement for proper operation
of the built-in fan.

Pins are numbered as shown below. Pin 1 is at the top of the keyed
side of the connector.

    +5v VCC  1  2   +5v VCC
        GND  3  4   GND
      Reset  5  6   N/C
         RX  7  8   N/C
         TX  9  10  Set

Connecting the PMS7003 to a compatible 3.3v device requires 4 pins:

 - Connect microcontroller +5v VCC or USB to pin 1 (VCC).
 - Connect microcontroller GND to pin 3  (GND).
 - Connect microcontroller TX to pin 7 (RX).
 - Connect microcontroller RC to pin 9 (TX).

## Usage

    // Constructor
    Plantower_PMS7003 sensor = Plantower_PMS7003();

    void setup()
    {
      // Initialize the sensor with the serial device
      // that it's connected to. Hardware Serial1 is the
      // default, if no parameter is provided to init()

      Serial1.begin(9600);    // Note: 9600 baud
      sensor.init(&Serial1);

    }

    void loop()
    {
      // Use updateFrame() to read in sensor data in your
      // loop until hasNewData() returns true.
      sensor.updateFrame();

      // Note: once updateFrame() is called, all data is
      // invalid until hasNewData() returns true.
      if (sensor.hasNewData())
      {
        // PM1.0: getPM_1_0() 
        Serial.print("PM1.0: ");
        Serial.print(sensor.getPM_1_0());
        
        // PM2.5: getPM_2_5()
        Serial.print(" PM2.5: ");
        Serial.print(sensor.getPM_2_5());
        
        // PM10: getPM_10_0()
        Serial.print(" PM10: ");
        Serial.print(sensor.getPM_10_0());
        Serial.println();
      }

    }

A full example can be found in pms_7003_test.ino.


## License

This library was written by Jason Striegel and provided
under the BSD license. See license.txt for details.

