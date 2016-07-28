import processing.net.*;
Client myClient;
int resolv = 3 ;
int x_po = resolv + 11 ;
long line = 0 ;
void setup() {
  // This example will not run if you haven't
  // previously started a server on this port.
  myClient = new Client(this, "192.168.120.20", 23);
  size(1600, 600) ;
  background(0) ;
}
void draw() {
  // Change the background if the mouse is pressed
  myClient.write('c') ;
  if (myClient.available() > 1) {
    int val1 = myClient.read() << 8 ;
    int val2 = myClient.read() ;
    int val = val1 | val2 ;
    stroke(255, 255, 255) ;
    val = val * 512 / 1023 / 1 ;
    line(x_po - resolv, line, x_po, (height - val - 44)) ;
    line = (height - val - 44) ;
    x_po += resolv ;
    if (x_po > width) {
      background(0) ;
      x_po = resolv + 11 ;
    }
  }
}
