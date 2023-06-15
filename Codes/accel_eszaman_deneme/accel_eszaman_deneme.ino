//iki motor iç içe deneme

#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin1 2
#define stepPin1 3
#define motorInterfaceType1 1

#define dirPin2 7
#define stepPin2 6
#define motorInterfaceType2 1


// Create a new instance of the AccelStepper class:
AccelStepper stepper1 = AccelStepper(motorInterfaceType1, stepPin1, dirPin1);
AccelStepper stepper2 = AccelStepper(motorInterfaceType2, stepPin2, dirPin2);

float wheelSpeed = 800;



void setup() {
  // Set the maximum speed in steps per second:
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
}

void loop()
{

  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  iki_motor_ileri();
  iki_motor_geri();
  
  stepper1.runSpeed();
  stepper2.runSpeed();
  delay(2000);

}
void iki_motor_ileri() {
    stepper1.setSpeed(wheelSpeed);
    stepper2.setSpeed(wheelSpeed);
}

void iki_motor_geri() {
    stepper1.setSpeed(-wheelSpeed);
    stepper2.setSpeed(-wheelSpeed);
}
