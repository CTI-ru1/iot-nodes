
#define CONF_RESOURCE_NAME_SIZE 8
#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>
class Sensor {
public:

    Sensor() {
        this->changed = false;
    }

    Sensor(char * name) {
       this->changed = false;
    }
    
    
    char* get_name();
    void set_name(char * name);
    virtual void get_value( char* output_data, uint8_t& output_data_len);	
    virtual bool periodic_check(void);
    virtual void check_and_send(void);		
    int get_status();
    

private:
    char name[CONF_RESOURCE_NAME_SIZE];

protected:
    int status;
    int pin;
    bool changed;
    bool send;
			
};

#endif
