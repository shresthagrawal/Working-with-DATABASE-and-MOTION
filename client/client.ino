/////////////////////////////////////////////////////////////////////
///          Detect Motion and Store it In Database           //////
///////////////////////////////////////////////////////////////////

/// GOOGLE CODE-IN///////////////////////////////////////////////

/* The best part of the devide is that it doesnt require any configuration
 *  The IP and Pass are gthered the help of an   
 *  an open source project https://github.com/egzola/ESP8266-ScreenSetWifi.git
 *  which tries to transfer wifi credential to iot devices using LIFI technology
 *  and the Ip address and Port is automatically detected using multicast DNS 
*/


#include <ESP8266WiFi.h>
#include "mdns.h"
#include <ESP8266HTTPClient.h>
#include <Ticker.h>
#include <screenSetWifi.h>


// No need to add the SSID or Pass just for debugging process
//const char* ssid = ""; 
//const char* password = "";

char ssid[80];
char password[80];
int delayTime=50000;
int pirSensor = 13; //D7 in nodemcu
int ldrPin = 5; //LDR PIN 
String localPort="5000";// default port for sever
String localIp; // 
String serviceName="motion._service._tcp.local";
int ipFind = 0;


void getIPFromMdns(const mdns::Answer* answer){

    // find the Service Name and check it if it equals the service we need
   if(answer->rrtype == MDNS_TYPE_PTR){   
    Serial.println(answer->rdata_buffer);
   // if its equal next find IP Address  
    if(serviceName.equals(answer->rdata_buffer)){
        ipFind =1; 
      }
    }

    // find the port data
    if (answer->rrtype == MDNS_TYPE_SRV) {
        ipFind++;
        char* port_start = strstr(answer->rdata_buffer, "port=");
        if (port_start) {
          port_start += 5;
          char* port_end = strchr(port_start, ';');
          char port[1 + port_end - port_start];
          strncpy(port, port_start, port_end - port_start);
          port[port_end - port_start] = '\0';
          localPort= port;
          Serial.println("port found:"+localPort);
          }
        }
        
    // get IP Address
     if(answer->rrtype == MDNS_TYPE_A){
        ipFind++;
        // printing the Rawa Data from mDNS packet 
        answer->Display();
        // printing the Ip:
        Serial.println("IP Found:");
        Serial.println(answer->rdata_buffer);
        Serial.println("service Name Verified:"); 
        Serial.println(serviceName); 
        localIp = answer->rdata_buffer; 
      } 
}


// Initialise MDns to get the DNS Packets to querry the IP Address
mdns::MDns myMdns(NULL, NULL, getIPFromMdns);

void getSsidPassword(){
  Serial.println("\n\nReady\n");
  Serial.println("Config: Light Mode\n\n\r");  
  boolean ret = false;
  while(!ret)
  {
    ret = getData(ldrPin,NULL , ssid, password , true);
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
 // find the Ip address with mDns 
 if(ipFind<3) myMdns.loop();
 // once the Ip address is found use it to send request
 else{
   float motionStatus = digitalRead(pirSensor); 
    // if motion is detected print in cosole and make GET request to the server
    if(motionStatus== HIGH){
      Serial.println("Motion Detected");
      if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
      
        HTTPClient http;  //Declare an object of class HTTPClient
        http.begin("http://"+localIp+":"+localPort+"/saveData");  //Connect to Server to save currentTimeStamp
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
    
 delay(1000);//check sensor every
 }
}
