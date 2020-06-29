#include "hopfenlicht.h"

const int SPEEDFAKTOR = 1;
const int NR_OF_LEDS = 4;
LED led[] = {
  LED(11),
  LED(10),
  LED(9),
  LED(6)
};

enum modus {
  AQUA, // random fading
  HOPSCOTCH,
  CROSSOVER,
  TRICKLE_DOWN,
  TRICKLE_UP
};

void updateLeds(){
  for(int i=0;i<NR_OF_LEDS;i++){
    led[i].updateLed();
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
  randomSeed(analogRead(0));
}


void blinkLed(LED *led, int durationOn, int durationOff, int nrOfBlinks){
  for(int i=0;i<nrOfBlinks;i++){
    led->on();
    waitAndUpdate(durationOn);
    led->off();
    waitAndUpdate(durationOff);
  }
}

void aqua(){
  aqua(waitingTime()/4);
  aqua(waitingTime()/4);
  aqua(waitingTime()/4);
  aqua(waitingTime()/4);
}
void aqua(int waitingTime){
  // Serial.println("** Aqua method **");
  for(int i=0;i<NR_OF_LEDS;i++){
    if(random(100)<50){
      led[i].fadeTo(random(150,255),waitingTime);
    }
    else{
      led[i].fadeTo(random(0,50),waitingTime);
    }
  }
  waitAndUpdate(waitingTime);
}

void hopscotch(){
  hopscotch(waitingTime());
}
void hopscotch(int waitingTime){
  // Serial.println("** Hopscotch method **");
  // Start condition
  led[1].fadeTo(0,waitingTime/10);
  led[2].fadeTo(0,waitingTime/10);

  led[0].fadeUp(waitingTime/5);
  led[3].fadeUp(waitingTime/5);
  waitAndUpdate(waitingTime/5);
  waitAndUpdate(waitingTime/5);
  led[0].fadeDown(waitingTime/5);
  led[3].fadeDown(waitingTime/5);
  waitAndUpdate(waitingTime/10);
  
  led[1].fadeUp(waitingTime/5);
  led[2].fadeUp(waitingTime/5);
  waitAndUpdate(waitingTime/5);
  waitAndUpdate(waitingTime/5);
  led[1].fadeDown(waitingTime/5);
  led[2].fadeDown(waitingTime/5);
  waitAndUpdate(waitingTime/10);

}

void crossover(){
  crossover(waitingTime());
}
void crossover(int waitingTime){
  led[1].fadeTo(0,waitingTime/10);
  led[3].fadeTo(0,waitingTime/10);
  
  led[0].fadeTo(255,waitingTime/5);
  led[2].fadeTo(255,waitingTime/5);
  waitAndUpdate(waitingTime/5);
  waitAndUpdate(waitingTime/5);
  led[0].fadeTo(0,waitingTime/5);
  led[2].fadeDown(waitingTime/5);
  waitAndUpdate(waitingTime/10);

  led[1].fadeUp(waitingTime/5);
  led[3].fadeUp(waitingTime/5);
  waitAndUpdate(waitingTime/5);
  waitAndUpdate(waitingTime/5);
  led[1].fadeTo(0,waitingTime/5);
  led[3].fadeDown(waitingTime/5);
  waitAndUpdate(waitingTime/10);
}

void trickleDown(){
  trickleDown(waitingTime());
}
void trickleDown(int waitingTime){
//  Serial.println("** Trickledown mode **");
  led[1].fadeTo(0,waitingTime/8);
  led[2].fadeTo(0,waitingTime/8);
  led[3].fadeTo(0,waitingTime/8);

  led[0].fadeTo(255,waitingTime/4);
  waitAndUpdate(waitingTime/4);
  led[0].fadeTo(0,waitingTime/4);
  led[1].fadeTo(255,waitingTime/4);
  waitAndUpdate(waitingTime/4);
  led[1].fadeTo(0,waitingTime/4);
  led[2].fadeTo(255,waitingTime/4);
  waitAndUpdate(waitingTime/4);
  led[2].fadeTo(0,waitingTime/4);
  led[3].fadeTo(255,waitingTime/4);
  waitAndUpdate(waitingTime/4); 
  led[3].fadeTo(0,waitingTime/4); 
}

void trickleUp(){
  trickleUp(waitingTime());
}
void trickleUp(int waitingTime){
//  Serial.println("** Trickle up mode **");
  led[0].fadeTo(0,waitingTime/8);
  led[1].fadeTo(0,waitingTime/8);
  led[2].fadeTo(0,waitingTime/8);

  led[3].fadeTo(255,waitingTime/4);
  waitAndUpdate(waitingTime/4);
  led[3].fadeTo(0,waitingTime/4);
  led[2].fadeTo(255,waitingTime/4);
  waitAndUpdate(waitingTime/4);
  led[2].fadeTo(0,waitingTime/4);
  led[1].fadeTo(255,waitingTime/4);
  waitAndUpdate(waitingTime/4);
  led[1].fadeTo(0,waitingTime/4);
  led[0].fadeTo(255,waitingTime/4);
  waitAndUpdate(waitingTime/4); 
  led[0].fadeTo(0,waitingTime/4); 
}

const int waitingTime(){
  return random(3000,15000);
}

modus switchMode(modus _currentMode){
  if(random(100)<65){
    return _currentMode;
  }
  switch(random(6)){
    case 0: return AQUA; break;
    case 1: return HOPSCOTCH; break;
    case 2: return CROSSOVER; break;
    case 3: return TRICKLE_DOWN; break;
    case 4: return TRICKLE_UP; break;
    default: Serial.println("New random mode not known, returning AQUA"); return AQUA; break;
  }
}

void executeMode(modus _mode){
  switch(_mode){
    case 0: aqua(); aqua(); break;
    case 1: hopscotch(); break;
    case 2: crossover(); break;
    case 3: trickleDown(); break;
    case 4: trickleUp(); break;
    default: Serial.print("Mode not known "); Serial.print(_mode); aqua(); break;
  }
}

void testAllModes(){
  aqua();
  aqua();
  hopscotch();
  hopscotch();
  hopscotch();
  
  aqua();
  aqua();
  crossover();
  crossover();
  crossover();
    
  aqua();
  aqua();
  trickleDown();
  trickleDown();
  trickleDown();

  aqua();
  aqua();
  trickleUp();
  trickleUp();
  trickleUp();
}

modus currentMode = AQUA;
unsigned long loopCounter=0;
void loop(){
//  loopCounter++;
//  Serial.print("\n\n*** Loop start ");
//  Serial.print(loopCounter);
//  Serial.print(" ***\n");
  executeMode(currentMode);
  currentMode = switchMode(currentMode);
}
