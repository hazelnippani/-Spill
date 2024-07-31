#include <SoftwareSerial.h>
//SLAVE = 14:3:50de6

SoftwareSerial Bluetooth(3,2); // TX, RX

const int sensorPin = 4;
int liquidLevel = 0;

// const int Button = 4;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooth.begin(38400);

  // pinMode(Button,INPUT);
  pinMode(sensorPin,INPUT); //sensor


}

void loop() {
  // put your main code here, to run repeatedly:
  liquidLevel = digitalRead(sensorPin);
  if (liquidLevel >= 1)
  {
    Bluetooth.write("a");
  }
  else if (liquidLevel == 0){
    Bluetooth.write("b");
  }
  delay(300);

}
