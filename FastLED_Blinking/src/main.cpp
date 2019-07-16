#include <Arduino.h>
#include <Wire.h>
#include "FastLED.h"

#define LED_PIN		5
#define CHIPSET		WS2812

CRGB leds[64];

void setup() {
	FastLED.addLeds<CHIPSET, LED_PIN>(leds, 64);
}

void loop() {
	for (int i = 0; i < 64; i++) {
		leds[i] = CRGB::White;
		FastLED.show();
		delay(50);
		leds[i] = CRGB::Black;
		FastLED.show();
		delay(50);
	}

	for (int i = 62; i > 0; i--) {
		leds[i] = CRGB::White;
		FastLED.show();
		delay(50);
		leds[i] = CRGB::Black;
		FastLED.show();
		delay(50);
	}
}