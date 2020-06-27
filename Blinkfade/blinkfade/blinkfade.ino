
const int LED1 = 11;
const int LED2 = 10;
const int LED3 = 9;
const int LED4 = 6;
const int SPEEDFAKTOR = 1;

// Setting up the system
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(9600); // to communicate with the PC
}

void allLights(int value){
  analogWrite(LED1, value);
  analogWrite(LED2, value);
  analogWrite(LED3, value);
  analogWrite(LED4, value);
}

void fadeAll(int led1, int led2, int led3, int led4, int fadeInTime, int durationOn, int fadeOutTime, int durationOff){
  // Speeed
  durationOn = durationOn/SPEEDFAKTOR;
  durationOff = durationOff/SPEEDFAKTOR;
  fadeInTime = fadeInTime/SPEEDFAKTOR;
  fadeOutTime = fadeOutTime/SPEEDFAKTOR;


  
  // printing
  Serial.print("\n*** Starting a fade ***\n");
  Serial.print("durationOn = ");
  Serial.print(durationOn);
  Serial.print("\tdurationOff = ");
  Serial.print(durationOff);
  Serial.print("\tfadeInTime = ");
  Serial.print(fadeInTime);
  Serial.print("\tfadeOutTime = ");
  Serial.print(fadeOutTime);
  Serial.print("\n");

  
  // start condition
  analogWrite(led1, 0);
  analogWrite(led2, 0);
  analogWrite(led3, 0);
  analogWrite(led4, 0);
  
  // fading on
  int fadeValue = 0;
  int fadeStep = 5;
  int timeUntilNextFadeStep = (int) fadeInTime*fadeStep/255;
  Serial.print("Fading all ");
  Serial.print(timeUntilNextFadeStep);
  Serial.print(" ms up\n");
  while(fadeValue <= 255){
    delay(timeUntilNextFadeStep);
    analogWrite(led1, fadeValue);
    analogWrite(led2, fadeValue);
    analogWrite(led3, fadeValue);
    analogWrite(led4, fadeValue);
    fadeValue += fadeStep;
  }

  // all lights are on
  analogWrite(led1, 255);
  analogWrite(led2, 255);
  analogWrite(led3, 255);
  analogWrite(led4, 255);
  
  delay(durationOn);

  // fading off
  // fading on
  fadeValue = 255;
  timeUntilNextFadeStep = (int) fadeOutTime*fadeStep/255;
  Serial.print("Fading all ");
  Serial.print(timeUntilNextFadeStep);
  Serial.print(" ms down\n");
  while(fadeValue >= 0){
    delay(timeUntilNextFadeStep);
    analogWrite(led1, fadeValue);
    analogWrite(led2, fadeValue);
    analogWrite(led3, fadeValue);
    analogWrite(led4, fadeValue);
    fadeValue -= fadeStep;
  }


  allLights(0);
  delay(durationOff);  
}

void trickledownandupFade(){
  Serial.write("Lets do a trickledownandupFade!\n");
  fadeAll(LED1,LED1,LED1,LED1,2000,3000,2000,500);
  fadeAll(LED2,LED2,LED2,LED2,2000,3000,2000,500);
  fadeAll(LED3,LED3,LED3,LED3,2000,3000,2000,500);
  fadeAll(LED4,LED4,LED4,LED4,2000,3000,2000,500);
  fadeAll(LED3,LED3,LED3,LED3,2000,3000,2000,500);
  fadeAll(LED2,LED2,LED2,LED2,2000,3000,2000,500);
}
void crossoverFade(){
  Serial.write("Lets do a crossoverFade!\n");
  fadeAll(LED1,LED1,LED3,LED3, 2000,3000,2000,500);
  fadeAll(LED2,LED2,LED4,LED4, 2000,3000,2000,500);

}

void hopscotchFade(){
  Serial.write("Lets do a hopscotchFade!\n");
  fadeAll(LED1,LED1,LED4,LED4, 2000,3000,2000,500);
  fadeAll(LED3,LED3,LED2,LED2, 2000,3000,2000,500);

  
}


// the loop routine runs over and over again forever:

void loop() {

trickledownandupFade();
trickledownandupFade();
trickledownandupFade();
trickledownandupFade();
trickledownandupFade();
fadeAll(LED1,LED1,LED1,LED1,2000,3000,2000,500);

fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);

crossoverFade();
crossoverFade();
crossoverFade();
crossoverFade();
crossoverFade();

fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);

hopscotchFade();
hopscotchFade();
hopscotchFade();
hopscotchFade();
hopscotchFade();

fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);
fadeAll(LED1,LED2,LED3,LED4,2000,5000,2000,500);

}
