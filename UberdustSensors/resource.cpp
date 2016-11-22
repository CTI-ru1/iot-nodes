
#include "resource.h"

Resource::Resource() {
}

Resource::Resource(Sensor * sensor) {
    _sensor = sensor;
  
}

bool Resource::periodic_check(){
	_sensor->periodic_check();
}
void Resource::check_and_send(){
	_sensor->check_and_send();
}
void Resource::get_value( char* output_data, uint8_t& output_data_len) {
    _sensor->get_value( output_data, output_data_len);
}

char * Resource::name() {
    return _sensor->get_name();
}

uint8_t Resource::name_length() {
    return strlen(_sensor->get_name());
}


