//zoomkat 4-1-12
//open serial monitor to see what the arduino receives
//use the \ slash to escape the " in the html, or use ' instead of
//for use with W5100 based ethernet shields
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
Servo sg90 ; // create servo object to control a servo
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ; //mac address
IPAddress ip(192, 168, 120, 20) ;
EthernetServer server(90) ;
String request = "" ;
//////////////////////
void setup() {
  //start Ethernet
  Ethernet.begin(mac, ip);
  server.begin();
  sg90.attach(7); //the pin for the servo control
  Serial.begin(9600);
}
void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE>Arduino Servo</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<form method=\"get\">") ;
          client.println("Servo value = <input type=\"text\" name=\"val\">") ;
          client.println("<input type=\"submit\" value=\"send\">") ;
          client.println("</form>") ;
          client.println("</BODY>");
          client.println("</HTML>");
          delay(1);
          //stopping client
          client.stop();
          //clearing string for next read
          Serial.println(request) ;
          if (request.indexOf("val=") > -1) {
            request.remove(0, 10) ;
            request.remove(3) ;
            Serial.println(request) ;
            long servo_val = request.toInt() ;
            Serial.println(servo_val, DEC) ;
            sg90.write(servo_val) ;
          }
          request = "";
        }
      }
    }
  }
}
