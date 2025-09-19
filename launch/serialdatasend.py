import pandas as pd 
import serial
import time

# Read file and buffer angles
df = pd.read_csv("/datafiles/Angles.txt", delim_whitespace=True)
angles_buffer = df[["theta_0", "theta_1", "theta_2", "theta_3"]].values.tolist()

# Setup serial
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
time.sleep(2)  # wait for Arduino reset

print("Starting handshake protocol...")

for row in angles_buffer:
    # Format as comma-separated values
    msg = ",".join(map(str, row)) + "\n"

    # Send packet
    ser.write(msg.encode('utf-8'))
    print("Sent:", msg.strip())

    # Wait for Arduino to confirm
    while True:
        if ser.in_waiting > 0:
            response = ser.readline().decode().strip()
            if response == "done":
                print("Arduino confirmed: done")
                break   # send next packet
