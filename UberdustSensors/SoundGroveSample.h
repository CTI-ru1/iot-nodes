#include <Sensor.h>
#include <math.h>
#include <Wire.h>
#ifndef SOUNDGROVESAMPLE
#define SOUNDGROVESAMPLE
#define ref_SPL       94 
#define sensitivity    3.16
class SoundGroveSample: 
public Sensor 
{
 public:
  int pin;
	float status;
  float total,maximum,minimum,lastreading;
	
  unsigned long counter;
  SoundGroveSample(char * name, int pin):
  Sensor(name)
  {
    this->lastreading=0.0;			
    this->pin = pin;
    this->status = 0.0; 
    this->set_name(name);
    this->send=0;
    this->counter=0;			
    
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

       float rms=0.0;               
       rms=analogRead(this->pin);     
       rms *= 0.0048; 
    
      	if(rms <= 0)
       	{
        	rms = 0.0048;
        }
        float db_current = (ref_SPL + 20 * log10(rms/ sensitivity)); 
	this->lastreading=db_current;
	return send;
  }
  void check_and_send(void)
  {

	this->status=this->lastreading;
	Serial.print("last reading");
	Serial.println(this->lastreading);
			
        delay(10);   	
  }	
};
#endif
