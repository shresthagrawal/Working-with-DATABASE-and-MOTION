This project stores timestamps once a motion is detected through a nodeMCU and PIR sensor. Additionally to make this device even better an easier to configure I have tried to implement  an open source project https://github.com/egzola/ESP8266-ScreenSetWifi.git which tries to transfer wifi credential to iot devices using LIFI technology 

How to start this project



1*  create the circuit 

LDR: pin 1 -> vcc | pin 2 -> GPIO 5 
300K Resistor: pin 1 -> gnd | pin 2 -> GPIO 5
PIR Sensor: gnd pin -> gnd | vcc pin -> vcc | out pin -> GPIO 13

2*  start the server 

sudo python server.py

4* add the Lifi/ESP8266-screenSetWifi-master.zip lib to arduino
and upload the client/client.ino code to the nodeMCU

3* configure wifi credentials 

open /lifi/screenSetWifi.html with chrome, follow the steps.

4* (option step) to view the timeStamps 

open in chrome http://192.168.1.15:5000/printData