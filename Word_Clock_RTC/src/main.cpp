#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char months[12][10] = { 
	"January", "February", 
	"March", "April", 
	"May", "June",
	"July", "August", 
	"September", "October", 
	"November", "December" };

char daysOfTheWeek[7][12] = { 
	"Sunday", "Monday", 
	"Tuesday", "Wednesday", "Thursday",
	"Friday", "Saturday" };

void setup() {
	// Let's open a Serial Port with the
	// baudrate of 9600
	Serial.begin(9600);

	// Add a delay of 3 seconds.
	delay(3000);

	if (!rtc.begin()) {
		Serial.println("Couldn't detect RTC module.");
		while(1);
	}

	if (rtc.lostPower()) {
		Serial.println("RTC has lost power. Let's set the time.");
	}
}

void loop() {
	DateTime now = rtc.now();

	Serial.print(now.year(), DEC);
	Serial.print("-");
	//if (now.month() < 10)
	//	Serial.print("0");
	Serial.print(months[now.month()-1]);
	//Serial.print(now.month(), DEC);
	Serial.print("-");
	if (now.day() < 10)
		Serial.print("0");
	Serial.print(now.day(), DEC);
	Serial.print(" (");
	Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
	Serial.print(") ");
	if (now.hour() < 10)
		Serial.print("0");
	Serial.print(now.hour());
	Serial.print(":");
	if (now.minute() < 10)
		Serial.print("0");
	Serial.print(now.minute());
	Serial.print(":");
	if (now.second() < 10)
		Serial.print("0");
	Serial.print(now.second());
	Serial.println();
	delay(1000);
}