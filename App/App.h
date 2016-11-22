#ifndef APP_H
#define APP_H

#include <Arduino.h>
#include <TreeRouting.h>
#include "Sensor.h"
#define CONF_MAX_MSG_LEN 40
#include "resource.h"

typedef Resource resource_t;

class App {
	public:
		void init(uint16_t myAddress, TreeRouting * routing);
		void sensor_check(void);
		void sensor_send(void);
		void add_resource(Sensor * sensor);
  	        void handler(void);
		void receiver(byte* payload, uint16_t sender, unsigned int length);
  
	private:
		char buffer [90]; 
		String bufmac; 
       		 uint8_t len;
		resource_t resources_[10];
    		TreeRouting * routing_;
    		char _name[20];
    		uint16_t myAddress;
		uint8_t rcount;

};
#endif
