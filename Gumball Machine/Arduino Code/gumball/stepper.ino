#include <Stepper.h>

#define STEPPER_EN1 5
#define STEPPER_EN2 6
#define STEPPER_MC1 4
#define STEPPER_MC2 7
 
Stepper myStepper = Stepper(200, STEPPER_MC2, STEPPER_MC1); 

void stepperSetup() {
    pinMode(STEPPER_EN1, OUTPUT);
    pinMode(STEPPER_EN2, OUTPUT);
    myStepper.setSpeed(10);
}

void stepperSpin(){ 
  digitalWrite(STEPPER_EN1, HIGH);
  digitalWrite(STEPPER_EN2, HIGH);
  myStepper.step(-1);  
}

void stepperRevolution(){
  //My hack to enable the h bridge 
  digitalWrite(STEPPER_EN1, HIGH);
  digitalWrite(STEPPER_EN2, HIGH);
  //Step one full rotation
  myStepper.step(-200);
  //Wait 5 seconds
  //delay(5000);
}
