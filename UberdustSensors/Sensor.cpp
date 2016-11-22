
#include "Sensor.h"

char * Sensor::get_name() {
    return name;
}
void Sensor::set_name(char * name) {
    strcpy(this->name, name);
}
bool Sensor::periodic_check(void){
}
void Sensor::check_and_send(void){
}

int Sensor::get_status() {
    return status;
}

void Sensor::get_value( char* output_data, uint8_t& output_data_len)
{
}
