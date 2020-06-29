#ifndef LED_h
#define LED_h


static bool ledDefined[13] = {false,false,false,false,false,
                              false,false,false,false,false,
                              false,false,false};
                              
enum ledStatus {
  OFF,
  FADING,
  ON,
  CONST
};

class LED {
  private:
    const unsigned short pin;
    ledStatus internStatus = OFF;
    unsigned long fadeStart;
    unsigned long fadeTime = 0;
    unsigned short fadeGoalBrightness = 0;
    unsigned short fadeStartBrightness = 0;
    unsigned short currentBrightness = 0;
    LED();
  public:
    LED(unsigned short _pin); // TODO: Should be a singelton per pin
    
    void setStatus(ledStatus _newStatus, unsigned long _fadeTime, unsigned short _goalBrightness);
    ledStatus getStatus();
    
    void setBrightness(int _brightness);
    unsigned short getBrightness();
    
    const unsigned short getPin();

    void setFadeStart();
    unsigned long getFadeStart();
    
    unsigned long getFadeTime();

    // Status Methods
    void on();
    void off();
    void fadeUp(unsigned long fadeTime);
    void fadeDown(unsigned long fadeTime);
    void fadeTo(unsigned short _fadeGoalBrightness, unsigned long _fadeTime);
    void constant(short _brightness);
    
    void updateLed();
};

LED::LED(const unsigned short _pin) : pin(_pin)
{
  ledDefined[_pin]=true;
  pinMode(_pin,OUTPUT);
  Serial.print("Defined LEDs ");
  for(int i=0;i<13;i++){
    Serial.print(ledDefined[_pin]);
    Serial.print("\t");
  }
  Serial.println();
};

void LED::setStatus(ledStatus _newStatus, unsigned long _fadeTime, unsigned short _goalBrightness){
  internStatus = _newStatus;
  Serial.print("LED Nr ");
  Serial.print(pin);
  Serial.print(" is now ");
  Serial.println(_newStatus);
  switch(_newStatus) {
    case CONST: currentBrightness = _goalBrightness; analogWrite(this->getPin(),currentBrightness); break;
    case ON: currentBrightness = 0; analogWrite(this->getPin(),currentBrightness); break;
    case OFF: currentBrightness = 255; analogWrite(this->getPin(),currentBrightness); break;
    case FADING: 
      fadeTime = _fadeTime;
      fadeGoalBrightness = _goalBrightness;
      fadeStart = millis();
      Serial.print(" from "); Serial.print(currentBrightness);
      Serial.print(" to "); Serial.print(fadeGoalBrightness);
      Serial.print(" in "); Serial.print(fadeTime); Serial.println(" ms");
      break;
    default: Serial.println("Master! I dont know how to handle this status!!!"); break;
  }
}

ledStatus LED::getStatus(){
  return internStatus;
}

void LED::setBrightness(int _brightness){
  if(_brightness>255) {
    this->on();
    return;
  }
  else if(_brightness<0) {
    this->off();
    return;     
  }
  this->currentBrightness = _brightness;
}

unsigned short LED::getBrightness(){
  return currentBrightness;
}

const unsigned short LED::getPin(){
  return pin;
}

void LED::constant(short _brightness){
  setStatus(CONST,0,_brightness);
}

void LED::on(){ 
  setStatus(ON,0,255);
};

void LED::off(){
  setStatus(OFF,0,0);
};

void LED::fadeUp(unsigned long _fadeTime){
  setBrightness(0);
  fadeStart = millis();
  this->fadeTime = _fadeTime;
  setStatus(FADING,_fadeTime,255);
};

void LED::fadeDown(unsigned long _fadeTime){
  setBrightness(255);
  fadeStart = millis();
  this->fadeTime = _fadeTime;
  setStatus(FADING,_fadeTime,0);
}

void LED::fadeTo(unsigned short _fadeGoalBrightness, unsigned long _fadeTime){
  this->fadeGoalBrightness = _fadeGoalBrightness;
  this->fadeStartBrightness = this->getBrightness();
  this->fadeTime = _fadeTime;
  this->fadeStart = millis();
  setStatus(FADING,_fadeTime,_fadeGoalBrightness);
}

unsigned long LED::getFadeStart(){
  return fadeStart;
}

void LED::setFadeStart(){
  fadeStart = millis();
}

unsigned long LED::getFadeTime(){
  return fadeTime;
}

void LED::updateLed(){
  switch(this->getStatus()){
    case FADING:
      int brightness = 0;
      if(getFadeTime()<=0){
        Serial.print("Something went seriously wrong. The fadeTime is ");
        Serial.print(getFadeTime());
        Serial.print(" !?!?!?!?!?");
      }
      brightness = fadeStartBrightness + (double) (millis()-getFadeStart())/getFadeTime()*(fadeGoalBrightness-fadeStartBrightness);
      if(fadeGoalBrightness>=fadeStartBrightness){
        if(brightness>=fadeGoalBrightness){
          constant(fadeGoalBrightness);
          break;
        }
      }
      else if(brightness<=fadeGoalBrightness){
          constant(fadeGoalBrightness);
          break;
      }
      setBrightness(brightness);
      analogWrite(getPin(),getBrightness());
      break;
    default: break;
  }
}

#endif
