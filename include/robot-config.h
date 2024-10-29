using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Conveyor;
extern motor intake;
extern motor_group DriveRight;
extern motor_group DriveLeft;
extern digital_out PistonOut;
extern motor_group LinearMotion;
extern controller Controller1;
extern controller Controller2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );