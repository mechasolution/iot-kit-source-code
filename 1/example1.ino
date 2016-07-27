/*
  DHCP-based IP printer
  This sketch uses the DHCP extensions to the Ethernet library
  페이지 9 / 69
  to get an IP address via DHCP and print the address obtained.
  using an Arduino Wiznet Ethernet shield.
  Circuit:
  Ethernet shield attached to pins 10, 11, 12, 13
  created 12 April 2011
  modified 9 Apr 2012
  by Tom Igoe
*/
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ; //mac address
EthernetClient client;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while (1) ;
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
}
void loop() {
}
