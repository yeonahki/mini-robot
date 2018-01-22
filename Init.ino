#include <EEPROM.h>
#include <Servo.h>

Servo servo[4];
int servoPin[4] = {3, 5, 6, 10};
int alpha[4] = {0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for (int i = 0; i < 4; i++)
  {
    servo[i].attach(servoPin[i]);
    servo[i].write(alpha[i] + 90);
    //EEPROM.write(i, alpha[i] + 90);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
