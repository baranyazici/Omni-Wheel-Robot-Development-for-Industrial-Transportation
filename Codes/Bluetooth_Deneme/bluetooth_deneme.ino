//Bluetooth denemesi

#include <SoftwareSerial.h>
#include <AccelStepper.h>

SoftwareSerial Bluetooth(A8, 38); //Arduino RX pin connected to HC05 TX pin
                                  //Arduino TX pin connected to HC05 RX pin

//defining the stepper motors and related pins 
AccelStepper left_front(1, 42, 43); //(type:driver, STEP, DIR) -Stepper Motor 1
AccelStepper left_back(1, 40, 41); //Stepper Motor 2
AccelStepper right_back(1, 44, 45); //Stepper Motor 3
AccelStepper right_front(1, 46, 47); //Stepper Motor 4

int wheel_speed = 900;
int data_in, kk;


void setup() {
  //maximum speeds
  lef_back.setMaxSpeed(1000);
  left_front.setMaxSpeed(1000);
  right_back.setMaxSpeed(1000);
  right_front.setMaxSpeed(1000);

  Serial.begin(38400);
  Bluetooth.begin(38400);
  Bluetooth.setTimeout(1);
  delay(20);

  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  

}

void go_forward(){
  left_front.setSpeed(-wheel_speed);
  left_back.setSpeed(-wheel_speed);
  right_back.setSpeed(wheel_speed);
  right_front.setSpeed(wheel_speed);  
}

void go_backward(){
  left_front.setSpeed(wheel_speed);
  left_back.setSpeed(wheel_speed);
  right_back.setSpeed(-wheel_speed);
  right_front.setSpeed(-wheel_speed);  
}

void go_sideway_right(){
  left_front.setSpeed(-wheel_speed);
  left_back.setSpeed(wheel_speed);
  right_back.setSpeed(wheel_speed);
  right_front.setSpeed(-wheel_speed);  
}

void go_sideway_left(){
  left_front.setSpeed(wheel_speed);
  left_back.setSpeed(-wheel_speed);
  right_back.setSpeed(-wheel_speed);
  right_front.setSpeed(wheel_speed);    
}

void rotate_right(){
  left_front.setSpeed(-wheel_speed);
  left_back.setSpeed(-wheel_speed);
  right_back.setSpeed(-wheel_speed);
  right_front.setSpeed(-wheel_speed);     
}

void rotate_left(){
  left_front.setSpeed(wheel_speed);
  left_back.setSpeed(wheel_speed);
  right_back.setSpeed(wheel_speed);
  right_front.setSpeed(wheel_speed);    
}

void go_right_forward(){
  left_front.setSpeed(-wheel_speed);
  left_back.setSpeed(0);
  right_back.setSpeed(wheel_speed);
  right_front.setSpeed(0);   
}

void go_right_backward(){
  left_front.setSpeed(0);
  left_back.setSpeed(wheel_speed);
  right_back.setSpeed(0);
  right_front.setSpeed(-wheel_speed);     
}

void go_left_forward(){
  left_front.setSpeed(0);
  left_back.setSpeed(-wheel_speed);
  right_back.setSpeed(0);
  right_front.setSpeed(wheel_speed);       
}

void go_left_backward(){
  left_front.setSpeed(wheel_speed);
  left_back.setSpeed(0);
  right_back.setSpeed(-wheel_speed);
  right_front.setSpeed(0);  
}

void stop_moving(){
  left_front.setSpeed(0);
  left_back.setSpeed(0);
  right_back.setSpeed(0);
  right_front.setSpeed(0);  
}
