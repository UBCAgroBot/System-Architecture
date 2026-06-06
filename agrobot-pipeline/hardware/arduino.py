import serial
import time
import struct

def init_arduino(port, baud_rate):
    try:
        arduino = serial.Serial(port, baud_rate, timeout=0.1)
        time.sleep(2)
        print("-"*40)
        print("✓ Arduino successfully connected!")
        print("-"*40 + "\n")
        return arduino
    except Exception as e:
        print(f"✗ Arduino connection failed: {e}")
        print("Continuing pipeline without Arduino...")
        return None

def send_arduino(arduino, camera_id, class_id, left, top):
    if arduino and arduino.is_open:
        # Remove int casting possibly

        # Possibly send extra data for specific class map to use within Arduino C++ code
        msg = struct.pack('>BBBHH', 0xFF, camera_id, class_id, int(left), int(top))
        try:
            arduino.write(msg)
            print(f">> [ARDUINO TX]: cam={camera_id} class={class_id} x={int(left)}, y={int(top)}")
        except Exception as e:
            print(f"Serial write error: {e}")