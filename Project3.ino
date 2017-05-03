#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define N_PIXELS  110
#define LED_PIN    3
#define POT_PIN   A5

int sensorValue = 0;
int pot_hue = 0;
float pot_fract = 0;

int r =0, g=0, b=0;


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
//after many tests, GRB was the correct bitstream. Otherwise, it changed to green.
void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  sensorValue = analogRead(POT_PIN);
  // getting data from our position info
  pot_hue = map(sensorValue, 0, 1024, 0, 360);
  pot_fract = ((float)sensorValue)/1024;
  h2rgb(pot_fract,r,g,b);
  
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print(". output = ");
  Serial.println(pot_hue);
  Serial.println(pot_fract);
  Serial.print(". In RGB this is: ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.println(b);  
//  // Some example procedures showing how to display to the pixels:

  colorWipe(strip.Color(r, g, b), 15); //testzzzz
//  Send a theater pixel chase in...
  theaterChase(strip.Color(r, g, b), 80); //chasetests
  
//  theaterChase(strip.Color(127, 0, 0), 50); // Red
//  theaterChase(strip.Color(0, 0, 127), 50); // Blue
//
 specRainbow(strip.Color(127, 0, 0), 50);
//  rainbow(20);
  // rainbowCycle(5);
  //theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void specRainbow(uint32_t c, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void h2rgb(float H, int& R, int& G, int& B) {

 int var_i;
 float S=1, V=1, var_1, var_2, var_3, var_h, var_r, var_g, var_b;

   var_h = H * 6; // .781*6 = 4.6875
   if ( var_h == 6 ) var_h = 0;      //H must be < 1
   var_i = int( var_h ) ;            //Or ... var_i = floor( var_h )
   var_1 = V * ( 1 - S ); //0
   var_2 = V * ( 1 - S * ( var_h - var_i ) ); // .3125
   var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) ); //.6875

   if      ( var_i == 0 ) { 
     var_r = V     ; 
     var_g = var_3 ; 
     var_b = var_1 ;
   }
   else if ( var_i == 1 ) { 
     var_r = var_2 ; 
     var_g = V     ; 
     var_b = var_1 ;
   }
   else if ( var_i == 2 ) { 
     var_r = var_1 ; 
     var_g = V     ; 
     var_b = var_3 ;
   }
   else if ( var_i == 3 ) { 
     var_r = var_1 ; 
     var_g = var_2 ; 
     var_b = V     ;
   }
   else if ( var_i == 4 ) { 
     var_r = var_3 ; 
     var_g = var_1 ; 
     var_b = V     ;
   }
   else                   { 
     var_r = V     ; 
     var_g = var_1 ; 
     var_b = var_2 ;
   }

   R = (1-var_r) * 255;                  //RGB results = 0 ÷ 255
   G = (1-var_g) * 255;
   B = (1-var_b) * 255;
 
}
