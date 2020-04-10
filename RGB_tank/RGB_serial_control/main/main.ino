// void recvWithEndMarker();
// void showNewData();
// int main();
// void setup();

#include <avr/io.h>
#include <util/delay.h>
#include "WS2811.h"
#define BIT(B)           (0x01 << (uint8_t)(B))
#define SET_BIT_HI(V, B) (V) |= (uint8_t)BIT(B)
#define SET_BIT_LO(V, B) (V) &= (uint8_t)~BIT(B)

#define PAUSE  1000     // msec
#define DELAY    10	// msec

// Define the output function, using pin 0 on port b. -> pin D8 arduino
DEFINE_WS2811_FN(WS2811RGB, PORTB, 0)

// Global Variables
const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
uint8_t pixel_value = 0;
boolean newData = false, setup_flag = false;

// Drive the three pixels in an infinit loop.
void threepixeldemo(uint8_t pixel_v)
{
  // Configure pin for output.
  SET_BIT_HI(DDRB, 0);
  SET_BIT_LO(PORTB, 0);

  // off->red, off->green, off->blue
  // RGB_t rgb[3] = {{0,0,0},{0,0,0},{0,0,0}};
  // initiallise
  RGB_t rgb[1] = {{0,0,0}};
  WS2811RGB(rgb, ARRAYLEN(rgb));
  _delay_ms(PAUSE);
// Red
  rgb[0].r = pixel_v;
  rgb[0].g = 0;
  rgb[0].b = 0;
  WS2811RGB(rgb, ARRAYLEN(rgb));
  _delay_ms(PAUSE);
// Green
  rgb[0].r = 0;
  rgb[0].g = pixel_v;
  rgb[0].b = 0;
  WS2811RGB(rgb, ARRAYLEN(rgb));
  _delay_ms(PAUSE);
// Blue
  rgb[0].r = 0;
  rgb[0].g = 0;
  rgb[0].b = pixel_v;
  WS2811RGB(rgb, ARRAYLEN(rgb));
  _delay_ms(PAUSE);
}


void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;

 while (Serial.available() > 0 && newData == false) {

   rc = Serial.read();

   if (rc != endMarker) {
       receivedChars[ndx] = rc;
       ndx++;
     if (ndx >= numChars) {
       ndx = numChars - 1;
     }
   }
   else {
     receivedChars[ndx] = '\0'; // terminate the string
     ndx = 0;
     newData = true;
   }
 }
}

void showNewData() {
 if (newData == true) {
 Serial.print("This just in ... ");
 Serial.println(receivedChars);
 // pixel_value = (uint8_t)receivedChars;
 pixel_value = atoi(receivedChars);
 Serial.println(pixel_value);
 newData = false;
 threepixeldemo(pixel_value);
 }
}

// void setup() {
//   if(!setup_flag){
//     Serial.begin(9600);
//     Serial.println("<Arduino is ready>");
//     setup_flag = true;
//   }
// }

// int main(void) {
//   setup();
//   for(;;){
//     // while(Serial.available()>0){
//     // Serial.println("Serial available");
//     // }
//     recvWithEndMarker();
//     showNewData();
//   }
// }

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  // put your setup code here, to run once:
}

void loop() {
  recvWithEndMarker();
  showNewData();
}
