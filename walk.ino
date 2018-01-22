#include <Servo.h>
#include <EEPROM.h>

// 초음파 센서
#define DISTANCE_MAX 200
#define DISTANCE_MIN 1

#define TRIG_PIN 8
#define ECHO_PIN 9

// 서보모터
#define FOOT_L 3
#define FOOT_R 5
#define LEG_L 6
#define LEG_R 10

Servo servo[4];
int servoPin[4] = {FOOT_L, FOOT_R, LEG_L, LEG_R};
int alpha[4] = {0, 0, 0, 0};

long getDistance()
{
  long distance;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  distance = (pulseIn(ECHO_PIN, HIGH) / 29) / 2;

  if(distance > DISTANCE_MAX || distance < DISTANCE_MIN)
  {
    distance = 0;
  }
  return distance;
}

void setServo(int n, int pos)
{
  int angle;
  int start = servo[n].read();
  
  pos += 90;
  pos += alpha[n];

  if (start < pos)
  {
    for (angle = start; angle < pos; angle++)
    {
      servo[n].write(angle);
      delay(5);
    }
  }
  else if (start > pos)
  {
    for (angle = start; angle > pos; angle--)
    {
      servo[n].write(angle);
      delay(5);
    }
  }
}

void forward()
{
  setServo(1, -40);
  setServo(0, -20);
  setServo(2, 20);
  setServo(3, 20);
  setServo(0, 0);
  setServo(1, 0);

  setServo(0, 40);
  setServo(1, 20);
  setServo(3, -20);
  setServo(2, -20);
  setServo(1, 0);
  setServo(0, 0);
}

void backward()
{
  setServo(1, -40);
  setServo(0, -20);
  setServo(2, -20);
  setServo(3, -20);
  setServo(0, 0);
  setServo(1, 0);

  setServo(0, 40);
  setServo(1, 20);
  setServo(3, 20);
  setServo(2, 20);
  setServo(1, 0);
  setServo(0, 0);
}

void left()
{
  setServo(1, -40);
  setServo(0, -20);
  setServo(3, 20);
  setServo(2, 20);
  setServo(1, 0);
  setServo(0, 0);
  setServo(2, -20);
  setServo(3, -20);
}

void right()
{
  setServo(0, 40);
  setServo(1, 20);
  setServo(2, -20);
  setServo(3, -20);
  setServo(0, 0);
  setServo(1, 0);
  setServo(3, 20);
  setServo(2, 20);
}

void stop()
{
  setServo(0, 0);
  setServo(1, 0);
  setServo(2, 0);
  setServo(3, 0);
}
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // 초음파 센서 초기화
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // 서보모터 초기화
  for (int i = 0; i < 4; i++)
  {
    servo[i].attach(servoPin[i]);
    alpha[i] = EEPROM.read(i) - 90;
    setServo(i, 0);
  }

  Serial.println("=== Servo motor Setting ===");
  Serial.print("Left foot(0): ");
  Serial.println(alpha[0]);
  Serial.print("Right foot(1): ");
  Serial.println(alpha[1]);
  Serial.print("Left Leg(2): ");
  Serial.println(alpha[2]);
  Serial.print("Right Leg(3): ");
  Serial.println(alpha[3]);
}

void loop() {
  // put your main code here, to run repeatedly:
  long Distance_cm = getDistance();
  Serial.print(Distance_cm);
  Serial.println(" cm"); 
  
  if (Distance_cm != 0 && Distance_cm < 10)
  {
    forward();
  }
  else
  {
    stop();  
  }
  delay(100);
}
