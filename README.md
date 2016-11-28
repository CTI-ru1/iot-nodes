# iot-nodes

<<<<<<< HEAD
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
=======
The overall architecture of our platform is built upon multiple heteroge-
neous installations in school buildings. Each one of these installations con-
sists of a multitude of IoT nodes.
The overall design for the installation of IoT infrastructure consist of:
1. IoT Environmental Devices (On whataver of the 2 versions)
2. IoT Power Meter Devices
3. IoT Gateway
The eagles files and BOM of materials for the first 2 devices can be foound it on the respective folders and the Arduino program too. 
The Gateway program can be found it on: 
The necessary library for include the aplication on the Arduino program are on the folders App aand the different sensors processing are include as objects and the correespondig code can be found it
>>>>>>> a0d38ca0e84018b3dfbb061d33a9bb408c8fc246
on the folder UberdaustSensor.
	-	check_and_send(void): will be called once each 20 seconds. Then all the collected values will be updated in the cloud. Here you must give to the status parameter the final value to be update on.
			
- At the network level: Treerouting.h library is using on the creation of a tree network between all the IoT nodes, with the Gateway as root. Can be downloaded from (link)
- At physical and data link later we use IEEE802.15.4 communication with XBee devices connected to each IoT node using the Arduino XBee(Link) library and XBeeRadio library(link). We must notice here that on both libraries need to be modified the serial port for using with the Arduino Por Micro.On this case you just need to change the code in order to read from Serial1. 





