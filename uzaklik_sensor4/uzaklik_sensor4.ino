/*
   created by Rui Santos, https://randomnerdtutorials.com

   Complete Guide for Ultrasonic Sensor HC-SR04

    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
*/

int trigPin4 = 8;    // Trig 4
int echoPin4 = 9;    // Echo 4
int trigPin3 = 7;    // Trig 3
int echoPin3 = 6;    // Echo 3
int trigPin2 = 5;    // Trig 2
int echoPin2 = 4;    // Echo 2
int trigPin1 = 3;    // Trig 1
int echoPin1 = 2;    // Echo 1


long duration1, cm1, duration2, cm2, duration3, cm3, duration4, cm4;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
}

void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin1, HIGH);
  digitalWrite(trigPin2, HIGH);
  digitalWrite(trigPin3, HIGH);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);
  digitalWrite(trigPin4, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  duration3 = pulseIn(echoPin3, HIGH);
  duration4 = pulseIn(echoPin4, HIGH);

  // Convert the time into a distance
  cm1 = (duration1 / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  cm2 = (duration2 / 2) / 29.1;
  cm3 = (duration3 / 2) / 29.1;
  cm4 = (duration4 / 2) / 29.1;

  Serial.print(cm1);
  Serial.print("cm1");
  Serial.println();

  Serial.print(cm2);
  Serial.print("cm2");
  Serial.println();

  Serial.print(cm3);
  Serial.print("cm3");
  Serial.println();

  Serial.print(cm4);
  Serial.print("cm4");
  Serial.println();




  delay(250);
  if (cm1 <= 20)
    Serial.println("Sağa uzaklık 20cm'den kucuk");
  if (cm2 <= 20)
    Serial.println("Arkaya uzaklık 20cm'den kucuk");
  if (cm3 <= 20)
    Serial.println("Sola uzaklik 20cm'den kucuk");
  if (cm4 <= 20)
    Serial.println("Öne uzaklik 20cm'den kucuk");
















}
