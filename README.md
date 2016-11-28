# iot-nodes

The overall design for the installation of IoT infrastructure has been built upon the open-source (hardware and software) Arduino
platform and consist of:
-  Environmental Devices (Digital and Analog versions)
-  Power Meter Devices
-  Gateway

The Eagles files and BOM of materials for the first for all the IoT nodes can be found it in the respective folders and the Arduino programs too. 
The Gateway program can be found it on (link)

Libraries
--
- App.h Has been designed to include the overall application on your Arduino IoT node program. Manage the add of the different sensor connected to the node, collect the data from each one and the update cloud values through the under tree network. You can find the code on this repository. 
- For each each sensor include it on the IoT node a specific class is include it. The specific classes using on this platform can be found on UberdustSensor folder. If you want to include new ones just create a new sensor class, include it in the UbersdustSensor.h file and programming the follow methods as you need. 
	-	periodic_check(): will be called on each Arduino loop. Include here, for example a code if you want to read a sensor value faster that each 20 sec and calculated the averaage value.	 
on the folder UberdaustSensor.
	-	check_and_send(void): will be called once each 20 seconds. Then all the collected values will be updated in the cloud. Here you must give to the status parameter the final value to be update on.
			
- At the network level: Treerouting.h library is using on the creation of a tree network between all the IoT nodes, with the Gateway as root. Can be downloaded from (link)
- At physical and data link later we use IEEE802.15.4 communication with XBee devices connected to each IoT node using the Arduino XBee(Link) library and XBeeRadio library(link). We must notice here that on both libraries need to be modified the serial port for using with the Arduino Por Micro.On this case you just need to change the code in order to read from Serial1. 





