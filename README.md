# Wireless-Buzzers
This project implements a wireless buzzer system for quiz or game setups, supporting 4 teams with 4 players each. The system utilizes 5 ESP32 development boards and communicates via the ESPNOW protocol, achieving a latency response time of approximately 2 milliseconds.

# Features
Support for 4 Teams: Each team can have up to 4 players.
Wireless Communication: Uses ESPNOW protocol for fast and efficient communication between the ESP32 boards.
Low Latency: Achieves a latency response time of ~2 milliseconds.
Reset Functionality: Includes a reset button to clear the buzzer states.

# Components
* 5 x ESP32 Development Boards
* 4 x Push Buttons per Team
* 1 x Reset Button
* 1 x I2C 16x2 LCD Display
* Connecting Wires
* Wiring Diagram (included in the repo) 

# Installation
## Install the Required Libraries:
1. ESP-NOW: Available through the Arduino Library Manager.
2. WiFi: Included with the ESP32 core for Arduino.
3. LiquidCrystal_PCF8574: Available through the Arduino Library Manager.
4. Upload the Code to the ESP32 Boards:
    - Use the Arduino IDE to upload the Main.ino code to the main ESP32 board.
    - Ensure the correct board and port are selected in the Arduino IDE.

# Usage
* Power on the ESP32 Boards: Ensure all boards are powered on and within range.
* Press the Buzzer Buttons: Players can press their team’s buzzer buttons to send a signal to the main ESP32 board.
* View the Results: The main ESP32 board processes the signals and determines which button was pressed first, displaying the results on the LCD.
* Reset the System: Use the reset button to clear the buzzer states and start a new round.

# Contribution
Feel free to contribute to this project by opening issues or submitting pull requests.

# Upcoming 
* Python software that can be run on a computer, which controls the buzzers and displays the buttons pressed
    * Useful for projecting the buttons pressed to everyone participating
    * Allows for additional features to be implemented that the ESP32s can't do  
* PCB gerber files to make production easier

# License
Yuh student fr
