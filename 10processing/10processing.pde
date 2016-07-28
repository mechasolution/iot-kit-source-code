import processing.net.*;
Client myClient;
boolean flag_p = false ;
int resolv = 3 ;
int x_po = resolv + 11 ;
long line = 0 ;
int mou_sta = 0 ;
void setup() {
  myClient = new Client(this, "192.168.120.20", 23);
  size(600, 600) ;
  background(0) ;
  fill(255) ;
  rect(0, 100, width, height) ;
  fill(125) ;
  rect(50, 25, 200, 50) ;
  rect(350, 25, 200, 50) ;
  textAlign(CENTER, CENTER) ;
  textSize(30) ;
  fill(255, 255, 0) ;
  text("LED ON", 150, 50) ;
  text("LED OFF", 450, 50) ;
}
void draw() {
  myClient.write('c') ;
  if (myClient.available() > 1) {
    int val1 = myClient.read() << 8 ;
    int val2 = myClient.read() ;
    int val = val1 | val2 ;
    /*
      Highest analog value is 677 and lowest is 68
      609 = highest value - lowest value
    */
    int bright = (val - 68) * 255 / 609 / 1 ;
    if (bright > 255) bright = 255 ;
    else if (bright < 0) bright = 0 ;
    fill(bright) ;
    rect(0, 100, width, height) ;
  }
  if (flag_p == true ) {
    flag_p = false ;
    int mo_y = mouseY / 1 ;
    if (mo_y > 25 && mo_y < 75) {
      int mo_x = mouseX / 1 ;
      if (mo_x > 50 && mo_x < 250) myClient.write('n') ;
      else if (mo_x > 350 && mo_x < 550) myClient.write('f') ;
    }
  }
}
void mousePressed() {
  flag_p = true ;
}
