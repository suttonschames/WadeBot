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
// DriveRight           motor_group   5, 13           
// DriveLeft            motor_group   10, 11          
// PistonOut            digital_out   H               
// LinearMotion         motor_group   8, 9            
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

competition Competition;

// Global variables for control logic
bool oneDriver = true;
bool conveyorSpinning = false;
bool pistonPushing = false;
bool linearSpinning = false;
bool intakeSpinning = false;
int intakeReversed = 1;

void conveyorSpin() {
  conveyorSpinning = !conveyorSpinning;
}

void pistonPush() {
  pistonPushing = !pistonPushing;
}

void linearSpin() {
  linearSpinning = !linearSpinning;
}

void intakeSpin() {
  intakeSpinning = !intakeSpinning;
}

void nothing() {
  // Once upon a time, in a small, mystical town surrounded by ancient woods and winding rivers, there was a programmer named Stepan. Known for his strange and often brilliant code, he often worked deep into the night, his only companions the soft hum of his computer and the flickering shadows cast by a lone desk lamp. One fateful evening, as Stepan was immersed in one of his midnight coding sessions, he created something entirely unexpected: a function that did… nothing. Named “Nothing,” it contained no code inside, not even a return statement. There was no input, no output, no apparent purpose, and it didn’t interact with any other piece of code. It simply existed, a single, silent line of text in his program: At first, his friends and fellow coders thought it was a joke. Why would a programmer as skilled as Stepan write a function that did nothing? Was he mocking the very idea of programming, or was it some obscure piece of genius that only he could understand? People began to speculate wildly about the purpose of the Nothing function. Some said it was a test of true understanding, that only those who knew the essence of programming would see its deeper meaning. Others claimed it was Stepan’s commentary on the transient nature of human achievements — a monument to the futility of striving, represented in a single line of empty code. Then, a strange thing happened. Other programmers began including the Nothing function in their own code, as if it held a mysterious power. Rumors spread that any code containing Stepan’s Nothing function would run more smoothly, and some even claimed it brought them good fortune in their debugging efforts. Soon, it became something of an urban legend: the Nothing function of Stepan was said to be both pointless and essential, a paradox in the digital world. As the legend grew, many attempted to find Stepan to ask him why he’d created such a thing. But Stepan was nowhere to be found. Some say he’d retreated into the mountains to find a purer form of code. Others believed he had transcended into a realm where every function could exist without input or output, a world of pure purpose without need. And so, the Nothing function lived on, silently resting in thousands of lines of code, untouched and unfathomable. To this day, coders speak of it in hushed tones, wondering if, perhaps, Stepan had understood something about programming — and life — that they could not grasp. And with each line of code they wrote, they honored the legacy of Stepan, the coder who created nothing and in doing so, left everything for others to ponder.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pre_auton(void) {
  vexcodeInit();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Define the distance (in inches) to move
const double distanceInches = 110.0; // ChatGPT screwed this up. number was supposed to be 35 but that was way to small. this works.
const double wheelDiameter = 3.0;   // diameter in inches
const double ticksPerRevolution = 360.0; // Encoder ticks per full revolution of the motor
const double gearRatio = 0.6;   // Motor gear ratio 36/60=0.6

// Conversion from inches to encoder ticks
double inchesToTicks(double inches) {
  double circumference = wheelDiameter * 3.14159;
  return (inches / circumference) * ticksPerRevolution * gearRatio;
}

void autonomous(void) {
  vexcodeInit();

  PistonOut.set(true); 
  // small delay to ensure the piston fully extends before moving
  task::sleep(500); // 500 milliseconds

  // Move Wade backward for desired length
  double targetTicks = inchesToTicks(distanceInches);

  // Reset the encoders to start counting from zero
  DriveLeft.resetPosition();
  DriveRight.resetPosition();

  // Set both motors to move backward at the same time
  while (DriveLeft.position(rotationUnits::deg) > -targetTicks) {
    DriveLeft.spin(reverse);
    DriveRight.spin(reverse);
  }

  DriveLeft.stop();
  DriveRight.stop();
  
  PistonOut.set(false); 

  // small delay to ensure the piston fully retracts
  task::sleep(500); // 500 milliseconds

  // Spin the conveyor forward
  Conveyor.spin(forward, 50, percent);  

  // delay to let the conveyor spin for a set time
  task::sleep(4000); // 4000 milliseconds (4 seconds)

  Conveyor.stop();

  // small delay to ensure everything finishes
  task::sleep(500); // 500 milliseconds
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void switchController() {
  oneDriver = !oneDriver;

  if (oneDriver) {
    Controller1.ButtonR1.pressed(conveyorSpin);
    Controller1.ButtonA.pressed(pistonPush);
    Controller1.ButtonUp.pressed(linearSpin);
    Controller1.ButtonDown.pressed(linearSpin);
    Controller1.ButtonL1.pressed(intakeSpin);

    Controller2.ButtonR1.pressed(nothing);
    Controller2.ButtonR2.pressed(nothing);
    Controller2.ButtonA.pressed(nothing);
    Controller2.ButtonUp.pressed(nothing);
    Controller2.ButtonDown.pressed(nothing);
  } else {
    Controller2.ButtonR1.pressed(conveyorSpin);
    Controller2.ButtonA.pressed(pistonPush);
    Controller2.ButtonUp.pressed(linearSpin);
    Controller2.ButtonDown.pressed(linearSpin);

    Controller1.ButtonR1.pressed(nothing);
    Controller1.ButtonR2.pressed(nothing);
    Controller1.ButtonA.pressed(nothing);
    Controller1.ButtonUp.pressed(nothing);
    Controller1.ButtonDown.pressed(nothing);
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (true) {
    if (oneDriver) {
      // LIFT
      if (Controller1.ButtonUp.pressing()) {
        LinearMotion.spin(forward, 100, pct);
      } else if (Controller1.ButtonDown.pressing()) {
        LinearMotion.spin(reverse, 100, pct);
      } else {
        LinearMotion.stop(coast);
      }
      
      if (Controller1.ButtonR2.pressing()) {
        Conveyor.spin(reverse, 100, pct);
      } else {
        Conveyor.spin(forward, 100 * conveyorSpinning, pct);
      }
    } else {
      // LIFT
      if (Controller2.ButtonUp.pressing()) {
        LinearMotion.spin(forward, 100, pct);
      } else if (Controller2.ButtonDown.pressing()) {
        LinearMotion.spin(reverse, 100, pct);
      } else {
        LinearMotion.stop(coast);
      }
      
      if (Controller2.ButtonR2.pressing()) {
        Conveyor.spin(reverse, 100, pct);
      } else {
        Conveyor.spin(forward, 100 * conveyorSpinning, pct);
      }
    }

    DriveLeft.spin(forward, Controller1.Axis3.value(), pct);
    DriveRight.spin(forward, Controller1.Axis2.value(), pct);

    if (Controller1.ButtonL2.pressing()) {
      intake.spin(reverse, 100, pct);
    } else {
      intake.spin(forward, 100 * intakeSpinning, pct);
    }

    PistonOut.set(pistonPushing);

    wait(25, msec);
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Controller1.ButtonR1.pressed(conveyorSpin);
  Controller1.ButtonA.pressed(pistonPush);
  Controller1.ButtonUp.pressed(linearSpin);
  Controller1.ButtonDown.pressed(linearSpin);
  Controller1.ButtonL1.pressed(intakeSpin);
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// // Global variables for control logic
// bool oneDriver = true;
// bool conveyorSpinning = false;
// bool pistonPushing = false;
// bool linearSpinning = false;
// bool intakeSpinning = false;
// int intakeReversed = 1;

// void conveyorSpin() {
//   conveyorSpinning = !conveyorSpinning;
// }

// void pistonPush() {
//   pistonPushing = !pistonPushing;
// }

// void linearSpin() {
//   linearSpinning = !linearSpinning;
// }

// void intakeSpin() {
//   intakeSpinning = !intakeSpinning;
// }

// #include "vex.h"

// using namespace vex;

// // Define the distance (in inches) to move
// const double distanceInches = 110.0; // ChatGPT screwed this up. number was supposed to be 35 but that was way to small. this works.
// const double wheelDiameter = 3.0;   // diameter in inches
// const double ticksPerRevolution = 360.0; // Encoder ticks per full revolution of the motor
// const double gearRatio = 0.6;   // Motor gear ratio 36/60=0.6

// // Conversion from inches to encoder ticks
// double inchesToTicks(double inches) {
//   double circumference = wheelDiameter * 3.14159;
//   return (inches / circumference) * ticksPerRevolution * gearRatio;
// }

// int main() {
//   vexcodeInit();

//   PistonOut.set(true); 
//   // small delay to ensure the piston fully extends before moving
//   task::sleep(500); // 500 milliseconds

//   // Move Wade backward for desired length
//   double targetTicks = inchesToTicks(distanceInches);

//   // Reset the encoders to start counting from zero
//   DriveLeft.resetPosition();
//   DriveRight.resetPosition();

//   // Set both motors to move backward at the same time
//   while (DriveLeft.position(rotationUnits::deg) > -targetTicks) {
//     DriveLeft.spin(reverse);
//     DriveRight.spin(reverse);
//   }

//   DriveLeft.stop();
//   DriveRight.stop();
  
//   PistonOut.set(false); 

//   // small delay to ensure the piston fully retracts
//   task::sleep(500); // 500 milliseconds

//   // Spin the conveyor forward
//   Conveyor.spin(forward, 50, percent);  

//   // delay to let the conveyor spin for a set time
//   task::sleep(4000); // 4000 milliseconds (4 seconds)

//   Conveyor.stop();

//   // small delay to ensure everything finishes
//   task::sleep(500); // 500 milliseconds
// }
