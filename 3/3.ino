#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ; //mac address
IPAddress ip(192, 168, 120, 20); // IP address, may need to change depending on network
EthernetServer server(90); // create a server at port 90
void setup()
{
  Ethernet.begin(mac, ip); // initialize Ethernet device
  server.begin(); // start to listen for clients
}
void loop()
{
  EthernetClient client = server.available(); // try to get client
  if (client) { // got client?
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) { // client data available to read
        char c = client.read(); // read 1 byte (character) from client
        // last line of client request is blank and ends with \n
        // respond to client only after last line received
        if (c == '\n') {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // send web page
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Arduino Web Page</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>Hello Arduino!</h1>");
          client.println("This web page from the Arduino server");
          client.println("</body>");
          client.println("</html>");
          break;
        }
        // every line of text received from the client ends with \r\n
      } // end if (client.available())
    } // end while (client.connected())
    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection
  } // end if (client)
}
