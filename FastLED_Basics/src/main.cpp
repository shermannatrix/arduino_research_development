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
	/* leds[0] = CRGB::Red;
	FastLED.show();
	delay(30); */

	int val = analogRead(2);

	int numLedsToLight = map(val, 0, 1023, 0, NUM_LEDS);

	// First, clear the existing led values
	FastLED.clear();
	for (int led = 0; led < numLedsToLight; led++) {
		leds[led] = CRGB::Blue;
	}

	FastLED.show();
}