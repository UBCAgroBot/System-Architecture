# Can also just run "echo "Hello Arduino" > /dev/ttyACM0" in terminal

import serial
import time

port = "/dev/ttyACM0" # Change if needed
baud = 9600

print(f"Opening {port}...")
try:
    # Opening the port triggers a hardware reset on the Arduino
    arduino = serial.Serial(port, baud, timeout=1)
    time.sleep(2) # Wait for it to wake up

    print("Sending data... Watch the RX light on the Arduino!")
    for i in range(5):
        arduino.write(b"Test Message\n")
        print(f"Sent message {i+1}")
        time.sleep(0.5) # Wait half a second between blinks

    arduino.close()
    print("Test complete.")
except Exception as e:
    print(f"Failed: {e}")