//Graduation: 24.06.2023
//Bilge Kaan Tekin & Ahmet Baran Yazıcı

#include <SoftwareSerial.h> //including the SoftwareSerial library for Bluetooth communication
#include <AccelStepper.h> //including the AccelStepper libraryin
#include <Ultrasonic.h>

SoftwareSerial Bluetooth(A8, 38); //(RX,TX)Arduino RX pin connected to HC05 TX pin

#define RIGHTOUT 3  //defining the IR Sensor's OUT pins for right
#define BACKOUT 5   //back
#define LEFTOUT 7   //left
#define FRONTOUT 9  //front

//defining the stepper motors and related pins
AccelStepper left_front(1, 42, 43); //(type:driver, STEP, DIR) ->Stepper Motor 1
AccelStepper right_front(1, 40, 41); //->Stepper Motor 2
AccelStepper right_back(1, 44, 45); //->Stepper Motor 3
AccelStepper left_back(1, 46, 47); //->Stepper Motor 4

int wheel_speed = 600; //setting the wheel speed as integer
String data_in; //the string input coming from the Bluetooth
bool isMoving = false; //boolean function for runSpeed() command

void setup() {
  //pin Mode spesification for IR sensors as inputs
  pinMode(RIGHTOUT, INPUT);
  pinMode(BACKOUT, INPUT);
  pinMode(LEFTOUT, INPUT);
  pinMode(FRONTOUT, INPUT);

  //setting the maximum speeds of motors
  left_back.setMaxSpeed(1000);
  left_front.setMaxSpeed(1000);
  right_back.setMaxSpeed(1000);
  right_front.setMaxSpeed(1000);
  Bluetooth.begin(9600);
}

void loop() {
  //an if statement for avoiding obstacle
  if ((digitalRead(RIGHTOUT) == 0) || (digitalRead(BACKOUT) == 0) || (digitalRead(LEFTOUT) == 0) || (digitalRead(FRONTOUT) == 0)) {
    stop_moving();
    delay(1000);
    if ((digitalRead(RIGHTOUT) == 0)) {
      control_sideways_left();
      stop_moving();
    }
    else if ((digitalRead(BACKOUT) == 0)) {
      control_forward();
      stop_moving();
    }
    else if ((digitalRead(LEFTOUT) == 0)) {
      control_sideways_right();
      stop_moving();
    }
    else if ((digitalRead(FRONTOUT) == 0)) {
      control_backward();
      stop_moving();
    }
  }

  while (Bluetooth.available()) {       //checks if the Bluetooth is available
    data_in = Bluetooth.readString();   //the word written from the phone will be stored in the "data_in" string

    if (data_in == "w") {               //if we write "w" in our phone,
      go_forward();                     //code will run the "go_forward() functi
      isMoving = true;                  //by assigning isMoving as true, code will perform runSpeed() function
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

//control and action codes
void control_backward() {
  left_front.setCurrentPosition(0);
  left_back.setCurrentPosition(0);
  right_back.setCurrentPosition(0);
  right_front.setCurrentPosition(0);
  while ((left_front.currentPosition() != 100) && (left_back.currentPosition() != 100) &&
         (right_back.currentPosition() != -100) && (right_front.currentPosition() != -100)) {
    left_front.setSpeed(wheel_speed / 2);
    left_back.setSpeed(wheel_speed / 2);
    right_back.setSpeed(-wheel_speed / 2);
    right_front.setSpeed(-wheel_speed / 2);
    left_front.runSpeed();
    left_back.runSpeed();
    right_front.runSpeed();
    right_back.runSpeed();
  }
}

void control_forward() {
  left_front.setCurrentPosition(0);
  left_back.setCurrentPosition(0);
  right_back.setCurrentPosition(0);
  right_front.setCurrentPosition(0);
  while ((left_front.currentPosition() != -100) && (left_back.currentPosition() != -100) &&
         (right_back.currentPosition() != 100) && (right_front.currentPosition() != 100)) {
    left_front.setSpeed(-wheel_speed / 2);
    left_back.setSpeed(-wheel_speed / 2);
    right_back.setSpeed(wheel_speed / 2);
    right_front.setSpeed(wheel_speed / 2);
    left_front.runSpeed();
    left_back.runSpeed();
    right_front.runSpeed();
    right_back.runSpeed();
  }
}

void control_sideways_right() {
  left_front.setCurrentPosition(0);
  left_back.setCurrentPosition(0);
  right_back.setCurrentPosition(0);
  right_front.setCurrentPosition(0);
  while ((left_front.currentPosition() != -100) && (left_back.currentPosition() != 100) &&
         (right_back.currentPosition() != 100) && (right_front.currentPosition() != -100)) {
    left_front.setSpeed(-wheel_speed / 2);
    left_back.setSpeed(wheel_speed / 2);
    right_back.setSpeed(wheel_speed / 2);
    right_front.setSpeed(-wheel_speed / 2);
    left_front.runSpeed();
    left_back.runSpeed();
    right_front.runSpeed();
    right_back.runSpeed();
  }
}

void control_sideways_left() {
  left_front.setCurrentPosition(0);
  left_back.setCurrentPosition(0);
  right_back.setCurrentPosition(0);
  right_front.setCurrentPosition(0);
  while ((left_front.currentPosition() != 100) && (left_back.currentPosition() != -100) &&
         (right_back.currentPosition() != -100) && (right_front.currentPosition() != 100)) {
    left_front.setSpeed(wheel_speed / 2);
    left_back.setSpeed(-wheel_speed / 2);
    right_back.setSpeed(-wheel_speed / 2);
    right_front.setSpeed(wheel_speed / 2);
    left_front.runSpeed();
    left_back.runSpeed();
    right_front.runSpeed();
    right_back.runSpeed();
  }
}

void go_forward() {                     //the void function for go forward
  left_front.setSpeed(-wheel_speed/2);    //we set the necessary directions for each wheel
  left_back.setSpeed(-wheel_speed/2);     //in order to move the robot to the forward
  right_back.setSpeed(wheel_speed/2);     //(-) signs in front of the speed is for the direction
  right_front.setSpeed(wheel_speed/2);    //and for the speed, its using the int wheel_speed that is written before
}

void go_backward() {
  left_front.setSpeed(wheel_speed/2);
  left_back.setSpeed(wheel_speed/2);
  right_back.setSpeed(-wheel_speed/2);
  right_front.setSpeed(-wheel_speed/2);
}

void go_sideways_right() {
  left_front.setSpeed(-wheel_speed/2);
  left_back.setSpeed(wheel_speed/2);
  right_back.setSpeed(wheel_speed/2);
  right_front.setSpeed(-wheel_speed/2);
}

void go_sideways_left() {
  left_front.setSpeed(wheel_speed/2);
  left_back.setSpeed(-wheel_speed/2);
  right_back.setSpeed(-wheel_speed/2);
  right_front.setSpeed(wheel_speed/2);
}

void rotate_right() {
  left_front.setSpeed(-wheel_speed/2);
  left_back.setSpeed(-wheel_speed/2);
  right_back.setSpeed(-wheel_speed/2);
  right_front.setSpeed(-wheel_speed/2);
}

void rotate_left() {
  left_front.setSpeed(wheel_speed/2);
  left_back.setSpeed(wheel_speed/2);
  right_back.setSpeed(wheel_speed/2);
  right_front.setSpeed(wheel_speed/2);
}

void go_right_forward() {
  left_front.setSpeed(-wheel_speed/2);
  left_back.setSpeed(0);
  right_back.setSpeed(wheel_speed/2);
  right_front.setSpeed(0);
}

void go_right_backward() {
  left_front.setSpeed(0);
  left_back.setSpeed(wheel_speed/2);
  right_back.setSpeed(0);
  right_front.setSpeed(-wheel_speed/2);
}

void go_left_forward() {
  left_front.setSpeed(0);
  left_back.setSpeed(-wheel_speed/2);
  right_back.setSpeed(0);
  right_front.setSpeed(wheel_speed/2);
}

void go_left_backward() {
  left_front.setSpeed(wheel_speed/2);
  left_back.setSpeed(0);
  right_back.setSpeed(-wheel_speed/2);
  right_front.setSpeed(0);
}

void stop_moving() {
  left_front.setSpeed(0);
  left_back.setSpeed(0);
  right_back.setSpeed(0);
  right_front.setSpeed(0);
}
