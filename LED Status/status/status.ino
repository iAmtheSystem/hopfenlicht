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
    int fadeTime = 0;
    unsigned long fadeStart;
    int ledBrightness = 0;
  public:
    LED(int _pin);
    void on();
    void off();
    void fadeUp(int fadeTime);
    void fadeDown(int fadeTime);
    void setLedStatus(ledStatus _newStatus);
    ledStatus getLedStatus();
    void setBrightness(int _brightness);
    int getBrightness();
    int getPin();
    unsigned long getFadeStart();
    void setFadeStart();
    int getFadeTime();
};

const int NR_OF_LEDS = 4;
LED led[] = {
  LED(11),
  LED(10),
  LED(9),
  LED(6)
};
/*
LED LED1 = LED(11);
LED LED2 = LED(10);
LED LED3 = LED(9);
LED LED4 = LED(6);

LED leds[]= {
*/

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
  Serial.print("\nLED Nr ");
  Serial.print(pinNumber);
  Serial.print(" is now ON!");
  ledBrightness = 255;
  setLedStatus(ON);
};

void LED::off()
{
  Serial.print("\nLED Nr ");
  Serial.print(pinNumber);
  Serial.print(" is now OFF!");
  ledBrightness = 0;
  setLedStatus(OFF);
};

void LED::fadeUp(int _fadeTime){
  Serial.print("\nLED Nr ");
  Serial.print(pinNumber);
  Serial.print(" is now fading UP for ");
  Serial.print(fadeTime);
  Serial.print(" ms");
  setBrightness(0);
  fadeTime = _fadeTime;
  fadeStart = millis();
  internLedStatus=FADE_UP;
};

void LED::fadeDown(int _fadeTime){
  Serial.print("\nLED Nr ");
  Serial.print(pinNumber);
  Serial.print(" is now fading DOWN for ");
  Serial.print(fadeTime);
  Serial.print(" ms");
  setBrightness(255);
  fadeTime = _fadeTime;
  fadeStart = millis();
  internLedStatus=FADE_DOWN;
}

unsigned long LED::getFadeStart(){
  return fadeStart;
}

void LED::setFadeStart(){
  fadeStart = millis();
}

int LED::getFadeTime(){
  return fadeTime;
}


void updateLed(LED *led){
  int brightness;
  if(led.getLedStatus() == FADE_UP){
    brightness = (millis()-led.getFadeStart())/led.getFadeTime()*255;
    if (brightness>255) {
      led.on();
      brightness = 255; // dont want anything over 255;
    }
    led.setBrightness(brightness);
  }
  if(led.getLedStatus() == FADE_DOWN){
    brightness = 255-(millis()-led.getFadeStart())/led.getFadeTime()*255;
    if (brightness<0) {
      led.off();
      brightness = 0; // dont want anything under 0;
    }
    led.setBrightness(brightness);
  }
  analogWrite(led.getPin(),led.getBrightness());
}

void updateLeds(){
  for(int i=0;i<NR_OF_LEDS;i++){
    updateLed(led[i]);
  }
}

void waitAndUpdate(int waitTimeMs){
  while(waitTimeMs>0){
    updateLeds();
    delay(8);
    waitTimeMs -= 10; // best guess that updateLeds() needs 2 ms, could be made much nicer when triggered by a real clock -> import time ??
  }
}

// Setting up the system
void setup() {
  Serial.begin(9600); // to communicate with the PC
  Serial.print("*** Welcome Master Carina! I am here to serve you!***\n");
}

unsigned long loopCounter=0;
void loop(){
  loopCounter++;
  Serial.print("\n*** Loop start ");
  Serial.print(loopCounter);
  Serial.print(" ***\n");
  led[0].on();
  led[1].off();
  led[2].fadeDown(2550);
  led[3].fadeUp(10000);
  waitAndUpdate(5000);
  led[0].off();
  led[1].fadeUp(1000);
  led[2].fadeDown(500);
  led[3].fadeDown(10000);
  waitAndUpdate(10000);
}
