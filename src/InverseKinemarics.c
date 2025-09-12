#include <stdio.h>
#include "math.h"

#define PI 3.141592654

#define L1 13.5  // in centimeters
#define L2 12.5
#define L3 7

// Joint angles
float theta_e;   // End effector orientation
float theta_0;    
float theta_1;
float theta_2;
float theta_3;


#define STEP_Y 2   // step size along Y
#define STEP_X 2   // step size along X
#define STEP_z 2   // step size along z


typedef struct {
    int x, y, z;
} Point3D;

///////////////////////////////////////////////////////////////////////////////////
//inverse kinematics

int inverse_kinematics(double xe, double ye, double ze, double theta_e) {
    double xw = xe - (L3 * cos(theta_e));
    double yw = ye - (L3 * sin(theta_e));
    double zw = ze;

    double r = sqrt(xw*xw + yw*yw);

    theta_0 = atan2(ze, xe);

    double a = (L1*L1 + r*r - L2*L2) / (2.0 * L1 * r);
    double b = (L1*L1 + L2*L2 - r*r) / (2.0 * L1 * L2);

    // Clamp values fore cosine rule should not exceed (-1,1)
    if (a > 1.0) a = 1.0;
    if (a < -1.0) a = -1.0;
    if (b > 1.0) b = 1.0;
    if (b < -1.0) b = -1.0;

    // theta_1 = atan2(zw, sqrt(xw*xw + yw*yw)) + acos(a);
    theta_1 = atan2(yw, xw) + acos(a);

    theta_2 = (PI/2 + acos(-b));   // pi/2+acosb

    theta_3 = PI/2 + theta_e - theta_1 - theta_2;

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////
//movement in z direction keeping x-10 constant 
void zigzag_motion_1D(Point3D start, Point3D end, FILE *fptr) {
    int dir = 1; // 1 = forward in Y, -1 = backward
    int x = start.x;

    for (int z = start.z; z <= end.z; z += STEP_z) {
        if (dir == 1) {

            for (int y = start.y; y <= end.y; y += STEP_Y) {
                inverse_kinematics(x,y,z,theta_e);
                printf("%d %d %d %f %f %f %f \n", x, y, z, theta_0, theta_1, theta_2, theta_3);
                fprintf(fptr, "%d %d %d %f %f %f %f \n", x, y, z, theta_0, theta_1, theta_2, theta_3);

            }
        } else {
            for (int y = end.y; y >= start.y; y -= STEP_Y) {
                inverse_kinematics(x,y,z,theta_e);
                printf("%d %d %d %f %f %f %f \n", x, y, z, theta_0, theta_1, theta_2, theta_3);
                fprintf(fptr, "%d %d %d %f %f %f %f \n", x, y, z, theta_0, theta_1, theta_2, theta_3);
            }
        }
        dir *= -1; // flip direction each row
    }
}

//movement in z direction keeping with variable x
void zigzag_motion_2D(Point3D start, Point3D end, FILE *fptr) {
    int dir = 1; // 1 = forward in Y, -1 = backward
    int x = start.x;

    for (int y = start.y; y <= end.y; y += STEP_Y) {
        if (dir == 1) {

            for (int z = start.z; z <= end.z; z += STEP_z) {
                inverse_kinematics(x,y,z,theta_e);
                printf("%d %d %d %f %f %f %f \n", x, y, z, theta_0, theta_1, theta_2, theta_3);
                fprintf(fptr, "%d %d %d %f %f %f %f \n", x, y, z, theta_0, theta_1, theta_2, theta_3);
            }
        } else {
            for (int z = end.z; z >= start.z; z -= STEP_z) {
                inverse_kinematics(x,y,z,theta_e);
                printf("%d %d %d %f %f %f %f \n", x, y, z, theta_0, theta_1, theta_2, theta_3);
                fprintf(fptr, "%d %d %d %f %f %f %f \n", x, y, z, theta_0, theta_1, theta_2, theta_3);
            }
        }
        dir *= -1; // flip direction each row
    }
}

///////////////////////////////////////////////////////////////////////////////////

// main function

int main() {
    FILE *fptr;
    fptr = fopen("Angles.txt", "w");  
    if (!fptr) {
        perror("Error opening file");
        return 1;
    }

    Point3D p1 = {10, 8, 0};       // 1st vertical motion
    Point3D p2 = {10, 18, 20};

    Point3D p3 = {12, 8, 0};      // horizontal motion
    Point3D p4 = {12, 18, 20};

    Point3D p5 = {15, 8, 0};      // vertical motion
    Point3D p6 = {15, 18, 20};

    Point3D p7 = {18, 8, 0};       //horizontal motion
    Point3D p8 = {18, 18, 20};

    Point3D p9 = {10, 8, 0};      //vertical motion
    Point3D p10 = {10, 18, 20};


    zigzag_motion_1D(p1, p2, fptr);
    zigzag_motion_2D(p3,p4,fptr);
    zigzag_motion_1D(p5,p6,fptr);
    zigzag_motion_2D(p7,p8,fptr);

    // zigzag_motion_2D(p9,p10,fptr);



    fclose(fptr);
    return 0;
}