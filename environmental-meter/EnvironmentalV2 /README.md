# environmental-meter V1
IoT Environmental V2 include: 
- Grove-module with THO2 digital temperature and humidity sensor
- Grove-module with TSL2560 digital light sensor
- Grove-Sound sensor 
- PIR motion sensor.
Find the eagle files and BOM of materials necessary for reproducing the device on the HW folder and the specific Arduino program on SW folder. 
Is also necessary download the specific library for each digital module:
- Light module library: https://github.com/Seeed-Studio/Grove_Digital_Light_Sensor. 
- TH02 sensor has been modified and can be found it at https://github.com/CTI-ru1/Grove_Temper_Humidity_TH02. Here we have modified the original Seed-Studio library in order to 
can connect to the same I2C bus many digital sensors. We include methods to power on/off the module for guarantee just one module power each time on the I2C bus.

