

//The Castle Fun Center Prize Wheel V17.0
//Designed & Programmed by Mike Baier
//--Objective- Create a "prize wheel"
//utilizing lights and audio to randomly generate winning
//zones within an area to award a prize.
//wheel is activated with a button press 
//A Random LED is choosen as the winner, LED flashes, Audio plays


#include "Adafruit_WS2801.h"
#include <Adafruit_NeoPixel.h>
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include "SPI.h"
// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);
#include <avr/power.h>


#include <Adafruit_Soundboard.h>



//#include <Adafruit_NeoPixel.h>
#define NUMBER_OF_FLASHES          10
#define FLASH_RATE                 400
#define BUTTON_PIN   8    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define BUTTONPIXEL_PIN 5 //Digital IO pin connected to button pixels

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 24    //Neopixel group A count

#define PIXEL_COUNTB 16   //Button Neopixel group Count

#define BRIGHTNESS 10     // Set Brightness of all Pixels

#define BUTTONBRIGHTNESS 100 // Set brightness of button pixels


uint8_t dataPin  = 9;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 10;    // Green wire on Adafruit Pixels

int Audio1 = 36;
int Audio2 = 46;
int Audio3 = 44;
int Audio4 = 42;
int Audio5 = 40;
int Audio6 = 48;
int Audio7 = 38;
int Audio8 = 34;
int Audio9 = 32;
int Audio10= 30;

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGBW    Pixels are wired for RGBW bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRBW + NEO_KHZ800);
//Adafruit_NeoPixel stripb = Adafruit_NeoPixel(PIXEL_COUNTB, BUTTONPIXEL_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin );
Adafruit_NeoPixel stripb = Adafruit_NeoPixel(PIXEL_COUNTB, BUTTONPIXEL_PIN, NEO_GRBW + NEO_KHZ800);

int PrizeLED = 0;


int randomledchoice;

void setup() {
   Serial.begin(9600);
    Serial.println("THE CASTLE PRIZE-O-MATIC VS1053 Library Test");

  
    
    // set up the LCD's number of rows and columns: 
  
   lcd.begin(20, 4);
  
  /* pinMode(Audio1, OUTPUT);
   pinMode(Audio2, OUTPUT);
   pinMode(Audio3, OUTPUT);
   pinMode(Audio4, OUTPUT);
   pinMode(Audio5, OUTPUT);
   pinMode(Audio6, OUTPUT);
   pinMode(Audio7, OUTPUT);
   pinMode(Audio8, OUTPUT);
   pinMode(Audio9, OUTPUT);
   pinMode(Audio10, OUTPUT);
*/
   Serial.println(" Castle Prize-O-MATIC- SYSTEM READY!");
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show();// Initialize all pixels to 'off'
  
  stripb.setBrightness(BUTTONBRIGHTNESS);
  stripb.begin();
  stripb.show();
  
  

}

void loop(){
  // Get current button state and handle result
  
  
  if (digitalRead(BUTTON_PIN)==LOW) {
    
    Serial.println(" Button Pressed");  
    playgame();  //activate the spinning lights for the game
     
     
  }
  
  else
    {
   
    
  Serial.println(" Returning to Attract Mode");
  attractMode();
// Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("PRIZE-O-MATIC V1.0!");
   lcd.setCursor(2, 1);
   lcd.print("The Castle");
   lcd.setCursor(4,8);
   lcd.print("System Ready!"); 
  }
}
  
  
  // Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
 for(uint16_t i=0; i<strip.numPixels(); i++) {
   strip.setPixelColor(i, c);
   stripb.setPixelColor(i, c);
   strip.show();
   stripb.show();
   delay(wait);
   

    
    
  }
}


//Theatre-style crawling lights.
void theaterChase3(uint32_t c, uint8_t wait) {
  for (int j=0; j<20; j++) {  //do 20 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void theaterChase(uint32_t c, uint8_t wait, int randomledchoice)
{
   for (int i = 0; i < randomledchoice+1; i++)
   {
      strip.setPixelColor(i, c);
      strip.setPixelColor(i-1, 0);
      strip.show();
      delay(wait);
   }
}

void attractMode(void) 
{
  
  
  colorWipe(Color(0, 255, 0), 20);  
   if (digitalRead(BUTTON_PIN)==LOW) {
    
    Serial.println(" Button Pressed");  
    playgame(); 
   }
   //activate the spinning lights for the game
    //White
  colorWipe(Color(255, 0, 255), 20);  // Purple
  strip.show();
   if (digitalRead(BUTTON_PIN)==LOW) {
    
    Serial.println(" Button Pressed");  
    playgame(); 
   }
 colorWipe(stripb.Color(0, 255, 0), 20);     //White
  if (digitalRead(BUTTON_PIN)==LOW) {
    
    Serial.println(" Button Pressed");  
    playgame(); 
   }
  colorWipe(stripb.Color(255, 0, 255), 20);  // Purple
   if (digitalRead(BUTTON_PIN)==LOW) {
    
    Serial.println(" Button Pressed");  
    playgame(); 
   }
  stripb.show();
  
}

void playgame(void)
{
  randomSeed(millis()); // Seed the random generator with random amount of millis()

 Serial.println(" Seeding Random Generator");
 

 lcd.clear();
 lcd.setCursor(1,2);
 lcd.print("WHEEL SPINNING!");

 
 randomled();
 //theaterChase(Color(127, 127, 127), 40, 25);
 /*theaterChase(Color(127, 127, 127), 50, 25);
 theaterChase(Color(127, 127, 127), 50, 25);
 theaterChase(Color(127, 127, 127), 50, randomledchoice);
         
      strip.show(); 
      Serial.println(" play game sequence");
      //randomled();  // get a random LED zone to indicate the prize won
      lcd.clear();
     
   */   
} 

// Adds a new random led choice to the game sequence, by sampling the timer
void randomled(void)
{
  randomSeed(millis()); // Seed the random generator with random amount of millis()
 int  randomledchoice = random(1,26); //min (included), max (exluded)\

 Serial.println(" Random LED is:");
 Serial.println(randomledchoice);

   // We have to convert this number, 0 to 25, to convert to LED Zone/pixels
  //if(randomledchoice == 0) LEDzone1();
   if(randomledchoice == 1) LEDzone1();
  else if(randomledchoice == 2) LEDzone2();
  else if(randomledchoice == 3) LEDzone3();
  else if(randomledchoice == 4) LEDzone4();
  else if(randomledchoice == 5) LEDzone5();
  else if(randomledchoice == 6) LEDzone6();
  else if(randomledchoice == 7) LEDzone7();
  else if(randomledchoice == 8) LEDzone8();
  else if(randomledchoice == 9) LEDzone9();
  else if(randomledchoice == 10) LEDzone10();
  else if(randomledchoice == 11) LEDzone11();
  else if(randomledchoice == 12) LEDzone12();
  else if(randomledchoice == 13) LEDzone13();
  else if(randomledchoice == 14) LEDzone14();
  else if(randomledchoice == 15) LEDzone15();
  else if(randomledchoice == 16) LEDzone16();
  else if(randomledchoice == 17) LEDzone17();
  else if(randomledchoice == 18) LEDzone18();
  else if(randomledchoice == 19) LEDzone19();
  else if(randomledchoice == 20) LEDzone20();
  else if(randomledchoice == 21) LEDzone21();
  else if(randomledchoice == 22) LEDzone22();
  else if(randomledchoice == 23) LEDzone23();
  else if(randomledchoice == 24) LEDzone24();
  else if(randomledchoice == 25) LEDzone25();


  
  
  //PrizeLED=randomledchoice;
 
  
  
}

void LEDzone1(void)
{
Serial.println(" LED Zone 1");


pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
  
   

    
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 0);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);

 pinMode( Audio1, INPUT );
    digitalWrite( Audio1, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio1, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio1, INPUT );    //  back to input mode


  strip.setPixelColor(1, 0, 255, 0); 
   strip.setPixelColor(24, 0, 255, 0); 
    strip.setPixelColor(23, 0, 255, 0); 
    
 
     
     
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(0, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(0, 0, 0, 0);

  strip.show();  
  delay(FLASH_RATE);
}
 
  


}

void LEDzone2(void)

{
   Serial.println(" LED Zone 2");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
   
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 1);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);

 
 strip.setPixelColor(0, 0, 255, 0); 
   strip.setPixelColor(24, 0, 255, 0); 
    strip.setPixelColor(23, 0, 255, 0);

    
    pinMode( Audio1, INPUT );
    digitalWrite( Audio1, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio1, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio1, INPUT );    //  back to input mode

    
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(1, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(1, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone3(void)
{
 Serial.println(" LED Zone 3");

pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
 
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 2);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);

  pinMode( Audio7, INPUT );
    digitalWrite( Audio7, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio7, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio7, INPUT );    //  back to input mode
 
 strip.setPixelColor(3, 0, 255, 0); 
   strip.setPixelColor(4, 0, 255, 0); 
    strip.setPixelColor(5, 0, 255, 0);
  
 pinMode( Audio1, INPUT );
    digitalWrite( Audio1, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio1, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio1, INPUT );    //  back to input mode

    
 for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(2, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(2, 0, 0, 0);

  strip.show();  
  delay(FLASH_RATE);
 }
}

void LEDzone4(void)
{
 Serial.println(" LED Zone 4");

pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
    
  theaterChase(Color(127, 127, 127), 50, 26);
  theaterChase(Color(127, 127, 127), 50, 26);
  theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 3);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);

pinMode( Audio7, INPUT );
    digitalWrite( Audio7, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio7, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio7, INPUT );    //  back to input mode
    
 strip.setPixelColor(2, 0, 255, 0); 
   strip.setPixelColor(4, 0, 255, 0); 
    strip.setPixelColor(5, 0, 255, 0);
    

  
 for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(3, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(3, 0, 0, 0);

  strip.show();  
  delay(FLASH_RATE);
 }
}

void LEDzone5(void)
{

 Serial.println(" LED Zone 5");

 pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    
  theaterChase(Color(127, 127, 127), 50, 26);
  theaterChase(Color(127, 127, 127), 50, 26);
  theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 4);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);

pinMode( Audio7, INPUT );
    digitalWrite( Audio7, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio7, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio7, INPUT );    //  back to input mode
    

 strip.setPixelColor(2, 0, 255, 0); 
   strip.setPixelColor(3, 0, 255, 0); 
    strip.setPixelColor(5, 0, 255, 0);
  
  
 for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(4, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(4, 0, 0, 0);

  strip.show();  
  delay(FLASH_RATE);
 }
}



void LEDzone6(void)

{
   Serial.println(" LED Zone 6");
  
   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
    
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 5);
 
 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);

pinMode( Audio7, INPUT );
    digitalWrite( Audio7, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio7, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio7, INPUT );    //  back to input mode

    
    strip.setPixelColor(2, 0, 255, 0); 
   strip.setPixelColor(3, 0, 255, 0); 
    strip.setPixelColor(4, 0, 255, 0);

    
 for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(5, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(5, 0, 0, 0);

  strip.show();  
  delay(FLASH_RATE);
 }
}



void LEDzone7(void)
{
   Serial.println(" LED Zone 7");

pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
    
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 6);

 
 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


  pinMode( Audio2, INPUT );
    digitalWrite( Audio2, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio2, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio2, INPUT );    //  back to input mode
    
 for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(6, 255, 255, 255); 
 
  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(6, 0, 0, 0);

  strip.show();  
  delay(FLASH_RATE);
 }
}

void LEDzone8(void)

{
   Serial.println(" LED Zone 8");

    pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 7);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(8, 0, 255, 0); 
   strip.setPixelColor(9, 0, 255, 0); 
    strip.setPixelColor(10, 0, 255, 0);

pinMode( Audio3, INPUT );
    digitalWrite( Audio3, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio3, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio3, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(7, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(7, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone9(void)

{
   Serial.println(" LED Zone ");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
    
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 8);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(7, 0, 255, 0); 
   strip.setPixelColor(9, 0, 255, 0); 
    strip.setPixelColor(10, 0, 255, 0);

    pinMode( Audio3, INPUT );
    digitalWrite( Audio3, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio3, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio3, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(8, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(8, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone10(void)

{
   Serial.println(" LED Zone 10");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
    
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 9);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(7, 0, 255, 0); 
   strip.setPixelColor(8, 0, 255, 0); 
    strip.setPixelColor(10, 0, 255, 0);

    pinMode( Audio3, INPUT );
    digitalWrite( Audio3, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio3, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio3, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(9, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(9, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone11(void)

{
   Serial.println(" LED Zone 11");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real


    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 10);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(7, 0, 255, 0); 
   strip.setPixelColor(8, 0, 255, 0); 
    strip.setPixelColor(9, 0, 255, 0);

    pinMode( Audio3, INPUT );
    digitalWrite( Audio3, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio3, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio3, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(10, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(10, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone12(void)

{
   Serial.println(" LED Zone 12");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 11);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(12, 0, 255, 0); 
   strip.setPixelColor(13, 0, 255, 0); 
    strip.setPixelColor(14, 0, 255, 0);
 
    pinMode( Audio4, INPUT );
    digitalWrite( Audio4, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio4, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio4, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(11, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(11, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone13(void)

{
   Serial.println(" LED Zone 13");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 12);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(11, 0, 255, 0); 
   strip.setPixelColor(13, 0, 255, 0); 
    strip.setPixelColor(14, 0, 255, 0);
    
   pinMode( Audio4, INPUT );
    digitalWrite( Audio4, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio4, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio4, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(12, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(12, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone14(void)

{
   Serial.println(" LED Zone 14");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
    
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 13);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(11, 0, 255, 0); 
   strip.setPixelColor(12, 0, 255, 0); 
    strip.setPixelColor(14, 0, 255, 0);


     pinMode( Audio4, INPUT );
    digitalWrite( Audio4, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio4, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio4, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(13, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(13, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone15(void)

{
   Serial.println(" LED Zone 15");

pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 14);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(11, 0, 255, 0); 
   strip.setPixelColor(12, 0, 255, 0); 
    strip.setPixelColor(13, 0, 255, 0);

      pinMode( Audio4, INPUT );
    digitalWrite( Audio4, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio4, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio4, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(14, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(14, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone16(void)

{
   Serial.println(" LED Zone 16");

pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
   
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 15);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(16, 0, 255, 0); 
   strip.setPixelColor(17, 0, 255, 0); 
    strip.setPixelColor(18, 0, 255, 0);

     pinMode( Audio5, INPUT );
    digitalWrite( Audio5, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio5, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio5, INPUT );    //  back to input mode

    
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(15, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(15, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone17(void)

{
   Serial.println(" LED Zone 17");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 16);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);



 strip.setPixelColor(15, 0, 255, 0); 
   strip.setPixelColor(17, 0, 255, 0); 
    strip.setPixelColor(18, 0, 255, 0);

     pinMode( Audio5, INPUT );
    digitalWrite( Audio5, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio5, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio5, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(16, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(16, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone18(void)

{
   Serial.println(" LED Zone 18");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 17);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(15, 0, 255, 0); 
   strip.setPixelColor(16, 0, 255, 0); 
    strip.setPixelColor(18, 0, 255, 0);

    pinMode( Audio5, INPUT );
    digitalWrite( Audio5, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio5, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio5, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(17, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(17, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone19(void)

{
   Serial.println(" LED Zone 19");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 18);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(15, 0, 255, 0); 
   strip.setPixelColor(16, 0, 255, 0); 
    strip.setPixelColor(17, 0, 255, 0);
    
  pinMode( Audio5, INPUT );
    digitalWrite( Audio5, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio5, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio5, INPUT );    //  back to input mode
    
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(18, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(18, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone20(void)

{
   Serial.println(" LED Zone 20");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 19);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(20, 0, 255, 0); 
   strip.setPixelColor(21, 0, 255, 0); 
    strip.setPixelColor(22, 0, 255, 0);

    
    pinMode( Audio6, INPUT );
    digitalWrite( Audio6, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio6, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio6, INPUT );    //  back to input mode

    
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(19, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(19, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone21(void)

{
   Serial.println(" LED Zone 21");
   
   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 20);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(19, 0, 255, 0); 
   strip.setPixelColor(21, 0, 255, 0); 
    strip.setPixelColor(22, 0, 255, 0);


      pinMode( Audio6, INPUT );
    digitalWrite( Audio6, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio6, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio6, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(20, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(20, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone22(void)

{
   Serial.println(" LED Zone 22");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 21);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(19, 0, 255, 0); 
   strip.setPixelColor(20, 0, 255, 0); 
    strip.setPixelColor(22, 0, 255, 0);

   pinMode( Audio6, INPUT );
    digitalWrite( Audio6, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio6, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio6, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(21, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(21, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone23(void)

{
   Serial.println(" LED Zone 23");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real

    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 22);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(19, 0, 255, 0); 
   strip.setPixelColor(20, 0, 255, 0); 
    strip.setPixelColor(21, 0, 255, 0);


       pinMode( Audio6, INPUT );
    digitalWrite( Audio6, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio6, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio6, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(22, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(22, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone24(void)

{
   Serial.println(" LED Zone 24");

   pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
 
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 23);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(24, 0, 255, 0); 
   strip.setPixelColor(0, 0, 255, 0); 
    strip.setPixelColor(1, 0, 255, 0);


         pinMode( Audio1, INPUT );
    digitalWrite( Audio1, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio1, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio1, INPUT );    //  back to input mode
   
for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(23, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(23, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}
}

void LEDzone25(void)

{
Serial.println(" LED Zone 25");

pinMode( Audio9, INPUT );
    digitalWrite( Audio9, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio9, OUTPUT );   //  now pull the FX pin low for real
  
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
    theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 26);
 theaterChase(Color(127, 127, 127), 50, 24);

 pinMode( Audio9, INPUT );    //  back to input mode

 delay(20);


 strip.setPixelColor(23, 0, 255, 0); 
   strip.setPixelColor(0, 0, 255, 0); 
    strip.setPixelColor(1, 0, 255, 0);


           pinMode( Audio1, INPUT );
    digitalWrite( Audio1, LOW ); //  legal even if it doesn't seem to do anything
    pinMode( Audio1, OUTPUT );   //  now pull the FX pin low for real
    delay( 125 );           //  wait for 125ms
    pinMode( Audio1, INPUT );    //  back to input mode

     for (int i=0; i<NUMBER_OF_FLASHES; i++) {
  strip.setPixelColor(24, 255, 255, 255); 

  strip.show();
  delay(FLASH_RATE);
  strip.setPixelColor(24, 0, 0, 0);
 
  strip.show();  
  delay(FLASH_RATE);
}

  



}

 
//**********************************************************************************************

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}





// Create a 24 bit color value from R,G,B for WS2801
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}


//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


