# Project LeGO
 A League of Legends authentication device, LeGO stands for League Go which basically means I just need a fancy name to make it cool for people who browse my GitHub (which is none). This project began when I was annoyed about having to search for League shortcut and then enter the credentials manually every day. Inspired by Windows smart card readers, I decided to design an RFID reader with clapping as the main way to initiate authentication process.

 LeGO can be run on Arduino Uno or Arduino Nano (I could only test on the MEGA328P because those boards were all I had) and I can't guarantee this would work with every Arduino board. I tested the Python code on both Python 3.7.7 and 3.8.3, but please feel free to modify the code to suit your own version. 

# Schematic
 The included Arduino code contains the pin layout for connecting the RFID sensor to different Arduino board. This code is based on the [André Balboa's RFID Library](https://github.com/miguelbalboa/rfid) that is relatively easy to understand. The way you connect a sound sensor is also very simple as it only has a single output pin and the standard Vcc and Ground pins that can be connected to the 5V source straight from the Arduino Nano.

