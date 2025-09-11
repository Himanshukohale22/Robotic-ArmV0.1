// #include <stdio.h>
// #include <math.h>

// #define PI 3.141592654

// #define L1 12.0  // in centimeters
// #define L2 12.0
// #define L3 6.0

// #define STEP_Y 20   // step size along Y
// #define STEP_X 20   // step size along X

// // Joint angles
// float theta_e;   // End effector orientation
// // joint angles for other links 
// float theta_0;    
// float theta_1;
// float theta_2;
// float theta_3;


// typedef struct {
//     int x, y, z;
// } Point3D;


// int inverse_kinematics(double xe, double ye, double ze, double theta_e);

// int inverse_kinematics(double xe, double ye, double ze, double theta_e) {
    
//     double xw = xe - (L3 * cos(theta_e));
//     double yw = ye - (L3 * sin(theta_e));
//     double zw = ze;

    
//     double r = sqrt(xw*xw + yw*yw + zw*zw);

    
//     theta_0 = atan2(ze, xe);

//     double a = (L1*L1 + r*r - L2*L2) / (2.0 * L1 * r);
//     double b = (L1*L1 + L2*L2 - r*r) / (2.0 * L1 * L2);

//     // Clamp values to avoid domain errors in acos()
//     if (a > 1.0) a = 1.0;
//     if (a < -1.0) a = -1.0;
//     if (b > 1.0) b = 1.0;
//     if (b < -1.0) b = -1.0;

//     theta_1 = atan2(zw, sqrt(xw*xw + yw*yw)) + acos(a);
//     theta_2 = PI - acos(b);
//     theta_3 = theta_e - theta_1 - theta_2;

//     return 0;
// }


// // Pass FILE* so we can log directly to file
// void zigzag_motion(Point3D start, Point3D end, FILE *fptr) {
//     int dir = 1; // 1 = forward in Y, -1 = backward
//     int z = start.z;

//     for (int x = start.x; x >= end.x; x -= STEP_X) {
//         if (dir == 1) {
//             for (int y = start.y; y >= end.y; y -= STEP_Y) {
//                 printf("(%d, %d, %d)\n", x, y, z);                // to terminal
//                 fprintf(fptr, "%d %d %d\n", x, y, z);              // to file
//             }
//         } else {
//             for (int y = end.y; y <= start.y; y += STEP_Y) {
//                 printf("(%d, %d, %d)\n", x, y, z);
//                 fprintf(fptr, "%d %d %d\n", x, y, z);
//             }
//         }
//         dir *= -1; // flip direction each row
//     }
// }

// int main() {
    
//     /// co-ordinates print in sheet 
//     FILE *fptr1;
//     fptr1 = fopen("coordinates_values.txt", "w");  // ✅ fixed quotes and extension
//     if (!fptr1) {
//         perror("Error opening file");
//         return 1;
//     }
//     // angles print in sheet 

//     FILE *fptr2;
//     fptr2 = fopen("coordinates_values.txt", "w");  // ✅ fixed quotes and extension
//     if (!fptr2) {
//         perror("Error opening file");
//         return 1;
//     }

//     // /////////////

//     double xe = 0.0, ye = 29.0, ze = 0.0;
//     theta_e = PI/2;  // End effector orientation (45 degrees)

//     inverse_kinematics(xe, ye, ze, theta_e);

//     printf("Theta 0 = %f rad\n", theta_0);
//     printf("Theta 1 = %f rad\n", theta_1);
//     printf("Theta 2 = %f rad\n", theta_2);
//     printf("Theta 3 = %f rad\n", theta_3);

//     return 0;
// }


// ==================================================================


#include <stdio.h>
#include <math.h>

#define PI 3.141592654

#define L1 12.0  // in centimeters
#define L2 12.0
#define L3 6.0

// Joint angles
float theta_e;   // End effector orientation
float theta_0;    
float theta_1;
float theta_2;
float theta_3;

#define STEP_Y 20   // step size along Y
#define STEP_X 20   // step size along X

typedef struct {
    double x, y, z;
} Point3D;

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

    theta_2 = -(PI - acos(b));
    theta_3 = theta_e - theta_1 - theta_2;

    return 0;
}

// void zigzag_motion(Point3D start, Point3D end, FILE *fptr_out) {
//     int dir = 1; // 1 = forward in Y, -1 = backward
//     int z = start.z;

//     for (int x = start.x; x >= end.x; x -= STEP_X) {
//         if (dir == 1) {
//             for (int y = start.y; y >= end.y; y -= STEP_Y) {
//                 inverse_kinematics(x,y,z,theta_e);
//                 printf("(%d, %d, %d)\n", x, y, z);                // to terminal
//                 fprintf(fptr_out, "%d %d %d\n", x, y, z);              // to file
//             }
//         } else {
//             for (int y = end.y; y <= start.y; y += STEP_Y) {
//                 inverse_kinematics(x,y,z,theta_e);
//                 printf("(%d, %d, %d)\n", x, y, z);
//                 fprintf(fptr_out, "%d %d %d\n", x, y, z);
//             }
//         }
//         dir *= -1; // flip direction each row
//     }
// }

int main() {
    FILE *fptr_in, *fptr_out;
    
    // Open file with coordinates (already generated)
    fptr_in = fopen("coordinates_values.txt", "r");
    if (!fptr_in) {
        perror("Error opening input file");
        return 1;
    }

    // Open file with coordinates (not generated) --- output in single file
    // fptr_in = fopen("coordinates_values.txt","w");
    // if (!fptr_in)
    // {
    //     perror("Error opening file");
    //     return 1;
    // }

    // Output file to save thetas

    // Point3D p1 = {150, 150, -80};
    // Point3D p2 = {-150, -150, -80};

    // zigzag_motion(p1, p2,fptr_out);

    fptr_out = fopen("angles_values.txt", "w");
    if (!fptr_out) {
        perror("Error opening output file");
        fclose(fptr_in);
        return 1;
    }

    double xe, ye, ze;
    theta_e = 0;  // fixed orientation (90°)

    fprintf(fptr_out, "xe   ye   ze   theta0   theta1   theta2   theta3\n");

    // Read each line: x y z (IPC not to be used)
    while (fscanf(fptr_in, "%lf %lf %lf", &xe, &ye, &ze) == 3) {
        inverse_kinematics(xe, ye, ze, theta_e);

        printf("Input (%.2f, %.2f, %.2f) -> Θ0=%.3f, Θ1=%.3f, Θ2=%.3f, Θ3=%.3f\n",
               xe, ye, ze, theta_0, theta_1, theta_2, theta_3);

        fprintf(fptr_out, "%.2f %.2f %.2f %.5f %.5f %.5f %.5f\n",
                xe, ye, ze, theta_0, theta_1, theta_2, theta_3);
    }

    // inverse_kinematics(xe,ye,ze,theta_e);
    // fprintf(fptr_out, "%.2f %.2f %.2f %.5f %.5f %.5f %.5f\n",
    //             xe, ye, ze, theta_0, theta_1, theta_2, theta_3);


    fclose(fptr_in);
    fclose(fptr_out);

    return 0;
}
