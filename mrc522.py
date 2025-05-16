import serial
import time

# Set the serial port and baud rate
PORT = 'COM5'            # Adjust as needed (e.g., 'COM3', '/dev/ttyUSB0')
BAUD_RATE = 9600         # Default baud rate for MFRC522 UART mode

def send_at_command(command, delay=0.5):
    """
    Sends an AT command to the serial port and returns the response.
    """
    ser.write(b'AT+ID\r\n')  # Send command with CRLF
    time.sleep(delay)
    response = ser.read_all().decode('utf-8', errors='ignore').strip()
    return response

try:
    # Open serial port
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {PORT} at {BAUD_RATE} baud.")
    while True:
        # Loop to read RFID or other UART responses
        line = ser.readline()
        if line:
            tag_data = line.decode('utf-8', errors='ignore').strip()
            if tag_data == "+TAG:1":
                at_response = send_at_command("AT+RID")
                print(f"AT Command Response: {at_response}")

except serial.SerialException as e:
    print(f"Failed to open serial port {PORT}: {e}")
    raise SystemExit

except KeyboardInterrupt:
    print("Stopped by user.")

finally:
    if ser.is_open:
        ser.close()
