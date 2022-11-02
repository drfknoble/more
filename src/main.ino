/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
int dirPinLeft = 2;
int stepPinLeft = 3;
int dirPinRight = 4;
int stepPinRight = 5;
int stepsPerRevolution = 200;

int statusLED1 = 6;
int statusLED2 = 7;
int sensorFront = 9;
float frontDuration = 0.0;
float frontDistance = 5000.00;

bool completed = false;

void forward(float distance = 250.0) {

//  int count = 5;
//  float sum = 0.0;
//
//  for (int i = 0; i < count; i++) {
// 
//    sum += frontSensor();
//
//  }
//
//  frontDistance = (sum / count);
//
//  if (frontDistance < distance) {
//    return;
//  }
//    
  
  digitalWrite(dirPinLeft, LOW);
  digitalWrite(dirPinRight, LOW);

  float steps = distance / 377.0 * stepsPerRevolution;
 
  for (int i = 0; i < int(steps); i++) {    
    digitalWrite(stepPinLeft, HIGH);
    digitalWrite(stepPinRight, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPinLeft, LOW);
    digitalWrite(stepPinRight, LOW);
    delayMicroseconds(5000);
  }

  return;
}

void backward(float distance = 250.0) {
  digitalWrite(dirPinLeft, HIGH);
  digitalWrite(dirPinRight, HIGH);

  float steps = distance / 377.0 * stepsPerRevolution;

  for (int i = 0; i < int(steps); i++) {     
    digitalWrite(stepPinLeft, HIGH);
    digitalWrite(stepPinRight, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPinLeft, LOW);
    digitalWrite(stepPinRight, LOW);
    delayMicroseconds(5000);
  }

  return;
}

void right(float angle = 90) {
  digitalWrite(dirPinLeft, HIGH);
  digitalWrite(dirPinRight, LOW);

  float steps = angle * 3.14159 / 180.0 * 135.0 / 377.0 * stepsPerRevolution;

  for (int i = 0; i < int(steps); i++) {
    digitalWrite(stepPinLeft, HIGH);
    digitalWrite(stepPinRight, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPinLeft, LOW);
    digitalWrite(stepPinRight, LOW);
    delayMicroseconds(5000);
  }

  return;
}

void left(float angle = 90) {
  digitalWrite(dirPinLeft, LOW);
  digitalWrite(dirPinRight, HIGH);

  float steps = angle * 3.14159 / 180.0 * 135.0 / 377.0 * stepsPerRevolution;

  for (int i = 0; i < int(steps); i++) {
    digitalWrite(stepPinLeft, HIGH);
    digitalWrite(stepPinRight, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPinLeft, LOW);
    digitalWrite(stepPinRight, LOW);
    delayMicroseconds(5000);
  }

  return;
}

float frontSensor() {
  float duration = 0.0;
  float distance = 0.0;
  
  pinMode(sensorFront, OUTPUT);
  digitalWrite(sensorFront, LOW);
  delayMicroseconds(2);
  
  digitalWrite(sensorFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorFront, LOW);
  
  pinMode(sensorFront, INPUT);
  duration = pulseIn(sensorFront, HIGH);
  
//  distance = duration * 0.034 / 2; //cm
  distance = 10 * duration * 0.034 / 2; //mm
  
  return distance;
}

void setup() {
  // Declare pins as output:
  pinMode(stepPinLeft, OUTPUT);
  pinMode(dirPinLeft, OUTPUT);
  pinMode(stepPinRight, OUTPUT);
  pinMode(dirPinRight, OUTPUT);

  pinMode(statusLED1, OUTPUT);  
  pinMode(statusLED2, OUTPUT);
  pinMode(sensorFront, OUTPUT);

  digitalWrite(statusLED1, LOW);
  digitalWrite(statusLED2, LOW);
  digitalWrite(sensorFront, LOW);

  Serial.begin(115200);
}

void loop() {

  if (completed == false) {
  
    for (int i = 0; i < 3; i++) {
      forward(1000);
      delay(250);
      left();
      delay(250);
      forward(1000);
      delay(250);
      right();
      delay(250);
    }
  
    completed = true;

  }
    
  int count = 5;
  float sum = 0.0;

  for (int i = 0; i < count; i++) {
 
    sum += frontSensor();

  }

  frontDistance = (sum / count);

  Serial.print("front sensor distance = ");
  Serial.print(frontDistance);
  Serial.println(" mm");

  if (frontDistance <= 500) {
    digitalWrite(statusLED1, HIGH);
    digitalWrite(statusLED2, HIGH);
  } else {
    digitalWrite(statusLED1, LOW);
    digitalWrite(statusLED2, LOW);
  }
}
