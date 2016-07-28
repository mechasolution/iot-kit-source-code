#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ; //mac address
IPAddress ip(192, 168, 120, 20) ;
EthernetServer server(90) ;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2) ;
boolean lcd_flag = false ;
String request = "" ;
void setup() {
  // put your setup code here, to run once:
  Ethernet.begin(mac, ip) ;
  server.begin() ;
  lcd.begin(16, 2) ;
  Serial.begin(9600) ;
}
void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client = server.available() ;
  if (client) {
    lcd.begin(16, 2) ;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read() ;
        request += c ;
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE>Arduino LCD</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<form method=\"get\">") ;
          client.println("LCD text up = &nbsp;&nbsp;&nbsp;&nbsp;<input type=\"text\"name=\"val1\"> max 16<br />") ;
          client.println("LCD text down = <input type=\"text\" name=\"val2\"> max 16") ;
          client.print("<br />") ;
          for (int tem = 0; tem < 17; tem++) client.print("&nbsp;") ;
          client.println("&nbsp;") ;
          client.println("<input type=\"submit\" value=\"send\">") ;
          client.println("</form>") ;
          client.println("</BODY>");
          client.println("</HTML>");
          delay(1) ;
          client.stop() ;
          Serial.println(request) ;
          String req_back = request ;
          if (request.indexOf("val1") && request.indexOf("val2")) {
            request.remove(0, 11) ;
            Serial.println(request) ;
            for (int tem = 16; tem >= 0; tem--) {
              request.remove(tem) ;
              if (request.lastIndexOf("&") == -1) break ;
            }
            Serial.println(request) ;
            lcd.setCursor(0, 0) ;
            lcd.print(request) ;
            request = req_back ;
            request.remove(0, 11) ;
            int tem = 0 ;
            int count = 0 ;
            while (1) {
              request.remove(0, tem) ;
              Serial.println(request) ;
              if (request.startsWith("&val2")) {
                Serial.print("start :" ) ;
                Serial.println(request) ;
                req_back = request ;
                Serial.print("req_back :" ) ;
                Serial.println(req_back) ;
                for (int i = 14; i < 30; i++) {
                  request.remove(i) ;
                  Serial.print("req : ") ;
                  Serial.println(request) ;
                  if (request.lastIndexOf("HTTP/1.1") != -1) {
                    request.remove(i - 8) ;
                    break ;
                  }
                  request = req_back ;
                }
                request.remove(0, 6) ;
                Serial.print("except : ") ;
                Serial.println(request) ;
                lcd.setCursor(0, 1) ;
                lcd.print(request) ;
                break ;
              }
              tem = 1 ;
              count++ ;
              if (request.length() == 0) {
                lcd.setCursor(0, 0) ;
                lcd.print(" ") ;
                break ;
              }
            }
          }
          request = "" ;
        }
      }
    }
  }
}
