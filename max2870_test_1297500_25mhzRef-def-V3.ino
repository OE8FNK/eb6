/* This sketch is a test tool to perform the following tests: 
 * 1.) to test the basic connections between Max2870 and ESP32
 * 2.) to generate a test signal on 1297,500 alternating with 
 *    1297,501625 to verify that the MAX2870 Module and the 
 *    ESP32 is working. The deviation from the given frequency
 *    is about 5-10 kHz, based on 2 modules tested. 
 *    
 *    Minimal connections are:
 *    5  - LE  - output, Latch data to MAX2870
 *    13 - CE  - output, Enables MAX2870
 *    18 - CLK - output, SPI Clock to MAX2870
 *    23 - data- output, SPI MOSI to MAX2870
 *    19 - sdi - not used, but is defined in the SPI definitions
 *    and of course, you need to power both modules
 *    the max2870 can be powered from 3.3V or 5V connections
 *    *    
 *    created 2023/03/10  by Fred, OE8FNK 
 *    
*/
#include <SPI.h>

#define VSPI_MISO   MISO
#define VSPI_MOSI   MOSI
#define VSPI_SCLK   SCK
#define VSPI_SS     SS

static const int spiClk = 1000000; // 1 MHz

//alternating 1297,5 MHz and 1297,501625 MHz  

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

r0 = 0x0067cb00;
r1 = 0x20037d01;
r2 = 0x1b004e42;
r3 = 0x01008133;
r4 = 0x61af4224;
r5 = 0x01400005;

  
  pinMode(LED_BUILTIN , OUTPUT);
  pinMode(13 , OUTPUT);  // CE 
  digitalWrite(13, LOW);   // MAX2870 via CE off
  
  //initialise vspi instances of the SPIClass attached to VSPI 

  vspi = new SPIClass(VSPI);
  vspi->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);
  
  //set up slave select pins as outputs as the Arduino API
  //doesn't handle automatically pulling SS low
  pinMode(VSPI_SS, OUTPUT); //VSPI SS

}
// the loop function runs over and over again until power down or reset
void loop() {

r0 = 0x0067cb00;
r1 = 0x20037d01;
r2 = 0x1b004e42;
r3 = 0x01008133;
r4 = 0x61af4224;
r5 = 0x01400005;

  digitalWrite(13, LOW);   // CE  set MAX2870 Off (high)

registerwrite();

  digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(20);  // mindestens 20ms warten 
  // ###################################################################### gnd

registerwrite();
  digitalWrite(25, HIGH);    // turn the LED on 
  delay(150);                       // wait 
  Serial.print("."); 

  digitalWrite(13, LOW);   // CE  set MAX2870 Off 
  
  digitalWrite(25, LOW);   
  
  delay(50);                       // wait for a second

//switch to 1297,501526 
r0 = 0x0067cb08;
r1 = 0x20037d01;
r2 = 0x1b004e42;
r3 = 0x01008133;
r4 = 0x61af4224;
r5 = 0x01400005;

  digitalWrite(13, LOW);   // CE  set MAX2870 Off
  
registerwrite();
delay(20);

registerwrite();

  digitalWrite(25, HIGH);    // turn the LED on
  delay(150);                       // wait 

  digitalWrite(13, LOW);   // CE  set MAX2870 Off 
  digitalWrite(25, LOW);   
  delay(50);                      

  Serial.print("."); 
}

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
  digitalWrite(13, HIGH);   // CE  set MAX2870 ON (high) 
}
