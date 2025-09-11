#include <stdio.h>

typedef struct {
    int x, y, z;
} Point3D;

#define STEP_Y 2   // step size along Y
#define STEP_X 2   // step size along X
#define STEP_z 2   // step size along z

//movement in z direction keeping x-10 constant 
void zigzag_motion_1D(Point3D start, Point3D end, FILE *fptr) {
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

//movement in z direction keeping with variable x
void zigzag_motion_2D(Point3D start, Point3D end, FILE *fptr) {
    int dir = 1; // 1 = forward in Y, -1 = backward
    int x = start.x;

    for (int y = start.y; y <= end.y; y += STEP_Y) {
        if (dir == 1) {

            for (int z = start.z; z <= end.z; z += STEP_z) {
                printf("(%d, %d, %d)\n", x, y, z);                // to terminal
                fprintf(fptr, "%d %d %d\n", x, y, z);             // to file
            }
        } else {
            for (int z = end.z; z >= start.z; z -= STEP_z) {
                printf("(%d, %d, %d)\n", x, y, z);
                fprintf(fptr, "%d %d %d\n", x, y, z);
            }
        }
        dir *= -1; // flip direction each row
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("coordinates_values.txt", "w");  
    if (!fptr) {
        perror("Error opening file");
        return 1;
    }

    Point3D p1 = {10, 8, -10};       // 1st vertical motion
    Point3D p2 = {10, 18, 10};

    Point3D p3 = {12, 8, -10};      // horizontal motion
    Point3D p4 = {12, 18, 10};

    Point3D p5 = {15, 8, -10};      // vertical motion
    Point3D p6 = {15, 18, 10};

    Point3D p7 = {18, 8, -10};       //horizontal motion
    Point3D p8 = {18, 18, 10};

    Point3D p9 = {10, 8, -10};      //vertical motion
    Point3D p10 = {10, 18, 10};


    zigzag_motion_1D(p1, p2, fptr);
    zigzag_motion_2D(p3,p4,fptr);
    zigzag_motion_1D(p5,p6,fptr);
    zigzag_motion_2D(p7,p8,fptr);

    // zigzag_motion_2D(p9,p10,fptr);



    fclose(fptr);
    return 0;
}
