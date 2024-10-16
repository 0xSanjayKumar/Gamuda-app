import streamlit as st
import serial
import time
from PIL import Image

# Connect to the Arduino (adjust COM port and baud rate as needed)
ser = serial.Serial('COM3', 9600)
time.sleep(2)  # Wait for the connection to be established

st.title("Arduino-Controlled Streamlit App")

# Placeholder for the image
image_placeholder = st.empty()

# Pre-load images for different stop points
image_1 = Image.open("image_1.png")  # Replace with your image paths
image_2 = Image.open("image_2.png")
image_3 = Image.open("image_3.png")

# Function to update the image based on stop_count from Arduino
def update_image():
    while True:
        if ser.in_waiting > 0:
            stop_count = ser.readline().decode().strip()
            st.write(f"Stop count received: {stop_count}")
            if stop_count == "1":
                image_placeholder.image(image_1, caption="Stop Point 1")
            elif stop_count == "2":
                image_placeholder.image(image_2, caption="Stop Point 2")
            elif stop_count == "3":
                image_placeholder.image(image_3, caption="Stop Point 3")
            time.sleep(1)  # Adjust delay as needed

# Start the update_image function
if st.button("Start Arduino Program"):
    update_image()
