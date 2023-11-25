#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <string.h> 
#include <Servo.h>
#include <Math.h>
#define ON_Board_LED 2  //--> Defining an On Board LED (GPIO2 = D4), used for indicators when the process of connecting to a wifi router
const int trigPin = 5; // D1
const int echoPin = 4; // D2


//-- Getting information using MM LaptopNetwork 
const char* ssid = "LAPTOP-VFUTQCLK 8600";  
const char* password = "<0909Vg4";  
const char *host = "http://192.168.137.171"; 
//-- Using my own Network
//const char* ssid = "";  
//const char* password = "##";    
//const char *host = "http://192.168.1.128"; 
double duration;
double distance;
double pos=3444.44;
double vel=4.8;
double acel=8.16;
double pre_pos =0.0;
double pre_vel =0.0; 
double t_pre=0;
double t_current=0;
double dts=0;
double dt=0.00;

//String GetAddress, LinkGet,LinkSend, getData, SendAddress;
int id = 1; //--> ID in Database
//const String LinkSend ="http://192.168.1.128/ESP8266_GET_DATABASE/send_sensor_value.php";
//const String LinkGet = "http://192.168.1.128/ESP8266_GET_DATABASE/get_data.php"; 
const String LinkSend ="http://192.168.137.171/ESP8266_GET_DATABASE/send_sensor_value.php";
const String LinkGet = "http://192.168.137.171/ESP8266_GET_DATABASE/get_data.php"; 
//LinkGet = host + GetAddress; //--> Make a Specify request destination
//LinkSend = host + SendAddress;
String getData = "ID=" + String(id); 


  
Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

void setup() {
  Serial.begin(115200);
 Serial.println("Starting....");
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input  
digitalWrite(trigPin,LOW);
  // put your setup code here, to run once:
  ESC1.attach(12,1000,2000); // D6
  ESC2.attach(13,1000,2000); // D7
  ESC3.attach(14,1000,2000); // D5
  ESC4.attach(15,1000,2000); // D8
  
  delay(500); 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  //Serial.println("");
  //Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    //Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
}
 
void loop() {
  //Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);  
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
////  
//  duration = pulseIn(echoPin, HIGH)*0.17; // Distance in mm
//  t_pre = t_current;
//  t_current = micros();
//  dts = t_current-t_pre;
  
 // dt = (dts)/1000000; 
//  pre_pos = pos;
//  pos = distance;
//  pre_vel = vel;
//  vel = (pos-pre_pos);
//  acel = (vel-pre_vel)/dt;
  HTTPClient http; //--> Declare object of class HTTPClient
//  //----------------------------------------Getting Data from MySQL Database
  
  http.begin(LinkGet); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCodeGet = http.POST(getData); //--> Send the request
  String payloadGet = http.getString(); //--> Get the response payload from server
  http.end(); //--> Close connection 
  String v1 = payloadGet.substring(1 , 4);   String v2 = payloadGet.substring(5 , 8);
  String v3 = payloadGet.substring(9 , 12);  String v4 = payloadGet.substring(13, 16);
  int w1 = v1.toInt();  int w2 = v2.toInt();
  int w3 = v3.toInt();  int w4 = v4.toInt(); 
  w1 = map(w1, 0, 1023, 0, 180); ESC1.write(w1);  w2 = map(w2, 0, 1023, 0, 180); ESC2.write(w2); 
  w3 = map(w3, 0, 1023, 0, 180); ESC3.write(w3);  w4 = map(w4, 0, 1023, 0, 180); ESC4.write(w4);    
  http.begin(LinkSend);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
  String httpRequestData = "&pos=" + String(pos) + "&speed=" + String(pos) + "&acel=" + String(dts) + "";
  int httpResponseCode = http.POST(httpRequestData); 
  
  
  http.end();
  
}
