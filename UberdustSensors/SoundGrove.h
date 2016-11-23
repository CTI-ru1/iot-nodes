#include <Sensor.h>
#include <math.h>
#include <Wire.h>
#ifndef SOUNDGROVE
#define SOUNDGROVE 
#define ref_SPL       94 
#define sensitivity    3.16
class SoundGrove: 
public Sensor 
{
 public:
  int pin;
  float status;
  float total;
	
  unsigned long counter;
  SoundGrove(char * name, int pin):
  Sensor(name)
  {
   		
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
	this->total=this->total+db_current;		
        this->counter++;
	return send;
  }
  void check_and_send(void)
  {
	float finalvalue=this->total/this->counter;
        this->status=finalvalue;
	Serial.print("VALue:");
	Serial.println(this->status);

	this->counter=0.0;
	this->total=0.0;
	
			
        delay(10);   	
  }	
};
#endif
