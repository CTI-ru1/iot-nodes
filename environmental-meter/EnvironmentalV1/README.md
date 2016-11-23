# environmental-meter V1
IoT Environmental V1 include: Grove-THO2 sensor for temperature and humidity readings, Grove- TSL2560 light sensor, Grove-Sound sensor and Grove-PIR motion sensor.
Find the eagle files and BOM of materials necessary for reproducing the device on the HW folder and the specific Arduino program on SW folder. 
Is also necessary download the specific library for each sensor. The library for the light sensor can be found it at https://github.com/Seeed-Studio/Grove_Digital_Light_Sensor. 
The library for the TH02 sensor has beem modify and can be found it at https://github.com/CTI-ru1/Grove_Temper_Humidity_TH02. Here we have the Seed-Studio original library modify in order to can 
can connect to the same I2C bus many digital sensor. We includ methods to power on/off the module for garantee just one module power on each time at the I2C bus.

