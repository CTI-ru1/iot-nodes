#include <Sensor.h>
#include <math.h>
#ifndef LM35SENSOR
#define LM35SENSOR 

class LM35Sensor : 
public Sensor 
{
 public:
  int pin;
  float status;
  LM35Sensor(char * name, int pin):
  Sensor(name)
  {
    this->pin = pin;
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

	float temperature = analogRead(this->pin)*0.0049;//we found the anexactitud of the 5V
	temperature=temperature*100.0;  
	this->status = temperature;	    	
  }	
};
#endif
