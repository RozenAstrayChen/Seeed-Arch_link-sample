#include "mbed.h"
#include <WIZnetInterface.h>
#include "HTTPClient.h"
#include <MbedJSONValue.h>
#include <DHT.h>

//#define USE_DHCP 0

//#define LOOPBACKPORT 5000

const char * IP_Addr    = "222.98.173.212";
const char * IP_Subnet  = "255.255.255.192";
const char * IP_Gateway = "222.98.173.254";
unsigned char MAC_Addr[6] = {0x00,0x08,0xDC,0x12,0x34,0x55};
Serial pc(USBTX, USBRX);
//#ifdef TARGET_LPC11U35
SPI spi(SPI_PSELMOSI0, SPI_PSELMISO0, SPI_PSELSCK0); // mosi, miso, sclk
WIZnetInterface ethernet(&spi,p24,p17);
//define DHT pin
DHT sensor(D5,DHT11);
//define led
DigitalOut led(D4);
DigitalOut led1(LED1);
//PIR
DigitalIn alarm(p13, PullUp); //internal pull up 
int ret;
//#endif
void status_check(int);
int PIR_sensor();