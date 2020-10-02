#include <WiFi.h>
#include <EspMQTTClient.h>
#include <PubSubClient.h>
#include "RTClib.h"
#include <TimeLib.h>
#include <Wire.h>
#include<EEPROM.h>

RTC_DS1307 rtc;

#define buzzer 26
#define LED_A 19  
#define LED_B 18
#define LED_C 5 
#define LED_D 17
#define button_a 34
#define button_b 32
#define button_c 33
#define button_d 25

const char* ssid = "free h";
const char* password = "123456789";
const char* mqttServer = "tailor.cloudmqtt.com";
const int mqttPort = 14506;
const char* mqttUser = "asoknfqj";
const char* mqttPassword = "Qlo-csz2FTB1";

WiFiClient espClient;
PubSubClient client(espClient);

//--------------------------------------------------------------------------------------
//Motor A
const int inputPin1  = 16;    
const int inputPin2  = 4;   
//Motor B
const int inputPin3  = 0;   
const int inputPin4  = 2;   
//Motor C
const int inputPin5  = 27;   
const int inputPin6  = 14;   
//Motor D
const int inputPin7  = 12;  
const int inputPin8  = 13;

int addr=0;
char k[50],ab,bc,cd,de;
int h[50];


//--------------------------------------------------------------------------------------
void setup_wifi()
{ 
  delay(10);
  //  We start by connecting to a wifi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
  }
   
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.SSID());
  }
/*void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),"zvedndkc","0U5tQ4X0C90w")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("DIST", "0");
     
      client.subscribe("#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} */ 
  
void reconnect(){
    //loop until we are reconnected
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      delay(2000);
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test1");
 client.subscribe("esp/test2");
 }

//Code for storing medicine time in EEPROM of the microcontroller
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
 
  Serial.println(topic);
  String tp = topic;
  String message;
  for (int i = 0; i < length; i++) 
  {
   message = message + (char)payload[i];  //Conver *byte to String
   Serial.print(message);
   EEPROM.put(addr,message);
   EEPROM.commit();
   addr=addr+1;
   }
}
//Code for storing RTC time in an array
void RTC_TIME_TO_ARRAY(){
  DateTime now= rtc.now();
  h[0]=(((now.unixtime() %86400L)/3600)/10);
  h[1]=(((now.unixtime() %86400L)/3600)-h[0]*10);
  h[2]=((now.unixtime() %3600)/60/10);
  h[3]=(((now.unixtime() %3600)/60)-h[2]*10);
  for(int i=0;i<4;i++){
    Serial.print(h[i]);
    }  
}

//Code for retriving data
void Retrive_data(){
  
  k[0]=char(EEPROM.read(addr));
  ab=k[0];
  Serial.print(ab);
  addr=addr+1;
  Serial.println(addr);
  Serial.println("Heena");
  
  k[1]=char(EEPROM.read(addr));
  bc=k[1];
  Serial.print(bc);
  addr=addr+1;
  Serial.println(addr);
  Serial.println("Heena");
  
  
  k[2]=char(EEPROM.read(addr));
  cd=k[2];
  Serial.print(cd);
  addr=addr+1;
  Serial.println(addr);
  Serial.println("Heena");

  k[3]=char(EEPROM.read(addr));
  de=k[3];
  Serial.print(de);
}
  

void motor_driver(){
  
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, HIGH);
     digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, HIGH);
     digitalWrite(inputPin5, LOW);
    digitalWrite(inputPin6, HIGH);
     digitalWrite(inputPin7, LOW);
    digitalWrite(inputPin8, HIGH);
  
  
  }
void setup() {
  Serial.begin(115200);
  //----------------------------------------------------------------
  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(MQTTcallback);
  //---------------------------------------------------------------
 Wire.begin();
 rtc.begin();
 if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     //rtc.adjust(DateTime(2019, 3, 3, 20, 0, 0));
  }
  rtc.adjust(DateTime(2019, 3, 3, 20, 0, 0));
   //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   //-------------------------------------------------------------------------------------------
//buttons
    pinMode(button_a, INPUT);
    pinMode(button_b, INPUT);
    pinMode(button_c, INPUT);
    pinMode(button_d, INPUT);
//motor a
    pinMode(inputPin1, OUTPUT);
    pinMode(inputPin2, OUTPUT);
 //motor b   
    pinMode(inputPin3, OUTPUT);
    pinMode(inputPin4, OUTPUT);  
//motor c    
    pinMode(inputPin5, OUTPUT);
    pinMode(inputPin6, OUTPUT);
//motor d    
    pinMode(inputPin7, OUTPUT);
    pinMode(inputPin8, OUTPUT);
//led & buzzer
   pinMode(LED_A, OUTPUT);
   pinMode(LED_B, OUTPUT);
   pinMode(LED_C, OUTPUT);
   pinMode(LED_D, OUTPUT);
   pinMode(buzzer, OUTPUT);
}



void loop() {
//-----------------------------------------------------------  
 if (!client.connected()) {
    reconnect();
  }
 client.loop(); 
//----------------------------------------------------------




}
