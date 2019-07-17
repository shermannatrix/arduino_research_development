#include <Arduino.h>
#include <FastLED.h>
#define NUM_LEDS	64
#define DATA_PIN	5

// We need to set up a block of memory that will be used for storing & manipulating
// the led data.
CRGB leds[NUM_LEDS];

void setup() {
	FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB::YellowGreen;
		
		//leds[i] = CRGB::Black;
		//FastLED.show();
	}
	FastLED.show();
	delay(30);
}