// Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
//    M1=base degrees. Allowed values from 0 to 180 degrees
//    M2=shoulder degrees. Allowed values from 15 to 165 degrees
//    M3=elbow degrees. Allowed values from 0 to 180 degrees
//    M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
//    M5=wrist rotation degrees.elbow Allowed values from 0 to 180 degrees
//    M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.


#include <stdio.h>
#include "math.h"


typedef struct {
    int x, y, z;
} Point3D;

#define STEP_Y 2   // step size along Y
#define STEP_X 2   // step size along X
#define STEP_z 2 
// Pass FILE* so we can log directly to file
void zigzag_motion(Point3D start, Point3D end, FILE *fptr) {
    int dir = 1; // 1 = forward in Y, -1 = backward
    int x = start.x;

    for (int z = start.z; z <= end.z; z += STEP_z) {
        if (dir == 1) {

            for (int y = start.y; y <= end.y; y += STEP_Y) {
                printf("(%d, %d, %d)\n", x, y, z);                // to terminal
                fprintf(fptr, "%d %d %d\n", x, y, z);             // to file
            }
        } else {
            for (int y = end.y; y >= start.y; y -= STEP_Y) {
                printf("(%d, %d, %d)\n", x, y, z);
                fprintf(fptr, "%d %d %d\n", x, y, z);
            }
        }
        dir *= -1; // flip direction each row
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("datafiles/Coordinates_values.txt", "w");  // ✅ fixed quotes and extension
    if (!fptr) {
        perror("Error opening file");
        return 1;
    }

    // write header
    // fprintf(fptr, "xe ye ze\n");

    // Point3D p1 = {10, 6.2 , 0};
    // Point3D p2 = {10, 24, 20};

    // zigzag_motion(p1, p2, fptr);

    Point3D p1 = {10, 6.2, 0};       // 1st vertical motion
    Point3D p2 = {10, 24, 20};

    Point3D p3 = {12, 6.2, 0};      // horizontal motion
    Point3D p4 = {12, 24, 20};

    // Point3D p5 = {15, 6.2, 0};      // vertical motion
    // Point3D p6 = {15, 24, 20};

    Point3D p7 = {18, 6.2, 0};       //horizontal motion
    Point3D p8 = {18, 24, 20};

    // Point3D p9 = {10, 6.2, 0};      //vertical motion
    // Point3D p10 = {10, 24, 20};


    zigzag_motion_1D(p1, p2, fptr);
    zigzag_motion_2D(p3,p4,fptr);
    // zigzag_motion_1D(p5,p6,fptr);
    zigzag_motion_2D(p7,p8,fptr);

    fclose(fptr);
    return 0;
}
