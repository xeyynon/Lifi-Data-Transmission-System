import serial
import numpy as np
from PIL import Image

# Define the serial port and baud rate
ser = serial.Serial('COM8', 9600, timeout=1)  # Adjust 'COM8' as per your setup

# Initialize an empty list to store the pixel data
image_data = []

# Number of pixels in the image (8x8 = 64 pixels)
image_size = 64

print("Receiving image data...")
while len(image_data) < image_size:
    if ser.in_waiting > 0:  # Check if data is available to read
        byte_data = ser.read(1)  # Read one byte from serial
        image_data.append(ord(byte_data))  # Convert byte to int and add to list

print("Image data received successfully.")

# Convert the received data to a numpy array and reshape to 8x8
image_data = np.array(image_data, dtype=np.uint8).reshape((8, 8))

# Create an image from the array
img = Image.fromarray(image_data, mode='L')  # 'L' mode for grayscale

# Display and save the image
img.show()  # Display the image
img.save('received_image.png')  # Save the image as a PNG file
