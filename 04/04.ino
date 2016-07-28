#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ; //mac address
IPAddress ip(192, 168, 120, 20) ;
EthernetServer server(90) ;
String test = "" ;
void setup() {
  // put your setup code here, to run once:
  Ethernet.begin(mac, ip) ;
  server.begin() ;
  Serial.begin(9600) ;
}
void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client = server.available() ;
  if (client) {
    boolean currentLineIsBlank = true ;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read() ;
        test += c ;
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK") ;
          client.println("Content-Type: text/html") ;
          client.println("Connection: close") ;
          client.println() ;
          client.println("<!DOCTYPE html>") ;
          client.println("<html>") ;
          client.println("<head>") ;
          client.println("<title>anlaogRead</title>") ;
          client.println("<meta http-equiv='refresh' content='0'/>") ;
          client.println("</head>") ;
          client.println("<body onload=\"call()\">") ;
          String a_val = "<p>" ;
          a_val += String(analogRead(5)) ;
          a_val += "</p>" ;
          client.println(a_val) ;
          client.println("</body>") ;
          client.println("</html>") ;
          Serial.println(test) ;
          test = "" ;
          break ;
        }
        if (c == '\n') {
          currentLineIsBlank = true ;
        }
        else if (c != '\r') {
          currentLineIsBlank = false ;
        }
      }
    }
    delay(1) ;
    client.stop() ;
  }
}
