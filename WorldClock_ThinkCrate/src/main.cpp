#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>

#define LED_PIN		5
#define COLOR_ORDER	GRB
#define CHIPSET		WS2812
#define NUM_LEDS	64

#define BRIGHTNESS	200
#define FRAMES_PER_SECOND	10

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];
CRGBPalette16 gPal;


void Fire2012WithPalette();

void setup() {
	// put your setup code here, to run once:
	delay(3000);
	FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);

	gPal = HeatColors_p;
}

void loop() {
	random16_add_entropy(random());

	Fire2012WithPalette();

	FastLED.show();
	FastLED.delay(1000 / FRAMES_PER_SECOND);
}

#define COOLING		55
#define SPARKING	120

void Fire2012WithPalette() {
	// Array of temperature readings at each simulation cell
	static byte heat[NUM_LEDS];

	// Step 1. Cool down every cell a little
	for (int i = 0; i < NUM_LEDS; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
	}

	// Step 2. Heat from each cell drifts 'up' and diffuses a little
	for (int k = NUM_LEDS - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}

	// Step 3. Randomly ignite new 'sparks' of heat near the bottom
	if (random8() < SPARKING) {
		int y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}

	for (int j = 0; j < NUM_LEDS; j++) {
		byte colorindex = scale8(heat[j], 240);
		CRGB color = ColorFromPalette(gPal, colorindex);
		int pixelnumber;
		if(gReverseDirection) {
			pixelnumber = (NUM_LEDS - 1) - j;
		} else {
			pixelnumber = j;
		}
		leds[pixelnumber] = color;
	}
}