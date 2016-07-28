#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ; //mac address
IPAddress ip(192, 168, 120, 20) ;
EthernetServer server(90) ;
int ena = 2 ;
int in1 = 3 ;
int in2 = 4 ;
int in3 = 5 ;
int in4 = 6 ;
int enb = 7 ;
String request = "" ;
void setup() {
  // put your setup code here, to run once:
  Ethernet.begin(mac, ip) ;
  server.begin() ;
  Serial.begin(9600) ;
  for (int i = 2; i <= 7; i++) pinMode(i, OUTPUT) ;
  digitalWrite(ena, HIGH) ;
  digitalWrite(enb, HIGH) ;
}
void loop()
{
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c; // save the HTTP request 1 char at a time
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          // send web page
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Arduino motor</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>DC MOTOR</h1>");
          client.println("<form method=\"get\">") ;
          client.println("<a href=\"/?1\">L Motor CW</a>&nbsp;&nbsp;&nbsp;") ;
          client.println("<a href=\"/?4\">R Motor CW</a><br />") ;
          client.println("<a href=\"/?2\">L Motor STOP</a>") ;
          client.println("<a href=\"/?5\">R Motor STOP</a><br />") ;
          client.println("<a href=\"/?3\">L Motor CCW</a>&nbsp;") ;
          client.println("<a href=\"/?6\">R Motor CCW</a><br />") ;
          client.println("</form>");
          client.println("</body>");
          client.println("</html>");
          delay(1); // give the web browser time to receive the data
          client.stop(); // close the connection
          Serial.println(request);
          if (request.indexOf('?') > -1) {
            request.remove(0, 6) ;
            request.remove(1) ;
            switch (request.toInt()) {
              case 0 :
                lmotor_stop() ;
                rmotor_stop() ;
                break ;
              case 1 :
                lmotor_front() ;
                break ;
              case 2 :
                lmotor_stop() ;
                break ;
              case 3 :
                lmotor_rear() ;
                break ;
              case 4 :
                rmotor_front() ;
                break ;
              case 5 :
                rmotor_stop() ;
                break ;
              case 6 :
                rmotor_rear() ;
                break ;
            }
            Serial.println(request) ;
          }
          request = ""; // finished with request, empty string
        }
      }
      // every line of text received from the client ends with \r\n
    } // end if (client.available())
  } // end while (client.connected())
} // end if (client)
void lmotor_front()
{
  digitalWrite(in1, HIGH) ;
  digitalWrite(in2, LOW) ;
}
void lmotor_rear()
{
  digitalWrite(in1, LOW) ;
  digitalWrite(in2, HIGH) ;
}
void lmotor_stop()
{
  digitalWrite(in1, LOW) ;
  digitalWrite(in2, LOW) ;
}
void rmotor_front()
{
  digitalWrite(in3, HIGH) ;
  digitalWrite(in4, LOW) ;
}
void rmotor_rear()
{
  digitalWrite(in3, LOW) ;
  digitalWrite(in4, HIGH) ;
}
void rmotor_stop()
{
  digitalWrite(in3, LOW) ;
  digitalWrite(in4, LOW) ;
}
