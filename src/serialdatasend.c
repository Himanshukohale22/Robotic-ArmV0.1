#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {
    // Open the serial port
    int serial_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd < 0) {
        perror("Error opening serial port");
        return 1;
    }

    // Configure serial port (115200 8N1)
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("tcgetattr error");
        return 1;
    }

    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    tty.c_iflag &= ~IGNBRK;                     // disable break processing
    tty.c_lflag = 0;                            // no signaling chars, no echo
    tty.c_oflag = 0;                            // no remapping, no delays
    tty.c_cc[VMIN]  = 1;                        // read blocks
    tty.c_cc[VTIME] = 1;
    tty.c_cflag |= (CLOCAL | CREAD);            // ignore modem controls, enable reading
    tty.c_cflag &= ~(PARENB | PARODD);          // no parity
    tty.c_cflag &= ~CSTOPB;                     // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                    // no flow control

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr error");
        return 1;
    }

    // Open your data file
    FILE *fptr = fopen("datafiles/coordinates_values.txt", "r");
    if (fptr == NULL) {
        perror("Error opening data file");
        return 1;
    }

    // Skip header line
    char header[256];
    fgets(header, sizeof(header), fptr);

    // Variables for each column
    double xe, ye, ze, theta_e, theta_0, theta_1, theta_2, theta_3;
    char buffer[256];

    // Read rows and send
    while (fscanf(fptr, "%lf %lf %lf %lf %lf %lf %lf %lf",
                  &xe, &ye, &ze, &theta_e, &theta_0, &theta_1, &theta_2, &theta_3) == 8) {

        // Format data as CSV line
        int n = snprintf(buffer, sizeof(buffer),
                         "%.2f,%.2f,%.2f,%.6f,%.6f,%.6f,%.6f,%.6f\n",
                         xe, ye, ze, theta_e, theta_0, theta_1, theta_2, theta_3);

        // Send over serial
        write(serial_fd, buffer, n);

        // For debug
        printf("Sent: %s", buffer);
        usleep(100000); // 100ms delay between lines (adjust as needed)
    }

    fclose(fptr);
    close(serial_fd);
    return 0;
}
