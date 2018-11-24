/////////////////////////////////////////////////////////////////////
///          Detect Motion and Store it In Database           //////
///////////////////////////////////////////////////////////////////

/// GOOGLE CODE-IN///////////////////////////////////////////////

/* To make this device even better an easier to configure I have tried to implement  
 *  an open source project https://github.com/egzola/ESP8266-ScreenSetWifi.git
 *  which tries to transfer wifi credential to iot devices using LIFI technology
*/


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Ticker.h>
#include <screenSetWifi.h>

/* please add ssid and password to run this code */
//const char* ssid = "MANISHA AGRAWAL"; 
//const char* password = "Arashrobo123!";
char ssid[80];
char password[80];
int delayTime=50000;
int pirSensor = 13; //D7 in nodemcu
int ldrPin = 5; //LDR PIN 
String localIp= "192.168.1.15:5000"; // please change this to the Server Node Ip


void onTransmissionBegin()
{
}

void getSsidPassword(){
  Serial.println("\n\nReady\n");
  Serial.println("Config: Light Mode\n\n\r");  
  boolean ret = false;
  while(!ret)
  {
    ret = getData(ldrPin, onTransmissionBegin, ssid, password , true);
  }
  Serial.println(ssid);
  Serial.println(password);

 }

void setup () {
  Serial.begin(115200);
  pinMode(pirSensor, INPUT);
  // get SSID WITH LIFI 
  getSsidPassword();
  // connect to the network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
}
void loop() {
  float motionStatus = digitalRead(pirSensor); 
  // if motion is detected print in cosole and make GET request to the server
  if(motionStatus== HIGH){
    Serial.println("Motion Detected");
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
      HTTPClient http;  //Declare an object of class HTTPClient
      http.begin("http://"+localIp+"/saveData");  //Connect to Server to save currentTimeStamp
      int httpCode = http.GET();//Send the getRequest
      if (httpCode > 0) { //Check the returning code 
        String payload = http.getString();   //Get the request response payload
        Serial.println("currentTimeStamp:"+payload+"%");
        delay(delayTime);
      }
      else{
        Serial.println("Error Saving the timeStamp Value. \n Please check if the sever is switched onn.");
      }

      http.end();   //Close connection
    }  
  } 
  
      delay(100);//check sensor every
}
