

#include <SoftwareSerial.h>
#include "Seeed_CO2.h"

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

//Software Reset, Watchdog
#include <avr/wdt.h>
unsigned long resetTime = 0;
#define TIMEOUTPERIOD 30000   
#define doggieTickle() resetTime = millis();  // This macro will reset the timer
void(* resetFunc) (void) = 0; //declare reset function @ address 0

void watchdogReset()
{
  while(1);
}

void watchdogSetup()
{
  cli();  // disable all interrupts
  wdt_reset(); // reset the WDT timer
  MCUSR &= ~(1<<WDRF);  // because the data sheet said to
  // Enter Watchdog Configuration mode:
  WDTCSR = (1<<WDCE) | (1<<WDE);
  // Set Watchdog settings: interrupte enable, 0110 for timer
  WDTCSR = (1<<WDIE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0);
  sei();
  Serial.println("finished watchdog setup");  // just here for testing
}


ISR(WDT_vect) // Watchdog timer interrupt.
{
  if(millis() - resetTime > TIMEOUTPERIOD){
    doggieTickle()                                    
   resetFunc();     // This will call location zero and cause a reboot.
  }
  
}

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
byte server[] = { 150,140,5,20};


void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);


#define GET_TEMP_CMD	0
#define GET_CO2PPM_CMD	1

CO2 co2(5, 6);


char message[30];
char deviceName[20]="flareEA-1";
char sensName[20];
char sensValue[20];

int temperature_value = 0;
int co2ppm_value = 0;

void setup()
{
  watchdogSetup();
  doggieTickle();

  Serial.begin(115200);
  Serial.println("CO2 Sensor Setup");

  co2.Init();

  if (Ethernet.begin(mac)==0)
  {
     watchdogReset();
  }
  
  if (client.connect("arduinoClient")) {
    sprintf(message,"1-%s",deviceName);
    Serial.println(message);
    client.publish("connect",message);
    doggieTickle();
  }
}

void loop()
{

  if (!client.connected()) {
    Serial.println("Client no connected");
    watchdogReset();
   
  }
   if (client.loop())
   {
      doggieTickle();
   }
   else
   {
      Serial.println("Client no loop");
      watchdogReset();
   }
    
    
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 30000) {
    Serial.println("pushing to server...");
    //send connect 0
    sprintf(message,"0-%s",deviceName);
    client.publish("connect",message);


    temperature_value = co2.Read(GET_TEMP_CMD);
    co2ppm_value = co2.Read(GET_CO2PPM_CMD);

    Serial.print("Temperature is ");
    Serial.print(temperature_value);
    Serial.print("\t");
    Serial.print("co2ppm is ");
    Serial.print(co2ppm_value);
    Serial.println(" ");
    sprintf(message,"%s/co2",deviceName);
    Serial.println(message);
    sprintf(sensValue,"%d",co2ppm_value);
    client.publish(message,sensValue);
    
    sprintf(message,"%s/temp",deviceName);
    Serial.println(message);
    //message=deviceName+"/temp";
    sprintf(sensValue,"%d",temperature_value);
    client.publish(message,sensValue);
    
    lastCheck = millis();

  }

  
}
