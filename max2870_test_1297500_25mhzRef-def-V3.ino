/* The ESP32 has four SPi buses, however as of right now only two of
   them are available to use, HSPI and VSPI. Simply using the SPI API
   as illustrated in Arduino examples will use VSPI, leaving HSPI unused.

   However if we simply intialise two instance of the SPI class for both
   of these buses both can be used. However when just using these the Arduino
   way only will actually be outputting at a time.

   Logic analyser capture is in the same folder as this example as
   "multiple_bus_output.png"

   created 30/04/2018 by Alistair Symonds
*/
#include <SPI.h>

// Define ALTERNATE_PINS to use non-standard GPIO pins for SPI bus

#define VSPI_MISO   MISO
#define VSPI_MOSI   MOSI
#define VSPI_SCLK   SCK
#define VSPI_SS     SS

static const int spiClk = 1000000; // 1 MHz

//alternating 1297,5 MHz and 1297,501625 MHz  

unsigned int r0 = 0x00678258;
unsigned int r1 = 0x200303e9;
unsigned int r2 = 0x1b004e42;
unsigned int r3 = 0x01008133;
unsigned int r4 = 0x61af4224;
unsigned int r5 = 0x01400005;

uint8_t i = 0;



SPIClass * vspi = NULL;

void registerwrite(); 

void setup() {
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
  digitalWrite(25, HIGH);    // turn the LED off by making the voltage LOW
  delay(150);                       // wait 
  Serial.print("."); 

  digitalWrite(13, LOW);   // CE  set MAX2870 Off für 1 sek

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
  digitalWrite(13, HIGH);   // CE  set MAX2870 ON (high) 
}
