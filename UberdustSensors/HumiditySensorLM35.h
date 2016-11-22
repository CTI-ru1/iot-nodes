#include <Sensor.h>
#include <LM35Sensor.h>
class humiditySensorLM35: 
public Sensor 
{
public:
  int pin;
  float status;
  LM35Sensor* temp;
  humiditySensorLM35(char * name, int pin, LM35Sensor* temp): 
  Sensor(name)
  {
    this->temp=temp;
    this->pin = pin;
    this->status = 0.0;
    this->set_name(name);
    this->send=0;		
   
  }
  void get_value( char* output_data, uint8_t& output_data_len)
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

	//To properly caculate relative humidity, we need the temperature.
  	float temperature =this->temp->status ; //replace with a thermometer reading if you have it
  	//caculate relative humidity
 	 float supplyVolt = 5.0;

  	// read the value from the sensor:
  	int HIH4030_Value = analogRead(this->pin);
  	float voltage = HIH4030_Value/1023. * supplyVolt; // convert to voltage value

  	// convert the voltage to a relative humidity
  	// - the equation is derived from the HIH-4030/31 datasheet
 	 // - it is not calibrated to your individual sensor
 	 //  Table 2 of the sheet shows the may deviate from this line
 	 float sensorRH = 161.0 * voltage / supplyVolt - 25.8;
 	 float trueRH = sensorRH / (1.0546 - 0.0026 * temperature); //temperature adjustment 

	this->status = trueRH;
       
    	
  }
};

