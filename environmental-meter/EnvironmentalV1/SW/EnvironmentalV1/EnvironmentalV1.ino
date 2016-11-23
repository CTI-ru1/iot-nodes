
#define USE_TREE_ROUTING

#define REMOTE_RESET
//Include XBEE Libraries
#include <XBee.h>
#include <XbeeRadio.h>
//#include <BaseRouting.h>
#include <TreeRouting.h>
#include <NonRouting.h>

#include "EEPROM.h"
#include <Arduino.h>
//Software Reset
#include <avr/wdt.h>
//Include Aplication Libraries
#include <App.h>
#include <UberdustSensors.h>

//Create the XbeeRadio object we'll be using
XBeeRadio xbee = XBeeRadio();


//Aplication object
App ap;

//Message Routing
TreeRouting * routing;

void radio_callback(uint16_t sender, byte* payload, unsigned int length) {

}

//Runs only once
void setup() {
  
  wdt_disable();
  
  //start our XbeeRadio object and set our baudrate to 38400.
  xbee.begin(38400);
  //Initialize our XBee module with the correct values (using the default channel, channel 12)h
  xbee.init(16);

//#ifdef USE_TREE_ROUTING
  routing = new TreeRouting(&xbee);
//#else 
  //routing = new NonRouting(&xbee);
//#endif 
  routing->set_sink(false);
 

  uint16_t address = xbee.getMyAddress(); //fix 4hex digit address
  uint8_t * bit = ((uint8_t*) & address);
  uint8_t mbyte = bit[1];
  uint8_t lbyte = bit[0];
  bit[0] = mbyte;
  bit[1] = lbyte;
  routing->set_my_address(address);
  routing->set_message_received_callback(radio_callback);
  
  // init Aplication service 
  ap.init(address, routing);


  add_sensors();

  wdt_disable();
  wdt_enable(WDTO_8S);
}

void loop() {
 
  ap.handler();
  routing->loop();
  wdt_reset();
}


void add_sensors() {

#define TEMP_PIN A3
#define LIGHT_PIN A2
#define METH_PIN A1
#define CARBON_PIN A0

#define PIR_PIN 3
#define MICRO_PIN A5
#define HUM_PIN A4

    MethaneSensor* mh4Sensor = new MethaneSensor("mq2", METH_PIN);
    ap.add_resource(mh4Sensor);
    LM35Sensor* tempSensor = new LM35Sensor("lm35",TEMP_PIN);
    ap.add_resource(tempSensor);
    lightSensor* liSensor = new lightSensor("light", LIGHT_PIN);
    ap.add_resource(liSensor);
    CoSensor* coSen = new CoSensor("mq7v13", CARBON_PIN);
    ap.add_resource(coSen);
    pirSensor* pSensor = new pirSensor("pir", PIR_PIN);
    ap.add_resource(pSensor);
    SoundGrove* sound = new SoundGrove("sound", PIR_PIN);
    ap.add_resource(sound); 
    humiditySensorLM35* humSensor= new humiditySensorLM35("humid", HUM_PIN,tempSensor);
    ap.add_resource(humSensor);

}

