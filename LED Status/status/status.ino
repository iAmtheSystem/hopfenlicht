const int SPEEDFAKTOR = 1;

enum ledStatus {
  OFF,
  FADE_UP,
  ON,
  FADE_DOWN
};

class LED {
  private:
    ledStatus internLedStatus = OFF;
    int pinNumber;
    unsigned long fadeTime = 0;
    unsigned long fadeStart;
    int ledBrightness = 0;
  public:
    LED(int _pin);
    void on();
    void off();
    void fadeUp(unsigned long fadeTime);
    void fadeDown(unsigned long fadeTime);
    
    void setLedStatus(ledStatus _newStatus);
    ledStatus getLedStatus();
    void setBrightness(int _brightness);
    int getBrightness();
    int getPin();
    unsigned long getFadeStart();
    void setFadeStart();
    unsigned long getFadeTime();
};

const int NR_OF_LEDS = 4;
LED led[] = {
  LED(11),
  LED(10),
  LED(9),
  LED(6)
};

LED::LED(int _pin)
{
  this->pinNumber = _pin;
  pinMode(_pin,OUTPUT);
};

void LED::setLedStatus(ledStatus _newStatus){
  internLedStatus = _newStatus;
}

ledStatus LED::getLedStatus(){
  return internLedStatus;
}

void LED::setBrightness(int _brightness){
  this->ledBrightness = _brightness;
}

int LED::getBrightness(){
  return ledBrightness;
}

int LED::getPin(){
  return pinNumber;
}

void LED::on()
{ 
  Serial.print("LED Nr ");
  Serial.print(pinNumber);
  Serial.print(" is now ON!\n");
  ledBrightness = 255;
  setLedStatus(ON);
};

void LED::off()
{
  Serial.print("LED Nr ");
  Serial.print(pinNumber);
  Serial.print(" is now OFF!\n");
  ledBrightness = 0;
  setLedStatus(OFF);
};

void LED::fadeUp(unsigned long _fadeTime){
  setBrightness(0);
  fadeTime = _fadeTime;
  fadeStart = millis();
  internLedStatus=FADE_UP;

  Serial.print("LED Nr ");
  Serial.print(pinNumber);
  Serial.print(" is now fading UP for ");
  Serial.print(getFadeTime());
  Serial.print(" ms\n");
};

void LED::fadeDown(unsigned long _fadeTime){
  setBrightness(255);
  fadeTime = _fadeTime;
  fadeStart = millis();
  internLedStatus=FADE_DOWN;

  Serial.print("LED Nr ");
  Serial.print(pinNumber);
  Serial.print(" is now fading DOWN for ");
  Serial.print(getFadeTime());
  Serial.print(" ms\n");
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
