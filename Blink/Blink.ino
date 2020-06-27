const int LED1 = 11;
const int LED2 = 10;
const int LED3 = 9;
const int LED4 = 6;
const int SPEEDFAKTOR = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(9600);
}

void digitalWrite4(int pin1, int pin2, int pin3, int pin4, int value){
    digitalWrite(pin1,value);
    digitalWrite(pin2,value);
    digitalWrite(pin3,value);
    digitalWrite(pin4,value);
}

void yumba(int numberOfYumbas, int durationOn, int DurationOff){
  // tbd
}

void blinkAll(int led1, int led2, int led3, int led4, int durationOn, int durationOff, int numberOfBlinks){
  while(0<numberOfBlinks){
    digitalWrite4(led1,led2,led3,led4,HIGH);
    delay((int) durationOn/SPEEDFAKTOR);
    digitalWrite4(led1,led2,led3,led4,LOW);
    delay((int) durationOff/SPEEDFAKTOR);
    numberOfBlinks = numberOfBlinks-1;
  }
}

void trickledownandupSimple(){
  Serial.write("Lets do a trickledownandupSimple!\n");
  blinkAll(LED1,LED1,LED1,LED1,3000,500,1);
  blinkAll(LED2,LED2,LED2,LED2,3000,500,1);
  blinkAll(LED3,LED3,LED3,LED3,3000,500,1);
  blinkAll(LED4,LED4,LED4,LED4,3000,500,1);
  blinkAll(LED3,LED3,LED3,LED3,3000,500,1);
  blinkAll(LED2,LED2,LED2,LED2,3000,500,1);
}

void crossoverSimple(){
  Serial.write("Lets do a crossoverSimple!\n");
  blinkAll(LED1,LED1,LED3,LED3,3000,500,1);
  blinkAll(LED2,LED2,LED4,LED4,3000,500,1);
  blinkAll(LED1,LED1,LED3,LED3,3000,500,1);
  blinkAll(LED2,LED2,LED4,LED4,3000,500,1);
}

void hopscotchSimple(){
  Serial.write("Lets do a hopscotchSimple!\n");
  blinkAll(LED1,LED1,LED4,LED4,3000,500,1);
  blinkAll(LED2,LED2,LED3,LED3,3000,500,1);
  blinkAll(LED1,LED1,LED4,LED4,3000,500,1);
  blinkAll(LED2,LED2,LED3,LED3,3000,500,1);
}


// the loop function runs over and over again forever
void loop() {
  Serial.write("Hello master Carina! Lets looooop!\n");
  
  trickledownandupSimple();
  trickledownandupSimple();
  trickledownandupSimple();
  trickledownandupSimple();
  blinkAll(LED1,LED1,LED1,LED1,3000,500,1);

  blinkAll(LED1,LED2,LED3,LED4,5000,500,5);

  crossoverSimple();
  crossoverSimple();

  blinkAll(LED1,LED2,LED3,LED4,5000,500,5);
  
  hopscotchSimple();
  hopscotchSimple();
  
  blinkAll(LED1,LED2,LED3,LED4,5000,500,5);

  
}
