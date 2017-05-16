#include <Servo.h>

Servo servoMotor;

int anguloCerrado = 20;
int anguloAbierto = 90;

int buttonPin = 7;
int buzzerPin = 8;
int servoPin = 9;
int ledPin = 10;

void setup() {
  servoMotor.attach(servoPin);
  cerrarCompuerta();
  pinMode(buttonPin,INPUT);
  pinMode(ledPin,OUTPUT);
  tone(buzzerPin, 0, 5);
  delay(5);
  noTone(buzzerPin);
  playReady();
  delay(10);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    abrirCompuerta();
    playCharge();
    playReady();
    delay(300);
    actionShot();
    delay(500);
    actionShot();
    delay(500);
    actionShot();
    delay(50);
    actionDisCharge();
    playNoAmmo();
    while(buttonState==HIGH){
      buttonState = digitalRead(buttonPin);
    }
  }
}

//-----------Servo-------------

void cerrarCompuerta(){
  servoMotor.write(anguloCerrado);
}

void abrirCompuerta(){
  servoMotor.write(anguloAbierto);
}


//-----------Buzzer-------------

void playTone(int atone, int duration) { // A sub routine for playing tones like the standard arduino melody example
  for (long i = 0; i < duration * 1000L; i += atone * 2) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(atone);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(atone);
  }
}

void playCharge(){
  for (int i = 1;i < 254;i++) {
    playTone((3000-9*i), 1);
  } 
}

void playDischarge(){
  for (int i = 1;i < 254;i++) {
      playTone((1000+9*i), 2);
  }
}

void playNoAmmo() {
  for (int i=0;i<3;i++){
    playTone(500, 100);
    playTone(1000, 100);
    delay(300);
  }
}

void playReady(){
  playTone(500, 500);
}

void playShot(){
  playTone(500, 50);
  for (int i = 1;i < 64;i++) {
      playTone((1000+9*i), 1);
  }
}


//-----------Acciones_Complejas------------

void actionDisCharge(){
  int pos=90;
  int j = 0;
  for (int i = 1;i < 254;i++) {
    playTone((1000+9*i), 2);
    j++;
    if (j==4){
      pos=pos-1;
      servoMotor.write(pos);
      j=0;
    }
  }
  servoMotor.write(20);
}

void actionShot(){
  digitalWrite(ledPin, HIGH);
  playShot();
  digitalWrite(ledPin, LOW);
}

