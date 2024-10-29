#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Conveyor = motor(PORT1, ratio18_1, false);
motor intake = motor(PORT3, ratio6_1, false);
motor DriveRightMotorA = motor(PORT5, ratio6_1, false);
motor DriveRightMotorB = motor(PORT13, ratio6_1, false);
motor_group DriveRight = motor_group(DriveRightMotorA, DriveRightMotorB);
motor DriveLeftMotorA = motor(PORT10, ratio6_1, true);
motor DriveLeftMotorB = motor(PORT11, ratio6_1, true);
motor_group DriveLeft = motor_group(DriveLeftMotorA, DriveLeftMotorB);
digital_out PistonOut = digital_out(Brain.ThreeWirePort.H);
motor LinearMotionMotorA = motor(PORT8, ratio36_1, false);
motor LinearMotionMotorB = motor(PORT9, ratio36_1, true);
motor_group LinearMotion = motor_group(LinearMotionMotorA, LinearMotionMotorB);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}