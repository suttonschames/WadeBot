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


bool oneDriver = true;

bool conveyorSpinning= false;
void conveyorSpin(){
  conveyorSpinning = !conveyorSpinning;
}

bool pistonPushing= false;
void pistonPush(){
  pistonPushing = !pistonPushing;
}

bool linearSpinning= false;
void linearSpin(){
  linearSpinning = !linearSpinning;
}

bool intakeSpinning= false;
void intakeSpin(){
  intakeSpinning = !intakeSpinning;
}

void nothing(){
  // ChatGPT wrote this story. I didn't read it. I thuoght it would be funny to put in here cause this function is, well, like just look at it...

  /*
  Once upon a time, in a small, mystical town surrounded by ancient woods and winding rivers, there was a programmer named Stepan. 
  Known for his strange and often brilliant code, he often worked deep into the night, his only companions the soft hum of his computer and the flickering shadows cast by a 
  lone desk lamp. One fateful evening, as Stepan was immersed in one of his midnight coding sessions, he created something entirely unexpected: a function that did… nothing. 
  Named “Nothing,” it contained no code inside, not even a return statement. There was no input, no output, no apparent purpose, and it didn’t interact with any other piece of code. 
  It simply existed, a single, silent line of text in his program:

  At first, his friends and fellow coders thought it was a joke. Why would a programmer as skilled as Stepan write a function that did nothing? Was he mocking the very idea of 
  programming, or was it some obscure piece of genius that only he could understand? People began to speculate wildly about the purpose of the Nothing function. 
  Some said it was a test of true understanding, that only those who knew the essence of programming would see its deeper meaning. 
  Others claimed it was Stepan’s commentary on the transient nature of human achievements — a monument to the futility of striving, represented in a single line of empty code.

  Then, a strange thing happened. Other programmers began including the Nothing function in their own code, as if it held a mysterious power. 
  Rumors spread that any code containing Stepan’s Nothing function would run more smoothly, and some even claimed it brought them good fortune in their debugging efforts. 
  Soon, it became something of an urban legend: the Nothing function of Stepan was said to be both pointless and essential, a paradox in the digital world.

  As the legend grew, many attempted to find Stepan to ask him why he’d created such a thing. But Stepan was nowhere to be found. 
  Some say he’d retreated into the mountains to find a purer form of code. Others believed he had transcended into a realm where every function could 
  exist without input or output, a world of pure purpose without need.

  And so, the Nothing function lived on, silently resting in thousands of lines of code, untouched and unfathomable. To this day, coders speak of it in hushed 
  tones, wondering if, perhaps, Stepan had understood something about programming — and life — that they could not grasp. And with each line of pass they wrote, 
  they honored the legacy of Stepan, the coder who created nothing and in doing so, left everything for others to ponder.
  */
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
  }
  
  else{
    Controller2.ButtonL1.pressed(conveyorSpin);
    Controller2.ButtonR2.pressed(pistonPush);
    Controller2.ButtonUp.pressed(linearSpin);
    wait(10,msec);
    Controller1.ButtonL1.pressed(nothing);
    Controller1.ButtonR2.pressed(nothing);
    Controller1.ButtonUp.pressed(nothing);
  }
}//switchController_func

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Controller1.ButtonL1.pressed(conveyorSpin);
  Controller1.ButtonL2.pressed(intakeSpin);
  Controller1.ButtonR2.pressed(pistonPush);
  Controller1.ButtonUp.pressed(linearSpin);
  Controller1.ButtonA.pressed(switchController);

  // guys, please stop writing your code blocks stacked on top of each other. it's so unreadable. keep it nice and spread out like this.
  while (true) { 
    if(oneDriver){ 
      if(Controller1.ButtonUp.pressing()){
        LinearMotion.spin(forward,100,pct);
      }
      else if(Controller1.ButtonDown.pressing()){
        LinearMotion.spin(reverse,100,pct);
      }
      else{
        LinearMotion.stop(coast);
      }
    }//if
      
    else{
      if(Controller2.ButtonUp.pressing()){
        LinearMotion.spin(forward,100,pct);
      }
      else if(Controller2.ButtonDown.pressing()){
        LinearMotion.spin(reverse,100,pct);
      }
      else{
        LinearMotion.stop(coast);
      }
    }//else
    
    DriveLeft.spin(forward,Controller1.Axis3.value(),pct);
    DriveRight.spin(forward,Controller1.Axis2.value(),pct);
    Conveyor.spin(forward,100*conveyorSpinning,pct);
    intake.spin(forward,100*intakeSpinning,pct);
    PistonOut.set(pistonPushing);
  }//while
  wait(25, msec);
}//main_func
