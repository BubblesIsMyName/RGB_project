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
#define LONGPAUSE  3000     // msec
#define DELAY    10	// msec

// Define the output function, using pin 0 on port b. -> pin D8 arduino
DEFINE_WS2811_FN(WS2811RGB, PORTB, 0)

// Global Variables
const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
uint8_t pixel_value = 0;
boolean newData = false, setup_flag = false;
int string_lenth = 0;

// Drive the three pixels in an infinit loop.
void threepixeldemo(uint8_t pixel_r,uint8_t pixel_g,uint8_t pixel_b)
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
    rgb[0].r = pixel_r;
    rgb[0].g = pixel_g;
    rgb[0].b = pixel_b;
    WS2811RGB(rgb, ARRAYLEN(rgb));
    _delay_ms(LONGPAUSE);
// // Red
//   rgb[0].r = pixel_v;
//   rgb[0].g = 0;
//   rgb[0].b = 0;
//   WS2811RGB(rgb, ARRAYLEN(rgb));
//   _delay_ms(PAUSE);
// // Green
//   rgb[0].r = 0;
//   rgb[0].g = pixel_v;
//   rgb[0].b = 0;
//   WS2811RGB(rgb, ARRAYLEN(rgb));
//   _delay_ms(PAUSE);
// // Blue
//   rgb[0].r = 0;
//   rgb[0].g = 0;
//   rgb[0].b = pixel_v;
//   WS2811RGB(rgb, ARRAYLEN(rgb));
//   _delay_ms(PAUSE);
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
     string_lenth = ndx;
     ndx = 0;
     newData = true;
   }
 }
}

void showNewData() {
 if (newData == true) {
   uint8_t rd_pix = 0;
   uint8_t gr_pix = 0;
   uint8_t bl_pix = 0;
   //The arays need to be initiallised otherwise you'll get inccorret values.
   char ard_pix[] = {0,0,0,0,0};
   char agr_pix[] = {0,0,0,0,0};
   char abl_pix[] = {0,0,0,0,0};
   int rd=0,gr=0,bl=0;

   Serial.print("This just in ... ");
   Serial.println(receivedChars);

   Serial.print("String lenth ... ");
   Serial.println(string_lenth);

   for(int i = 0; i <= string_lenth; i++){
     if(receivedChars[i]!='x' && rd_pix == 0){
       ard_pix[rd] = receivedChars[i];
       rd++;
       if(receivedChars[i+1]=='x')rd_pix = 1;
     }
     else if(receivedChars[i]!='x' && gr_pix == 0){
       agr_pix[gr] = receivedChars[i];
       gr++;
       if(receivedChars[i+1]=='x')gr_pix = 1;
     }
     else if(receivedChars[i]!='x' && bl_pix == 0){
       abl_pix[bl] = receivedChars[i];
       bl++;
       if(receivedChars[i+1]=='x')bl_pix = 1;
     }
   }

  rd_pix = atoi(ard_pix);
  gr_pix = atoi(agr_pix);
  bl_pix = atoi(abl_pix);

  Serial.println(rd_pix);
  Serial.println(gr_pix);
  Serial.println(bl_pix);

   newData = false;
   threepixeldemo(rd_pix,gr_pix,bl_pix);
 }
}

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  // put your setup code here, to run once:
}

void loop() {
  recvWithEndMarker();
  showNewData();
}
