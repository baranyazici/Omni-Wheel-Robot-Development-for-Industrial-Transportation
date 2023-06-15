//Bilge Kaan Tekin & Ahmet Baran Yazıcı

#include <SoftwareSerial.h> //including the SoftwareSerial library for Bluetooth communication
#include <AccelStepper.h> //including the AccelStepper library 
//#include "NewPing.h"
SoftwareSerial Bluetooth(A8, 38); //(RX,TX)Arduino RX pin connected to HC05 TX pin
long duration,cm,distance_right1;


#define trig 5
#define echo 4
//#define TRIGPIN2 5
//#define ECHOPIN2 4
//#define TRIGPIN3 7
//#define ECHOPIN3 6
//#define TRIGPIN4 9
//#define ECHOPIN4 8
//
//#define MAX_DISTANCE 900
//
//NewPing right1(TRIGPIN1, ECHOPIN1, MAX_DISTANCE);
//NewPing back2(TRIGPIN2, ECHOPIN2, MAX_DISTANCE);
//NewPing left3(TRIGPIN3, ECHOPIN3, MAX_DISTANCE);
//NewPing front4(TRIGPIN4, ECHOPIN4, MAX_DISTANCE);

//float duration, distance_right1, distance_back2, distance_left3, distance_front4;
//bool isMoving = false;

//defining the stepper motors and related pins
AccelStepper left_front(1, 42, 43); //(type:driver, STEP, DIR) ->Stepper Motor 1
AccelStepper right_front(1, 40, 41); //->Stepper Motor 2
AccelStepper right_back(1, 44, 45); //->Stepper Motor 3
AccelStepper left_back(1, 46, 47); //->Stepper Motor 4

int wheel_speed = 800; //setting the wheel speed as integer
String data_in; //the string input coming from the Bluetooth

void setup() {
  //setting the maximum speeds of motors
  left_back.setMaxSpeed(1000);
  left_front.setMaxSpeed(1000);
  right_back.setMaxSpeed(1000);
  right_front.setMaxSpeed(1000);

  pinMode(TRIGPIN1, OUTPUT);
  pinMode(ECHOPIN1, INPUT);
  //necessary Baud rates for Bluetooth communication
  Serial.begin(9600);
  Bluetooth.begin(9600);

}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
  while (Bluetooth.available()) {       //checks if the Bluetooth is available


    data_in = Bluetooth.readString();   //the word written from the phone will be stored in the "data_in" string

    if (data_in == "w") {               //if we write "w" in our phone,
      go_forward();                     //code will run the "go_forward() function
      Serial.println(data_in);          //to check if the code working properly, we printed the data_in on the serial monitor
    }
    else if (data_in == "s") {          //if user writes "s" from phone's terminal monitor
      go_backward();                    //code will run the "go_backward()" function
      Serial.println(data_in);
    }
    else if (data_in == "d") {
      go_sideways_right();
      Serial.println(data_in);
    }
    else if (data_in == "a") {
      go_sideways_left();
      Serial.println(data_in);
    }
    else if (data_in == "e") {
      rotate_right();
      Serial.println(data_in);
    }
    else if (data_in == "q") {
      rotate_left();
      Serial.println(data_in);
    }
    else if (data_in == "wd") {
      go_right_forward();
      Serial.println(data_in);
    }
    else if (data_in == "sd") {
      go_right_backward();
      Serial.println(data_in);
    }
    else if (data_in == "wa") {
      go_left_forward();
      Serial.println(data_in);
    }
    else if (data_in == "sa") {
      go_left_backward();
      Serial.println(data_in);
    }
    else if (data_in == "p") {
      stop_moving();
      Serial.println(data_in);
    }
  }





  left_front.runSpeed();    //after deciding which function to be called
  left_back.runSpeed();     //we set the .runSpeed() function of the library
  right_back.runSpeed();    //that allows us to run the motors according to the given speed afterwards
  right_front.runSpeed();
}

void go_forward() {                     //the void function for go forward

  if (distance_right1 > 5) {
    left_front.setSpeed(-wheel_speed);    //we set the necessary directions for each wheel
    left_back.setSpeed(-wheel_speed);     //in order to move the robot to the forward
    right_back.setSpeed(wheel_speed);     //(-) signs in front of the speed is for the direction
    right_front.setSpeed(wheel_speed);    //and for the speed, its using the int wheel_speed that is written before
  }
  else {
    left_front.setSpeed(0);
    left_back.setSpeed(0);
    right_back.setSpeed(0);
    right_front.setSpeed(0);
  }
}

void go_backward() {
  left_front.setSpeed(wheel_speed);
  left_back.setSpeed(wheel_speed);
  right_back.setSpeed(-wheel_speed);
  right_front.setSpeed(-wheel_speed);
}

void go_sideways_right() {
  left_front.setSpeed(-wheel_speed);
  left_back.setSpeed(wheel_speed);
  right_back.setSpeed(wheel_speed);
  right_front.setSpeed(-wheel_speed);
}

void go_sideways_left() {
  left_front.setSpeed(wheel_speed);
  left_back.setSpeed(-wheel_speed);
  right_back.setSpeed(-wheel_speed);
  right_front.setSpeed(wheel_speed);
}

void rotate_right() {
  left_front.setSpeed(-wheel_speed);
  left_back.setSpeed(-wheel_speed);
  right_back.setSpeed(-wheel_speed);
  right_front.setSpeed(-wheel_speed);

}

void rotate_left() {
  left_front.setSpeed(wheel_speed);
  left_back.setSpeed(wheel_speed);
  right_back.setSpeed(wheel_speed);
  right_front.setSpeed(wheel_speed);
}

void go_right_forward() {
  left_front.setSpeed(-wheel_speed);
  left_back.setSpeed(0);
  right_back.setSpeed(wheel_speed);
  right_front.setSpeed(0);
}

void go_right_backward() {
  left_front.setSpeed(0);
  left_back.setSpeed(wheel_speed);
  right_back.setSpeed(0);
  right_front.setSpeed(-wheel_speed);
}

void go_left_forward() {
  left_front.setSpeed(0);
  left_back.setSpeed(-wheel_speed);
  right_back.setSpeed(0);
  right_front.setSpeed(wheel_speed);
}

void go_left_backward() {
  left_front.setSpeed(wheel_speed);
  left_back.setSpeed(0);
  right_back.setSpeed(-wheel_speed);
  right_front.setSpeed(0);
}

void stop_moving() {
  left_front.setSpeed(0);
  left_back.setSpeed(0);
  right_back.setSpeed(0);
  right_front.setSpeed(0);
}
