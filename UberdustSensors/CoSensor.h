#include <Sensor.h>

class lightSensor : 
public Sensor 
{
public:
  int pin, status;
  lightSensor(char * name, int pin): 
  Sensor(name)
  {
    this->pin = pin;
    this->status = 0;
    this->set_name(name);
    this->send=0;		
  
  }
  void get_value(char* output_data, uint8_t& output_data_len)
  {
	char* sensorname=get_name();
	
    	output_data_len = sprintf( (char*)output_data, "%s,%d",sensorname, this->status); 

  }
  bool periodic_check(){
	send=0;
	return send;
  }		
  void check_and_send(void)
  {
    
	int newStatus =analogRead(this->pin);  
	this->status=newStatus;	
		
  }	
};

