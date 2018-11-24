This project stores timestamps once a motion is detected through a nodeMCU and PIR sensor. Additionally this device requires zero configuration:
	* The ip Address and the port is automatically  acquired using mDNS/DNS-SD 
	https://pypi.org/project/zeroconf/
	 * Automatic configuration of wifi using an open source project https://github.com/egzola/ESP8266-ScreenSetWifi.git which tries to transfer wifi credential to iot devices using LIFI technology 

   

How to start this project



1*  create the circuit 

LDR: pin 1 -> vcc | pin 2 -> GPIO 5 
300K Resistor: pin 1 -> gnd | pin 2 -> GPIO 5
PIR Sensor: gnd pin -> gnd | vcc pin -> vcc | out pin -> GPIO 13

2*  start the server 
change the IP address to your local IP 
sudo python server.py

3* add the Lifi/ESP8266-screenSetWifi-master.zip lib to arduino
and upload the client/client.ino code to the nodeMCU

4* configure wifi credentials 

open /lifi/screenSetWifi.html with chrome, follow the steps.

5* (option step) to view the timeStamps 

open in chrome http://192.168.1.15:5000/printData
