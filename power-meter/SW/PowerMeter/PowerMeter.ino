
#define USE_TREE_ROUTING    
#define REMOTE_RESET
//Include XBEE Libraries
#include <XBee.h>
#include <XbeeRadio.h>
//#include <BaseRouting.h>
#include <TreeRouting.h>
#include "EEPROM.h"
//Software Reset
#include <avr/wdt.h>
//Include CoAP Libraries
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
  Serial.begin(9600);

  wdt_disable();
  
  //Initialize our XBee module with the correct values (using the default channel, channel 12)h
  xbee.init(16,38400);

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
  
 CurrentSensor2 * current = new CurrentSensor2("cur/1",A1);
 ap.add_resource(current);
   
CurrentSensor2 * current2 = new CurrentSensor2("cur/2",A2);
  ap.add_resource(current2);
  
CurrentSensor2 * current3 = new CurrentSensor2("cur/3",A3);
  ap.add_resource(current3);

}



