/* This sketch is a test tool to perform the following tests: 
 * 1.) to test the basic connections between Max2870 and ESP32
 * 2.) to generate a test signal on 5328MHz to verify that the 
 * MAX2870 Module, the ESP32 and the ESP32 is working as
 * Receiver
 * In order to hardwire the EB6 as receiver, connect TX to GND
 *  and RX to +3.3V directly on the board. 
 * 
 * 
 *    Minimal connections are:
 *    27 - LE  - output, Latch data to MAX2870
 *    26 - CE  - output, Enables MAX2870
 *    14 - CLK - output, SPI Clock to MAX2870
 *    12 - data- output, SPI MOSI to MAX2870
 *    18 - sdi - not used, but is defined in the SPI definitions
 *    and of course, you need to power both modules
 *    the max2870 can be powered from 3.3V or 5V connections
 *    *    
 *    created 2023/03/10  by Fred, OE8FNK 
 *    
*/
#include <SPI.h>
#include "heltec.h"
#include "Arduino.h"

#define VSPI_MISO   18   //only defined here in software, not connected
#define VSPI_MOSI   12   //DATA
#define VSPI_SCLK   14   //CLK
#define VSPI_SS     27   //LE

static const int spiClk = 1000000; // 1 MHz

//5328 Mhz
unsigned int r0 = 0;
unsigned int r1 = 0;
unsigned int r2 = 0;
unsigned int r3 = 0;
unsigned int r4 = 0;
unsigned int r5 = 0;

uint8_t i = 0;




SPIClass * vspi = NULL;

void registerwrite(); 

void setup() {

r0 = 0x006a8f00;  // for 25mhz fref, 5328mhz
//r0 = 0x00733200;  // for 25mhz fref, 5760mhz
r1 = 0x20037d01;
r2 = 0x1b004e42;
r3 = 0x01008133;
r4 = 0x618f4224;
r5 = 0x01400005;

  
  pinMode(LED_BUILTIN , OUTPUT);
  pinMode(26 , OUTPUT);  // CE 
  digitalWrite(26, LOW);   // MAX2870 via CE off
  
  //initialise vspi instances of the SPIClass attached to VSPI 

  vspi = new SPIClass(VSPI);
  vspi->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);
  
  //set up slave select pins as outputs as the Arduino API
  //doesn't handle automatically pulling SS low
  pinMode(VSPI_SS, OUTPUT); //VSPI SS
  digitalWrite(26, LOW);   // CE  set MAX2870 Off (high)
  registerwrite();
  digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(20);  // mindestens 20ms warten 
  // ###################################################################### gnd
  registerwrite();
  delay(1);

}  // end of void(setup)...

// the loop function runs over and over again until power down or reset
void loop() {
  
  digitalWrite(25, HIGH);    // turn the LED on 
  delay(150);                       // wait 
  Serial.print("."); 

  digitalWrite(25, HIGH);    // turn the LED on
  delay(150);                       // wait 
  Serial.print("."); 
} // end of while loop 

void registerwrite() {
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(VSPI_SS, LOW);   // LE MAX2870 low
  vspi->transfer32(r5); delay(1); 
  digitalWrite(VSPI_SS, HIGH);   // LE MAX2870 high
  digitalWrite(VSPI_SS, LOW);   // LE MAX2870 low
  vspi->transfer32(r4); delay(1); 
  digitalWrite(VSPI_SS, HIGH);   // LE MAX2870 high
  digitalWrite(VSPI_SS, LOW);   // LE MAX2870 low
  vspi->transfer32(r3); delay(1);
  digitalWrite(VSPI_SS, HIGH);   // LE MAX2870 high
  digitalWrite(VSPI_SS, LOW);   // LE MAX2870 low
  vspi->transfer32(r2); delay(1);
  digitalWrite(VSPI_SS, HIGH);   // LE MAX2870 high
  digitalWrite(VSPI_SS, LOW);   // LE MAX2870 low
  vspi->transfer32(r1); delay(1);
  digitalWrite(VSPI_SS, HIGH);   // LE MAX2870 high
  digitalWrite(VSPI_SS, LOW);   // LE MAX2870 low
  vspi->transfer32(r0); delay(1);
  digitalWrite(VSPI_SS, HIGH);   // LE MAX2870 high
  vspi->endTransaction();
  delay(1);
  digitalWrite(26, HIGH);   // CE  set MAX2870 ON (high) 
}
