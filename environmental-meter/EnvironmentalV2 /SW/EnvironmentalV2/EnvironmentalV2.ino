

#define USE_TREE_ROUTING
#define REMOTE_RESET
//Include XBEE Libraries
#include <XBee.h>
#include <XbeeRadio.h>
#include <TreeRouting.h>
#include <NonRouting.h>
#include "EEPROM.h"
#include <Arduino.h>
//Software Reset
#include <avr/wdt.h>
//Include Aplication Libraries
#include <App.h>
#include <UberdustSensors.h>
#include <Wire.h>
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
    // init aplication service
    ap.init(address, routing);
    Wire.begin();
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
  //The TH02 temperature&humidity digital sensor must be the first on be added:
  //Because the sensor must be power off befor the other digital sensors can be adde it and by defeault is on.
  TemDigital* tem = new TemDigital("lm35", 5);
  ap.add_resource(tem);
  HumDigital* hum = new HumDigital("humid");
  ap.add_resource(hum);
  //LightDigital* light = new LightDigital("light");
  //ncoap.add_resource(light);
  SoundGroveTest* sound = new SoundGroveTest("sound", A3);
  ap.add_resource(sound);  
  SoundGroveSample* sound2 = new SoundGroveSample("light", A3);
  ap.add_resource(sound2);

}

