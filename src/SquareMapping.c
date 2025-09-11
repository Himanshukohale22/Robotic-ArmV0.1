// #include <stdio.h>

// typedef struct {
//     int x, y, z;
// } Point3D;

// #define NUM_POINTS 4   // change based on how many points you have

// // Example path points
// Point3D path[NUM_POINTS] = {
//     {150, 250, -200},
//     {-150, 250, 200},
//     {-140, 240, 200},
//     {140, 240, 200}
// };

// // Zigzag state
// int direction = 1;   // 1 = forward, -1 = backward
// int current_index = 0;

// Point3D zigzag_envelope() {
//     Point3D p = path[current_index];

//     // Move index for next call
//     current_index += direction;

//     // Reverse direction at ends
//     if (current_index >= NUM_POINTS) {
//         direction = -1;
//         current_index = NUM_POINTS - 2;
//     } else if (current_index < 0) {
//         direction = 1;
//         current_index = 1;
//     }

//     return p;
// }

// int main() {
//     for (int i = 0; i < 20; i++) {
//         Point3D p = zigzag_envelope();
//         printf("Step %d -> (%d, %d, %d)\n", i, p.x, p.y, p.z);
//     }
//     return 0;
// }

// 
// #include <stdio.h>
// 
// typedef struct {
    // int x, y, z;
// } Point3D;
// 
// #define STEP_Y 20   // step size along Y
// #define STEP_X 20   // step size along X
// 
// void zigzag_motion(Point3D start, Point3D end) {
    // int dir = 1; // 1 = forward in Y, -1 = backward
    // int z = start.z;
// 
    // for (int x = start.x; x >= end.x; x -= STEP_X) {
        // if (dir == 1) {
            // for (int y = start.y; y >= end.y; y -= STEP_Y) {
                // printf("(%d, %d, %d)\n", x, y, z);
            // }
        // } else {
            // for (int y = end.y; y <= start.y; y += STEP_Y) {
                // printf("(%d, %d, %d)\n", x, y, z);
            // }
        // }
        // dir *= -1; // flip direction each row
    // }
// 
// 
    // for (int i = 0; i < 3; i++) {
        // fprintf(stdout, "%d %d %d\n", path[i].x, path[i].y, path[i].z);
    // }
// }
// 
// int main() {
// 
    // FILE *fptr;
    // fptr = fopen('coordinates_values', 'w');
    // 
    // Point3D p1 = {150, 150, -200};
    // Point3D p2 = {-150, -150, -200};
    // fprintf(fptr,"xe | ye | ze | theta_e \n");
    // zigzag_motion(p1, p2);
// 
    // fclose(fptr);
    // return 0;
// 
// }
// 

// ======================================================



#include <stdio.h>

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
    fptr = fopen("coordinates_values.txt", "w");  // ✅ fixed quotes and extension
    if (!fptr) {
        perror("Error opening file");
        return 1;
    }

    // write header
    // fprintf(fptr, "xe ye ze\n");

    Point3D p1 = {10, 8, -10};
    Point3D p2 = {10, 18, 10};

    zigzag_motion(p1, p2, fptr);

    fclose(fptr);
    return 0;
}
