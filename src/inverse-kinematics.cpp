#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>

#define PI 3.141592654
#define L1 120   // scaled length in pixels
#define L2 120
#define L3 60

using namespace cv;
using namespace std;

Point2i get_point(Point2i base, double angle, double length) {
    return Point2i(
        base.x + (int)(length * cos(angle)),
        base.y - (int)(length * sin(angle))  // minus because y grows downward in OpenCV
    );
}

int main() {
    // Target end-effector pose
    double xe = 100.0, ye = 200.0, ze = 0.0;
    double theta_e = 0; // 45° end-effector orientation

    // Inverse kinematics
    double xw = xe - (L3 * cos(theta_e));
    double yw = ye - (L3 * sin(theta_e));
    double r  = sqrt(xw*xw + yw*yw );

    double a = (L1*L1 + r*r - L2*L2) / (2.0 * L1 * r);
    double b = (L1*L1 + L2*L2 - r*r) / (2.0 * L1 * L2);

    // if (a>1) a=1; if (a<-1) a=-1;
    // if (b>1) b=1; if (b<-1) b=-1;

    double theta0 = atan2(ze, xe);
    double theta1 = atan2(yw, xw) + acos(a);
    double theta2 = -(PI - acos(b));
    double theta3 = theta_e - theta1 - theta2;
    
    cout << "xe=" << xe << " ye=" << ye
         << " Theta2=" << theta2 << " theta_e=" << theta_e << \n  <<  endl;


    cout << "Theta0=" << theta0 << " Theta1=" << theta1
         << " ze=" << ze << " Theta3=" << theta3  <<  endl;

    // Visualization
    Mat canvas(500, 500, CV_8UC3, Scalar(255,255,255));
    Point2i base(250, 400);

    // Joint positions
    Point2i joint1 = get_point(base, theta0, L1);
    Point2i joint2 = get_point(joint1, theta0+theta1, L2);
    Point2i endEff = get_point(joint2, theta0+theta1+theta2, L3);

    // Draw links
    line(canvas, base, joint1, Scalar(0,0,255), 4);
    line(canvas, joint1, joint2, Scalar(0,255,0), 4);
    line(canvas, joint2, endEff, Scalar(255,0,0), 4);

    // Draw joints
    circle(canvas, base, 5, Scalar(0,0,0), FILLED);
    circle(canvas, joint1, 5, Scalar(0,0,0), FILLED);
    circle(canvas, joint2, 5, Scalar(0,0,0), FILLED);
    circle(canvas, endEff, 5, Scalar(0,0,255), FILLED);

    // Show
    imshow("3-Link Manipulator", canvas);
    waitKey(0);
    return 0;
}
