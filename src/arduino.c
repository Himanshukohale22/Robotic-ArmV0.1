 /*
  testBraccio90.ino

 testBraccio90 is a setup sketch to check the alignment of all the servo motors
 This is the first sketch you need to run on Braccio
 When you start this sketch Braccio will be positioned perpendicular to the base
 If you can't see the Braccio in this exact position you need to reallign the servo motors position

 Created on 18 Nov 2015
 by Andrea Martino

 This example is in the public domain.
 */

#include <Braccio.h>
#include <Servo.h>


/*
1Rad × 180/π = 57.296Deg
*/

double BaseAngle[];
double ShoulderAngle[];
double elbowAnlge[];

float base_angle;
float shoulder_angle;
float elbow_angle;
float wrist_angle;
float wrist_rotation;
float gripper;

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

// start of angles wrist_angle
int base_start = 0;
int base_end = 91;
int wrist_start = 0;
int wrist_end = 46;


void setup() {  
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Serial.begin(115200);
  Braccio.begin();
  
}

void loop() {
  /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
  /////////////////////////////////////////////
    if (Serial.available()) {
        String data = Serial.readStringUntil('\n'); // e.g. "0.0,3.3,-2.5,-0.7"
    }

    // Parse CSV values
    int c1 = data.indexOf(',');
    int c2 = data.indexOf(',', c1 + 1);
    int c3 = data.indexOf(',', c2 + 1);

    double theta0 = data.substring(0, c1).toFloat();
    double theta1 = data.substring(c1 + 1, c2).toFloat();
    double theta2 = data.substring(c2 + 1, c3).toFloat();
    double theta3 = data.substring(c3 + 1).toFloat();

    // Convert radians → degrees
    float base_angle = (theta0 * 180.0 / 3.14159);
    float shoulder_angle = (theta1 * 180.0 / 3.14159);
    float elbow_angle = (theta2 * 180.0 / 3.14159);
    float wrist_angle = (theta3 * 180.0 / 3.14159);

  
  /////////////////////////////////////////////

  float base_m0 = 0;
  float wrist_m4 = 0;

  ////////////////////////////////////////////

  int base_m0 = 0;
  int wrist_m4 = 0;
  int stepDelay = 20;

  delay(500);
  Braccio.ServoMovement(stepDelay, base_angle,shoulder_angle,elbow_angle, wrist_angle, wrist_rotation,gripper);	 
  delay(500);

}



//int _Braccio::ServoMovement(int stepDelay, int vBase, int vShoulder, int vElbow,int vWrist_ver, int vWrist_rot, int vgripper) {