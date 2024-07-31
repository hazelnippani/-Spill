#include <SoftwareSerial.h>
#include <Servo.h>;

SoftwareSerial Bluetooth(3,2); // TX, RX

const int servoPin = 4;
const int buzzPin = 6;
Servo servo;
int counter = 0;
bool sensedM = false;
const int sensorJ = 9;
bool buzzed = false;
bool buzzedJ = false;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooth.begin(38400);
  servo.attach (servoPin);
  pinMode(servoPin,OUTPUT);
  servo.write (0);
  pinMode(buzzPin,OUTPUT);
  pinMode(sensorJ,INPUT);

}

void loop() {
  int liquidL = digitalRead(sensorJ);
  if (Bluetooth.available())
    Serial.write(Bluetooth.read());

  if (Bluetooth.read() == 'a')
  {
    counter++;
    sensedM = true;
    delay(400);
  }
  if (Bluetooth.read() == 'b')
  {
    counter++;
    sensedM = false;
    delay(400);
  }
  if(sensedM){
    if(counter >= 1)
      servo.write (125); // 180 degrees, doesn't acc = 180 for some reason like girl what
      if(!buzzed){
        tone(buzzPin, 1000);
        delay(500);
        noTone(buzzPin);
        buzzed = true;
      }
    counter = 0;
  }
  else{
    if(counter >= 1)
      servo.write (0); // 0 degrees
    noTone(buzzPin);
    buzzed = false;
    counter = 0;
  }
  //Jug sensor:
  if (liquidL >= 1 && !buzzedJ)
  {
    tone(buzzPin, 1000);
    delay(500);
    noTone(buzzPin);
    buzzedJ = true;
    liquidL = 0;
  }
  else if(liquidL < 1) {
      buzzedJ = false;
  }
}
