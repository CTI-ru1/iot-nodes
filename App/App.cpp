#include <App.h>
#include <inttypes.h>
void App::init(uint16_t myAddress, TreeRouting * routing) {
    this->myAddress = myAddress;
    this->rcount = 0;
    routing_ = routing;
    
    char buffer2[50];
    sprintf( (char*)buffer2, "0x%.3x/", this->myAddress); 
    this->bufmac=String(buffer2);	

}

void App::handler() {
	
	sensor_check();

	sensor_send();
}

void App::receiver(byte* payload, uint16_t sender, unsigned int length){
	routing_->send(0xfff,payload,length);
}
void App::sensor_check(void) {
	        
 	uint8_t i;
        for (i = 0; i < rcount; i++) {
        	if(resources_[i].periodic_check())
		{
			char buffer2[50];
			sprintf( (char*)buffer2, "0x%.3x/", this->myAddress); 
			resources_[i].get_value(buffer,len);
			String buf=String(buffer2)+String(buffer);
			buf.toCharArray(buffer, buf.length()+1); 
	
			len=sizeof(buffer);

		   	routing_->send(0xfff,(byte *)buffer,len);
		    	memset(buffer, 0, sizeof(buffer));
		}
			
    	}		
}
void App::sensor_send(void) {
	       
	uint8_t i; 
	String buf;
	static unsigned long timestamp = 0;
	if(millis() - timestamp > 10000)
	{	
			
		buf=bufmac;	
		for (i = 0; i < this->rcount; i++) {
 
			resources_[i].check_and_send();
			resources_[i].get_value(buffer,len);	
			buf=buf+String(buffer)+"+";	
		
   		 }
		buf.toCharArray(buffer, buf.length()+1); 
	
		len=sizeof(buffer);

	   	routing_->send(0xfff,(byte *)buffer,len);
		timestamp = millis();
		memset(buffer, 0, sizeof(buffer));
	 }		
}

void App::add_resource(Sensor * sensor) {
    resources_[this->rcount++] = resource_t(sensor);
}

