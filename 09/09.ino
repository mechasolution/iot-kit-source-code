#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ; //mac address
IPAddress ip(192, 168, 120, 20) ;
EthernetServer server(23) ;
void setup() {
  // initialize the ethernet device
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());
}
void loop() {
  // wait for a new client:
  EthernetClient client = server.available();
  if (client) {
    if (client.available() > 0) {
      char c = client.read() ;
      if (c == 'c') {
        int value = analogRead(5) ;
        client.write((value >> 8) & 0xFF) ;
        client.write(value & 0xFF) ;
      }
    }
  }
}
