//Bilge Kaan Tekin & Ahmet Baran Yazıcı

#include <SoftwareSerial.h> //including the SoftwareSerial library for Bluetooth communication
#include <AccelStepper.h> //including the AccelStepper libraryin
#include <Ultrasonic.h>

SoftwareSerial Bluetooth(A8, 38); //(RX,TX)Arduino RX pin connected to HC05 TX pin


#define RIGHTOUT 3
#define LEFTOUT 5
#define TRIGPIN3 7
#define ECHOPIN3 6
#define TRIGPIN4 9
#define ECHOPIN4 8
volatile float MAX_DISTANCE = 15.00;
volatile float frontDuration, frontDistanceCm, leftDuration, leftDistanceCm, rightDuration, rightDistanceCm, backDuration, backDistanceCm;
long duration;
int distance;

//defining the stepper motors and related pins
AccelStepper left_front(1, 42, 43); //(type:driver, STEP, DIR) ->Stepper Motor 1
AccelStepper right_front(1, 40, 41); //->Stepper Motor 2
AccelStepper right_back(1, 44, 45); //->Stepper Motor 3
AccelStepper left_back(1, 46, 47); //->Stepper Motor 4

int wheel_speed = 800; //setting the wheel speed as integer
unsigned long previousTime = 0;
unsigned long currentTime = 0;
String data_in; //the string input coming from the Bluetooth
bool isMoving = false;


void setup() {
  //Serial.begin(9600);
  pinMode(RIGHTOUT,INPUT);
  pinMode(LEFTOUT, INPUT);
  //setting the maximum speeds of motors
  left_back.setMaxSpeed(1500);
  left_front.setMaxSpeed(1500);
  right_back.setMaxSpeed(1500);
  right_front.setMaxSpeed(1500);
  Bluetooth.begin(9600);
}

void loop() {

  if((digitalRead(RIGHTOUT)== 0) || (digitalRead(LEFTOUT)== 0)){
    stop_moving();
  }


  while (Bluetooth.available()) {       //checks if the Bluetooth is available
    data_in = Bluetooth.readString();   //the word written from the phone will be stored in the "data_in" string

    if (data_in == "w") {               //if we write "w" in our phone,
      go_forward();                     //code will run the "go_forward() functi
      isMoving = true;

    }
    else if (data_in == "s") {          //if user writes "s" from phone's terminal monitor
      go_backward();                    //code will run the "go_backward()" function
      isMoving = true;

    }
    else if (data_in == "d") {
      go_sideways_right();
      isMoving = true;
    }
    else if (data_in == "a") {
      go_sideways_left();
      isMoving = true;
    }
    else if (data_in == "e") {
      rotate_right();
      isMoving = true;
    }
    else if (data_in == "q") {
      rotate_left();
      isMoving = true;
    }
    else if (data_in == "wd") {
      go_right_forward();
      isMoving = true;
    }
    else if (data_in == "sd") {
      go_right_backward();
      isMoving = true;
    }
    else if (data_in == "wa") {
      go_left_forward();
      isMoving = true;
    }
    else if (data_in == "sa") {
      go_left_backward();
      isMoving = true;
    }
    else if (data_in == "p") {
      stop_moving();
      isMoving = false;
    }
  }


  if (isMoving) {
    left_front.runSpeed();
    left_back.runSpeed();
    right_front.runSpeed();
    right_back.runSpeed();
  }

}

void go_forward() {                     //the void function for go forward
  left_front.setSpeed(-wheel_speed);    //we set the necessary directions for each wheel
  left_back.setSpeed(-wheel_speed);     //in order to move the robot to the forward
  right_back.setSpeed(wheel_speed);     //(-) signs in front of the speed is for the direction
  right_front.setSpeed(wheel_speed);    //and for the speed, its using the int wheel_speed that is written before
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
