#include <Sensor.h>
#include <math.h>
#include <Wire.h>
#include <TH02_dev.h>
#ifndef HUMDIGITAL
#define HUMDIGITAL 

class HumDigital: 
public Sensor 
{
 public:
  int pin;
	float status;	
  HumDigital(char * name):Sensor(name)
  {
    	
    this->status = 0.0; 
    this->set_name(name);
    this->send=0;
  }
   void get_value(char* output_data, uint8_t& output_data_len)
  {
	char* sensorname=get_name();
	char sensorvalue[6];
	dtostrf(this->status,4,2,sensorvalue);
    	output_data_len = sprintf( (char*)output_data, "%s,%s",sensorname, sensorvalue);
  }
  bool periodic_check(){
	send=0;
	return send;
  }
  void check_and_send(void)
  {
		Serial.print("Checking temperature:");
		TH02.PowerOn();
		delay(150); 
		float hum=TH02.ReadHumidity();
		TH02.PowerOff();
		delay(150);
		Serial.println(this->status);
		this->status=hum;
	    	
  }	
};
#endif
