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

void printLedStatus(ledStatus _status){
  switch(_status){
    case OFF: Serial.print("OFF"); break;
    case FADING: Serial.print("FADING"); break;
    case ON: Serial.print("ON"); break;
    case CONST: Serial.print("CONST"); break;
    default: Serial.print("UNKOWN STATUS"); break;
  }
}

class LED {
  private:
    const unsigned short pin;
    ledStatus internStatus = OFF;
    unsigned short currentBrightness = 0;
    unsigned long fadeStart;
    unsigned short fadeStartBrightness = 0;
    unsigned long fadeTime = 0;
    unsigned short fadeGoalBrightness = 0;
    LED();
  public:
    LED(unsigned short _pin); // TODO: Should be a singelton per pin
    
    // Getter and setter
    
    const unsigned short getPin();

    void setStatus(ledStatus _newStatus, unsigned long _fadeTime, unsigned short _goalBrightness);
    ledStatus getStatus();
    
    void setBrightness(int _brightness);
    unsigned short getBrightness();

    void setFadeStart();
    unsigned long getFadeStart();

    void setFadeStartBrightness(int _brightness);
    unsigned short getFadeStartBrightness();

    void setFadeTime(unsigned long _fadeTime);
    unsigned long getFadeTime();

    void setFadeGoalBrightness(int _brightness);
    unsigned short getFadeGoalBrightness();

    // Status Methods
    void on();
    void off();
    void fadeUp(unsigned long fadeTime);
    void fadeDown(unsigned long fadeTime);
    void fadeTo(int _fadeGoalBrightness, unsigned long _fadeTime);
    void constant(short _brightness);

    unsigned short brightnessCheck(int _brightness);
    void updateLed();
};

LED::LED(const unsigned short _pin) : pin(_pin)
{
  ledDefined[_pin]=true;
  pinMode(_pin,OUTPUT);
};

// Getter and setter
const unsigned short LED::getPin(){
  return pin;
}

void LED::setStatus(ledStatus _newStatus, unsigned long _fadeTime, unsigned short _goalBrightness){
  internStatus = _newStatus;
  //Serial.print("LED at pin nr ");Serial.print(pin);Serial.print(" is now ");printLedStatus(_newStatus);Serial.println("!");
  switch(_newStatus) {
    case CONST: setBrightness(_goalBrightness); analogWrite(this->getPin(),getBrightness()); break;
    case ON: setBrightness(255); analogWrite(this->getPin(),getBrightness()); break;
    case OFF: setBrightness(0); analogWrite(this->getPin(),getBrightness()); break;
    case FADING: 
      setFadeTime(_fadeTime);
      setFadeGoalBrightness(brightnessCheck(_goalBrightness));
      setFadeStart();
      //Serial.print("\t\tfrom "); Serial.print(getBrightness());
      //Serial.print(" to "); Serial.print(getFadeGoalBrightness());
      //Serial.print(" in "); Serial.print(getFadeTime()); Serial.println(" ms");
      break;
    default: Serial.println("Master! I dont know how to handle this status!!!"); break;
  }
}

ledStatus LED::getStatus(){
  return internStatus;
}

void LED::setBrightness(int _brightness){
  /*
  Serial.print("DEBUG: Setting brightness of ");
  Serial.print(pin);
  Serial.print(" to ");
  Serial.println(_brightness);
  */
  this->currentBrightness = brightnessCheck(_brightness);
}

unsigned short LED::getBrightness(){
  return currentBrightness;
}

void LED::setFadeGoalBrightness(int _brightness){
  this->fadeGoalBrightness = brightnessCheck(_brightness);
}

unsigned short LED::getFadeGoalBrightness(){
  return this->fadeGoalBrightness;
}

void LED::setFadeStart(){
  fadeStart = millis();
}

unsigned long LED::getFadeStart(){
  return fadeStart;
}

void LED::setFadeStartBrightness(int _brightness){
  fadeStartBrightness = brightnessCheck(_brightness);
}

unsigned short LED::getFadeStartBrightness(){
  return fadeStartBrightness;
}

void LED::setFadeTime(unsigned long _fadeTime){
  if(_fadeTime>100000){
    Serial.print("WARN: Really long fade time detected: ");
    Serial.println(_fadeTime);
  }
  fadeTime = _fadeTime;    
}

unsigned long LED::getFadeTime(){
  return fadeTime;
}

void LED::constant(short _brightness){
  if(_brightness>=255){
    if(_brightness>255){
      Serial.print("WARN: requested const brightness overflow! brightness = ");
      Serial.println(_brightness);
    }
    this->on();
    return;
  }
  else if(_brightness<=0){
    if(_brightness<0){
      Serial.print("WARN: requested const brightness underflow! brightness = ");
      Serial.println(_brightness);
    }
    this->off();
    return;
  }
  setStatus(CONST,0,_brightness);
}

void LED::on(){ 
  setStatus(ON,0,255);
};

void LED::off(){
  setStatus(OFF,0,0);
};

void LED::fadeUp(unsigned long _fadeTime){
  this->setBrightness(0);
  fadeTo(255,_fadeTime);
};

void LED::fadeDown(unsigned long _fadeTime){
  this->setBrightness(255);
  fadeTo(0,_fadeTime);
}

void LED::fadeTo(int _fadeGoalBrightness, unsigned long _fadeTime){
  this->setFadeGoalBrightness(brightnessCheck(_fadeGoalBrightness));
  this->setFadeStartBrightness(this->getBrightness());
  this->setFadeTime(_fadeTime);
  this->setFadeStart();
  setStatus(FADING,getFadeTime(),getFadeGoalBrightness());
}

unsigned short LED::brightnessCheck(int _brightness){
  if(_brightness>255) {
    Serial.print("WARN: pin nr ");
    Serial.print(pin);
    Serial.print(" brightness overflow! brightness = ");
    Serial.println(_brightness);
    _brightness = 255;  
    }
  else if(_brightness<0) {
    Serial.print("WARN: pin nr ");
    Serial.print(pin);
    Serial.print(" brightness underflow! brightness = ");
    Serial.println(_brightness);
    _brightness = 0;
  }
  return _brightness;
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
      brightness = getFadeStartBrightness() + ((millis()-getFadeStart())/(double) getFadeTime())* ((int) getFadeGoalBrightness()- (int) getFadeStartBrightness());
      /* Poor mans debugger */
      /*
      Serial.print("pin ");Serial.print(pin); Serial.print("\t");
      Serial.print("Brightness ");Serial.print(brightness); Serial.print("\t");
      Serial.print("Time past ");Serial.print(millis()-getFadeStart());Serial.print("\t");
      Serial.print("fadeStartBrightness ");Serial.print(fadeStartBrightness); Serial.print("\t");
      Serial.print("fadeStart ");Serial.print(getFadeStart()); Serial.print("\t");
      Serial.print("fadeTime ");Serial.print(getFadeTime()); Serial.print("\t");
      Serial.print("fadeGoalBrightness ");Serial.print(fadeGoalBrightness); Serial.print("\t");
      Serial.println();
      */
      
      if(getFadeGoalBrightness()>=getFadeStartBrightness()){
        if(brightness>=getFadeGoalBrightness()){
          this->constant(getFadeGoalBrightness());
          break;
        }
      }
      else {
        if(brightness<=(int) getFadeGoalBrightness()){
          this->constant(getFadeGoalBrightness());
          break;
        }
      }
      
          
      setBrightness(brightness);
      analogWrite(getPin(),getBrightness());
      break;
    default: break;
  }
}

#endif
