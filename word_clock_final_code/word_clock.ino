#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    64
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB


//settings
#define MODE 1 //1 for white words with rainbow bg, 2 for changing bg with colored words, 3 for plain bg with colored words, 4 for only words in rainbow
               // if you want to customise the display, you can make your own modes at the bottom of the code
#define BG_brightness 30
#define WORDS_brightness 255
#define hispeed true // if true, the LED transition will be set to maximum speed
#define UPDATES_PER_SECOND 10 // if hispeed is false, you can adjust the speed

CRGB leds[NUM_LEDS];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int currentView[] = {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
}; // to check the state of each LED (on or off)

/* start of declaring LEDs */

int five[] = {
   3,4,5,6,
 };
 int ten[] = {
   0,1,2,
 };
 int fifteen[]={
   16,17,18,20,21,22,23,
 };
 int twenty[]={
   24,25,26,27,28,29,
 };
 int thirty[]={
   8,9,10,11,13,15,
 };
 int forty[]={
   8,9,10,12,14,
 };
 int fifty[]={
   19,20,21,22,23,
 };
 

 int hours00[] = {
   41,42,44,45,46,47
 }; //12
 int hours01[] = {
   32,35,38,
 }; //1
 int hours02[] = {
   38,46,54,
 }; //2
 int hours03[] = {
   48,49,50,52,54,
 }; //3
 int hours04[] = {
   36,37,38,39,
 }; //4
 int hours05[] = {
   49,51,53,55,
 }; //5
 int hours06[] = {
   61,62,63
 }; //6
 int hours07[] = {
   40,41,42,43,63,
 }; //7
 int hours08[] = {   
   56,57,58,59,60,
 }; //8
 int hours09[] = { 
   32,33,34,35,
 }; //9
 int hours10[] = {  
   40,48,56,
 };  //10
 int hours11[] = { 
   40,41,42,43,44,45,
 }; //11

/* end of declaring LEDs */

int sayMinutes;
int oldMinutes;
int sayHours;

void setup() {
  Serial.begin(9600);
  
  delay(3000); //"safety delay"
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
    static uint8_t startIndex = 0;
    DateTime now = rtc.now();
    sayMinutes = now.minute()/5;
    sayHours = now.hour()%12;
      if (sayMinutes!=oldMinutes){
        oldMinutes=sayMinutes;
        for (int i = 0; i < 64; i++){
          currentView[i] = 0;
        }
        checkTime();
      }
    startIndex = startIndex + 1; /* motion speed */        
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    if (hispeed == false){
      FastLED.delay(1000/UPDATES_PER_SECOND);
    }
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.println();
}

void checkTime() {

    DateTime now = rtc.now();
    sayMinutes = now.minute()/5;
    sayHours = now.hour()%12;
/* ****************************************
   minutes
**************************************** */
  int toTurnOn = 0;
  //reset
  
  if (sayMinutes==0){
  //nothing
  }
    else if (sayMinutes==1){
      for(int i=0;i<sizeof(five)/2;i++){
        toTurnOn = five[i];
        currentView[toTurnOn]=1;
      }
      currentView[30]=1;
      currentView[31]=1;
    }
    //ten
    else if (sayMinutes==2){
      for(int i=0;i<sizeof(ten)/2;i++){
        toTurnOn = ten[i];
        currentView[toTurnOn]=1;
      }
    }
    //fifteen
    else if (sayMinutes==3){
      for(int i=0;i<sizeof(fifteen)/2;i++){
        toTurnOn = fifteen[i];
        currentView[toTurnOn]=1;
      }
    }
    //twenty
    else if (sayMinutes==4){
      for(int i=0;i<sizeof(twenty)/2;i++){
        toTurnOn = twenty[i];
        currentView[toTurnOn]=1;
      }
    }
    //twenty five
    else if (sayMinutes==5){
      for(int i=0;i<sizeof(twenty)/2;i++){
        toTurnOn = twenty[i];
        currentView[toTurnOn]=1;
      }
      for(int i=0;i<sizeof(five)/2;i++){
        toTurnOn = five[i];
        currentView[toTurnOn]=1;
      }
    }
    //thirty past
    else if (sayMinutes==6){
      for(int i=0;i<sizeof(thirty)/2;i++){
        toTurnOn = thirty[i];
        currentView[toTurnOn]=1;
      }
    }
    //thirty five past
    else if (sayMinutes==7){
      for(int i=0;i<sizeof(thirty)/2;i++){
        toTurnOn = thirty[i];
        currentView[toTurnOn]=1;
      }
      for(int i=0;i<sizeof(five)/2;i++){
        toTurnOn = five[i];
        currentView[toTurnOn]=1;
      }
    }
    //forty
    else if (sayMinutes==8){
      for(int i=0;i<sizeof(forty)/2;i++){
        toTurnOn = forty[i];
        currentView[toTurnOn]=1;
      }
    }
    //forty five
    else if (sayMinutes==9){
      for(int i=0;i<sizeof(forty)/2;i++){
        toTurnOn = forty[i];
        currentView[toTurnOn]=1;
      }
      for(int i=0;i<sizeof(five)/2;i++){
        toTurnOn = five[i];
        currentView[toTurnOn]=1;
      }
    }
    //fifty
    else if (sayMinutes==10){
      for(int i=0;i<sizeof(fifty)/2;i++){
        toTurnOn = fifty[i];
        currentView[toTurnOn]=1;
      }
    }
    //fifty five
    else if (sayMinutes==11){
      for(int i=0;i<sizeof(fifty)/2;i++){
        toTurnOn = fifty[i];
        currentView[toTurnOn]=1;
      }
      for(int i=0;i<sizeof(five)/2;i++){
        toTurnOn = five[i];
        currentView[toTurnOn]=1;
      }
  }
/* ****************************************
    hours
**************************************** */

    if (sayHours==0){
      for(int i=0;i<sizeof(hours00)/2;i++){
        toTurnOn = hours00[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==1){
      for(int i=0;i<sizeof(hours01)/2;i++){
        toTurnOn = hours01[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==2){
      for(int i=0;i<sizeof(hours02)/2;i++){
        toTurnOn = hours02[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==3){
      for(int i=0;i<sizeof(hours03)/2;i++){
        toTurnOn = hours03[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==4){
      for(int i=0;i<sizeof(hours04)/2;i++){
        toTurnOn = hours04[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==5){
      for(int i=0;i<sizeof(hours05)/2;i++){
        toTurnOn = hours05[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==6){
      for(int i=0;i<sizeof(hours06)/2;i++){
        toTurnOn = hours06[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==7){
      for(int i=0;i<sizeof(hours07)/2;i++){
        toTurnOn = hours07[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==8){
      for(int i=0;i<sizeof(hours08)/2;i++){
        toTurnOn = hours08[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==9){
      for(int i=0;i<sizeof(hours09)/2;i++){
        toTurnOn = hours09[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==10){
      for(int i=0;i<sizeof(hours10)/2;i++){
        toTurnOn = hours10[i];
        currentView[toTurnOn]=1;
      }
    }
    else if (sayHours==11){
      for(int i=0;i<sizeof(hours11)/2;i++){
        toTurnOn = hours11[i];
        currentView[toTurnOn]=1;
      }
    }
}

/* As the name implies, it fills the LEDs based on the palette of colours */


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  static uint8_t BG_RGB = 0;

  
// mode 1: words are white, background is rainbow
  if (MODE==1){
    for( int i = 0; i < NUM_LEDS; i++) {
      if (currentView[i]==1){
        leds[i].setRGB(255,255,255);
        colorIndex += 1;
      }
      else{
        leds[i] = ColorFromPalette( currentPalette, colorIndex, BG_brightness, currentBlending);
        colorIndex += 1;
      }
    }
  }

// mode 2: words are white, background is solid color but changes
  if (MODE==2){
    BG_RGB += 1;
    for( int i = 0; i < NUM_LEDS; i++) {
      if (currentView[i]==1){
        leds[i] = ColorFromPalette( currentPalette, colorIndex, WORDS_brightness, currentBlending);
        colorIndex += 3;
      }
      else{
        leds[i] = ColorFromPalette( currentPalette, BG_RGB, BG_brightness, currentBlending);
        colorIndex += 3;
      }
    }
  }

// mode 3: words are rainbow, background is solid color without changing
  if (MODE==3){
    for( int i = 0; i < NUM_LEDS; i++) {
      if (currentView[i]==1){
        leds[i] = ColorFromPalette( currentPalette, colorIndex, WORDS_brightness, currentBlending);
        colorIndex += 1;
      }
      else{
        leds[i].setRGB(0,10,15);
        colorIndex += 1;
      }
    }
  }

// mode 4: words are rainbow, background is turned off
  if (MODE==4){
    BG_RGB += 3;
    for( int i = 0; i < NUM_LEDS; i++) {
      if (currentView[i]==1){
        leds[i] = ColorFromPalette( currentPalette, colorIndex, WORDS_brightness, currentBlending);
        colorIndex += 1;
      }
      else{
        leds[i].setRGB(0,0,0);
        colorIndex += 1;
      }
    }
  }
    
}
