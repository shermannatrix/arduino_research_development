#include <Arduino.h>
#include "FastLED.h"

#define LED_PIN		5
#define CHIPSET		WS2812

CRGB leds[64];

void setup() {
	FastLED.addLeds<CHIPSET, LED_PIN>(leds, 64);
}

void loop() {
	static uint8_t hue = 0;
  	FastLED.showColor(CHSV(hue++, 255, 255)); 
  	delay(10);
}