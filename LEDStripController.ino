#include <Adafruit_NeoPixel.h>

const int STRIP_LENGTH = 37;

const int LED_STRIP_PIN = 4;

const int BRIGHTNESS_POT = A6;
const int BRIGHTNESS_SWITCH = 8;

const int COLOR_POT = A3;
const int COLOR_SWITCH = 6;

float brightness = 0.0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LENGTH, LED_STRIP_PIN,
                            NEO_GRB + NEO_KHZ800);

void setup() {
  
   pinMode(COLOR_POT, INPUT);
   pinMode(COLOR_SWITCH, INPUT_PULLUP);
   pinMode(BRIGHTNESS_POT, INPUT);
   pinMode(BRIGHTNESS_SWITCH, INPUT_PULLUP);
   Serial.begin(9600);
   strip.begin();
   strip.show();    
}

void loop() {
  if (digitalRead(BRIGHTNESS_SWITCH) == HIGH) {
      // Get the percentage of the full brightness.
      brightness = 1.0 - (analogRead(BRIGHTNESS_POT) / 1023.0);
      Serial.print("Brightness: ");
      Serial.println(brightness);
     if (digitalRead(COLOR_SWITCH) == HIGH) {
        // Scale down the color range.
        int color = (analogRead(COLOR_POT) / 1023.0)  *  245. .0;
        Serial.print("Color: ");
       Serial.println(color);
        calculateAndChangeColor(color);
      } else {
          // Color is disabled. Change strip to white.
          changeColor(255, 255, 255);
          Serial.println("Color disabled");
      }  
  } else {
      changeColor(0,0,0); 
      Serial.println("Strip is off");
  }  

  delay(50);

}

void changeColor(int red, int green, int blue) {
    int i;
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, red*brightness, green*brightness, blue*brightness);
    }
    strip.show();
}

// This is based on the Adafruit NeoPixel strandtest example.
void calculateAndChangeColor(int potValue) {
  int red = 0;
  int green = 0;
  int blue = 0;
  if(potValue < 85) {
    red = potValue * 3;
    green = 255 - potValue * 3;
  } else if(potValue < 170) {
     potValue -= 85;
     red = 255 - potValue * 3;
     blue = potValue * 3;
  } else {
     potValue -= 170;
     green = potValue * 3;
     blue = 255 - potValue * 3;
  }
  changeColor(red, green, blue);
  
} 


