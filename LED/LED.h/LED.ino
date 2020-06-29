#include "LED.h"

const int SPEEDFAKTOR = 1;
const int NR_OF_LEDS = 4;
LED led[] = {
  LED(11),
  LED(10),
  LED(9),
  LED(6)
};


void updateLed(LED *led){
  int brightness;
  if(led->getLedStatus() == FADE_UP){
    brightness = (double) (millis()-led->getFadeStart())/led->getFadeTime()*255;
    if (brightness>255) {
      led->on();
      brightness = 255; // dont want anything over 255;
    }
    led->setBrightness(brightness);
  }
  if(led->getLedStatus() == FADE_DOWN){
    brightness = 255 * (1 - (double) (millis()-led->getFadeStart())/led->getFadeTime() );
    if (brightness<0) {
      led->off();
      brightness = 0; // dont want anything under 0;
    }
    led->setBrightness(brightness);
  }
  analogWrite(led->getPin(),led->getBrightness());
}

void updateLeds(){
  for(int i=0;i<NR_OF_LEDS;i++){
    updateLed(&led[i]);
  }
}

void waitAndUpdate(int waitTimeMs){
  unsigned long startTime = millis();
  while(millis()-startTime<waitTimeMs){
    updateLeds();
    delay(10);
  }
}

// Setting up the system
void setup() {
  Serial.begin(9600); // to communicate with the PC
  Serial.print("\n\n****** Welcome Master Carina! I am here to serve you!******\n");
}

void blinkLed(LED *led, int durationOn, int durationOff, int nrOfBlinks){
  for(int i=0;i<nrOfBlinks;i++){
    led->on();
    waitAndUpdate(durationOn);
    led->off();
    waitAndUpdate(durationOff);
  }
}

unsigned long loopCounter=0;
void loop(){
  loopCounter++;
  Serial.print("\n\n*** Loop start ");
  Serial.print(loopCounter);
  Serial.print(" ***\n");
  blinkLed(&led[0],2000,1000,2);
}
