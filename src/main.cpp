/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       suttonschames                                             */
/*    Created:      Mon Oct 07 2024                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/




// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Conveyor             motor         1               
// intake               motor         3               
// Controller1          controller                    
// DriveRight           motor_group   5, 13           
// DriveLeft            motor_group   10, 11          
// PistonOut            digital_out   H               
// LinearMotion         motor_group   8, 9            
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;
//created a placeholder variable, doesn't interact w/stuff just holds 1/0
//defaulted to be 0 
bool oneDriver = true;
bool conveyorSpinning= false ;
void conveyorSpin(){
conveyorSpinning = !conveyorSpinning;
// ^^acts as a toggle/switch for the value, sets to neg val
//not gate lol
};
bool pistonPushing= false ;
void pistonPush(){
pistonPushing = !pistonPushing;
};
bool linearSpinning= false ;
void linearSpin(){
linearSpinning = !linearSpinning;
};
bool intakeSpinning= false ;
void intakeSpin(){
intakeSpinning = !intakeSpinning;
// ^^acts as a thing zoggle/switch for the value, sets to neg val
//not gate lol
};
void nothing(){

}
void switchController(){
  oneDriver = !oneDriver;
  if(oneDriver){
    Controller1.ButtonL1.pressed(conveyorSpin);
    Controller1.ButtonR2.pressed(pistonPush);
    Controller1.ButtonUp.pressed(linearSpin);
    wait(10,msec);
    Controller2.ButtonL1.pressed(nothing);
    Controller2.ButtonR2.pressed(nothing);
    Controller2.ButtonUp.pressed(nothing);
  }else{
    Controller2.ButtonL1.pressed(conveyorSpin);
    Controller2.ButtonR2.pressed(pistonPush);
    Controller2.ButtonUp.pressed(linearSpin);
    wait(10,msec);
    Controller1.ButtonL1.pressed(nothing);
    Controller1.ButtonR2.pressed(nothing);
    Controller1.ButtonUp.pressed(nothing);
  }
}// apples

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
    Controller1.ButtonL1.pressed(conveyorSpin);
    Controller1.ButtonL2.pressed(intakeSpin);
    Controller1.ButtonR2.pressed(pistonPush);
    Controller1.ButtonUp.pressed(linearSpin);
    Controller1.ButtonA.pressed(switchController);

  //Controller1.ButtonUp.pressed(linearSpin);
  //binds the button to the function callback



  while (true) {
    if(oneDriver){  
      if(Controller1.ButtonUp.pressing()){
        LinearMotion.spin(forward,100,pct);
      }else if(Controller1.ButtonDown.pressing()){
        LinearMotion.spin(reverse,100,pct);
      }else{
        LinearMotion.stop(coast);
      }
    }else{
      if(Controller2.ButtonUp.pressing()){
        LinearMotion.spin(forward,100,pct);
      }else if(Controller2.ButtonDown.pressing()){
        LinearMotion.spin(reverse,100,pct);
      }else{
        LinearMotion.stop(coast);
      }
    }
    DriveLeft.spin(forward,Controller1.Axis3.value(),pct);
    DriveRight.spin(forward,Controller1.Axis2.value(),pct);

    Conveyor.spin(forward,100*conveyorSpinning,pct);
    intake.spin(forward,100*intakeSpinning,pct);

    PistonOut.set(pistonPushing);
  }

// spins both motors
//DriveLeftFront.spin(forward);
//DriveLeftBack.spin(forward);
//DriveRightFront.spin(forward);
//DriveRightBack.spin(forward);


wait(25, msec);


//intake mechanism - l1 and l2
//pressed takes the callback function and uses as variable to toggle/trigger an event
}
