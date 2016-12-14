#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>
const char *ssid = "controlt";
const char *password = "";
ESP8266WebServer server(80);

char led_status[50];
String webSite;
Servo myservo;
//#define LEDR 5

int potpin = 0;
int val;

/*void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  //digitalWrite(LEDB, LOW);
}*/
void buildWeb(){
  
  webSite += "<!DOCTYPE html>";
  webSite += "<head><meta charset = \"utf-8\">";
  webSite += "<title> Motor Control </title>";
  webSite += "<style>";
  webSite += "body{background-color:#D1BBFF; font-family: Arial, Helvetica, Sans-Serif; Color: #000088;}";
  webSite += "div{width:500px; text-align: center; margin: 50 auto;}";
  webSite += "</style>";
  webSite += "</head>";
  webSite += "<body>";
  webSite += "<div>";
  webSite += "<h1>Motor Control form</h1>";
  //webSite += "<p id=\"ledStatus\">You can select a RGB LED color ...</p>";
  webSite += "<form action=\"form1\">";
  webSite += "<input type=\"radio\" id=\"red\" name=\"led\" value=\"red\"><label for=\"red\">Color Red</label>";
  webSite += "<input type=\"radio\" id=\"green\" name=\"led\" value=\"green\"><label for=\"green\">Color Green</label>";
 // webSite += "<input type=\"radio\" id=\"blue\" name=\"led\" value=\"blue\"><label for=\"blue\">Color blue</label><br><br>";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</div>";
  webSite += "</body></html>";
}
void handleRoot(){
  server.send(200,"text/html",webSite);
}

void handleLEDStatus(){
  if(server.arg("led") == "red"){
     snprintf(led_status,50,"1");
     myservo.write(0);
      delay(15);
   // digitalWrite(LEDR,HIGH);
    //digitalWrite(LEDG,LOW);
    //digitalWrite(LEDB,LOW);
  }
  else if(server.arg("led") == "green"){
     snprintf(led_status,50,"2");
     myservo.write(179);                  // 設定 Servo 旋轉角度
      delay(15);   
    //digitalWrite(LEDR,LOW);
   // digitalWrite(LEDG,HIGH);
    //digitalWrite(LEDB,LOW);
  }
 /* else if(server.arg("led") == "blue"){
     snprintf(led_status,50,"Now, RGB LED color is blue...");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDB,HIGH);
  }*/
server.send (200,"text/html",led_status );
}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  // put your setup code here, to run once:
  myservo.attach(5);
  //pinMode(LEDB, OUTPUT);
  //turnoff();
  buildWeb();
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  server.on("/",handleRoot);
  server.on("/form1",handleLEDStatus);
  server.onNotFound(handleNotFound);
  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

