import streamlit as st
import serial
import time
from PIL import Image

ser = serial.Serial('COM3', 9600)
time.sleep(2) 

st.title("Arduino-Controlled Streamlit App")

# Button to start the Arduino program
if st.button("Start Arduino Program"):
    st.success("Arduino Program Started")

image_placeholder = st.empty()

# Pre-load images
image_1 = Image.open("image_1.png")  
image_2 = Image.open("image_2.png")

def update_image():
    while True:
        if ser.in_waiting > 0:
            arduino_input = ser.readline().decode().strip()
            if arduino_input == "1":
                image_placeholder.image(image_1, caption="Condition 1")
            elif arduino_input == "2":
                image_placeholder.image(image_2, caption="Condition 2")
            time.sleep(1)  # Adjust the delay as needed

update_image()
