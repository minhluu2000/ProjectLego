# Project LeGO
 A League of Legends authentication device, LeGO stands for League Go which basically means I just need a fancy name to make it cool for people who browse my GitHub (which is none). This project began when I was annoyed about having to search for League shortcut and then enter the credentials manually every day. Inspired by Windows smart card readers, I decided to design an RFID reader with clapping as the main way to initiate authentication process.

 LeGO can be run on Arduino Uno or Arduino Nano (I could only test on the MEGA328P because those boards were all I had) and I can't guarantee this would work with every Arduino board. I tested the Python code on both Python 3.7.7 and 3.8.3, but please feel free to modify the code to suit your own version. 

# Schematic
 The included Arduino code contains the pin layout for connecting the RFID sensor to different Arduino boards. This code is based on the [André Balboa's RFID Library](https://github.com/miguelbalboa/rfid) that is relatively easy to understand. The way you connect a sound sensor is also very simple as it only has a single output pin and the standard Vcc and Ground pins that can be connected to the 5V source straight from the Arduino Nano.

# How to install
 1. Load the Arduino code on the board using the Arduino IDE. Make sure you check all the pins with the ones written in the code.
 2. Install the requirements for python using the [requirements.txt file](https://pip.pypa.io/en/stable/user_guide/).
 3. Fill in your credentials in the login.json file as well as the RFID UID of any standard RFID card. If you want to know what the UID is of your card, after assemble the RFID reader with the Arduino, just use the RFID Library to load the dumpinfo sketch (check André GitHub for information).
 4. Check your client location and fill in that information at the place I commented in the main.py file.
 5. You can run directly the main.py file or you can run as an administrator with the main.bat file. You can also run it hidden by changing the .py file to .pyw. If you want this program to run at start, you can use Windows Task Scheduler.
 6. Demo video [here](https://youtu.be/tXQVPJi9RLs).

# Credits
 1. Thank you André for his simple-to-use RFID Library.
 2. Thank you dethi for your guidance on how to use the Riot Client API. This is also a huge thanks to the Riot Games Dev Community Discord.
 3. Thank you to [Carlos Trejo](https://github.com/CarlosGTrejo) for his tremendous help throughout the project.
