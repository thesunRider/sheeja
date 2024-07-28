import serial
import threading
import time
import socket
import binascii


socktcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
socktcp.connect(('10.0.2.15', 1273))  

# Serial port configuration
SERIAL_PORT = 'COM7'  # Change this to your port (e.g., '/dev/ttyUSB0' on Linux)
BAUD_RATE = 115200
READ_TIMEOUT = 1  # 1 second timeout

# Initialize serial port
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=READ_TIMEOUT)

# Function to read data from serial port
def read_serial():
    while True:
        try:
            data = ser.read(3000)
            if data:
               socktcp.sendall(data)
        except serial.SerialException as e:
            print("Serial exception:", e)
            break
        except KeyboardInterrupt:
            print("Keyboard interrupt")
            break

# Create and start a background thread for reading serial data
read_thread = threading.Thread(target=read_serial, daemon=True)
read_thread.start()

# Main loop or other operations
try:
    while True:
        # Perform other tasks in the main thread
        pass
except KeyboardInterrupt:
    print("Stopping serial read...")
    ser.close()
