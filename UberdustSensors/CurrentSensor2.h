#ifndef CURRENT_SENSOR2
#define CURRENT_SENSOR2

#include <EmonLib.h>                   // Include EmonLib Library
#include <Sensor.h>
class CurrentSensor2:
public Sensor 
{
public:

  unsigned long timestamp;
  EnergyMonitor emon1;
  CurrentSensor2 (char * name,  int pin)
  {    
    this->pin=pin;	
    this->status=0;
    this->set_name(name);
    this->send=0;	
    timestamp = 0;
    emon1.current(this->pin, 30);      // Current: input pin, calibration.	
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
		timestamp = millis();
		double val = emon1.calcIrms(1480);  // Calculate Irms only
		this->status=(int)(val*1000);		
		
  }
};
#endif
