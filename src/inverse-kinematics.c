#include <stdio.h>
#include <math.h>

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

    theta_2 = (PI/2 + acos(-b));   // pi/2+acosb

    theta_3 = PI/2 + theta_e - theta_1 - theta_2;

    return 0;
}

int main() {
    FILE *fptr_in, *fptr_out;
    
    // Open file with coordinates (already generated)
    fptr_in = fopen("datafiles/Coordinates_values.txt", "r");
    if (!fptr_in) {
        perror("Error opening input file");
        return 1;
    }

    fptr_out = fopen("datafiles/Angles_values.txt", "w");
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
    
    fclose(fptr_in);
    fclose(fptr_out);

    return 0;
}
