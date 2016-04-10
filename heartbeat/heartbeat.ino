#include <EEPROM.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
  #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Constant definitions
#define maxBrightness 255.0
#define maxTimeOn 9999 
#define blinkTime 125 

#define ARDUINO 1
  #define buzzerPin 11
  #define heartPin 6 
  #define ledPin 13
  #define lightPin A1
  #define lightPullUp A1
  #define touchPin A3
  #define touchPullUp A3

// Variables and constants for fading pin. Needs to be a hardware PWM pin; on
byte heartStage = 0;
int heartBrightness = 0;
byte heartCounter = 0;

// sleep & timing variables
boolean led_status = LOW;
boolean sensor_reset = true;
const long counts_on = 6000; //  6000 is aprox 1 minute
boolean awake = true;
boolean cur_light = false;
//boolean last_light = false;


void setup(){

    Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(heartPin, OUTPUT);
}

void loop(){

      digitalWrite(heartPin, HIGH);
      pinMode(ledPin, OUTPUT);  
      digitalWrite(ledPin, HIGH);
        blink_loop();
      digitalWrite(heartPin, LOW);
      digitalWrite(ledPin, LOW);  
    
}

boolean blink_loop(){
  long counter = 0;
  while (counter < counts_on){
    delayMicroseconds(maxTimeOn);
  
    // calculate brightness for heartbeat pin (by cycling 
    // through phases of pulse pattern)
    heartCounter++;
    if (heartCounter > 144) {
      heartStage = (heartStage + 1) % 4;
      heartCounter = 0;
    }
    else {
      switch(heartStage) {
        case 0:
          analogWrite(heartPin, heartBrightness);
          heartCounter += 144/12.0;
          heartBrightness += 255/12.0;
          if (heartBrightness > 255)
            heartBrightness = 255;
          break;
        case 1:
          analogWrite(heartPin, heartBrightness);
          heartCounter += 144/24.0;
          heartBrightness -= 255/24.0;
          if (heartBrightness < 0)
            heartBrightness = 0;
          break;
        case 2:
          analogWrite(heartPin, heartBrightness);
          heartCounter += 144/12.0;
          heartBrightness += 255/12.0;
          if (heartBrightness > 255)
            heartBrightness = 255;
          break;
        case 3:
          analogWrite(heartPin, heartBrightness);
          heartCounter += 144/72.0;
          heartBrightness -= 255/72.0;
          if (heartBrightness < 0)
            heartBrightness = 0;
          break;
      }
    }
  }
}
