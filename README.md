# Wireless-Buzzers
This project implements a wireless buzzer system for quiz or game setups, supporting 4 teams with 4 players each. The system utilizes 5 ESP32 development boards and communicates via the ESPNOW protocol, achieving a latency response time of approximately 2 milliseconds.

# Features
Support for 4 Teams: Each team can have up to 4 players.
Wireless Communication: Uses ESPNOW protocol for fast and efficient communication between the ESP32 boards.
Low Latency: Achieves a latency response time of ~2 milliseconds.
Reset Functionality: Includes a reset button to clear the buzzer states.

# Components
* 5 x ESP32 38pin Development Boards
    * https://www.aliexpress.com/item/32959541446.html?spm=a2g0o.order_list.order_list_main.79.56a61802KwvkZu 
* 4 x Push Buttons per Team & 1 x Reset Button (17 total)
    * https://www.aliexpress.com/item/4000097252595.html?spm=a2g0o.order_list.order_list_main.48.56a61802KwvkZu
* 1 x I2C 16x2 LCD Display
    * https://www.aliexpress.com/item/1005006100081942.html?spm=a2g0o.order_list.order_list_main.53.56a61802KwvkZu
* 5 Perf Boards
    * https://www.aliexpress.com/item/1005005795030364.html?spm=a2g0o.order_list.order_list_main.43.56a61802KwvkZu
* Connecting Wires
    * Buzzer wires: https://www.aliexpress.com/item/1005005586778126.html?spm=a2g0o.productlist.main.21.1bc23Mde3MdemM&algo_pvid=e1efc8fa-0c83-4f5d-94fd-0a4cd86bc16e&algo_exp_id=e1efc8fa-0c83-4f5d-94fd-0a4cd86bc16e-10&pdp_npi=4%40dis%21CAD%2138.18%2119.09%21%21%2127.02%2113.51%21%402103146c17221906930751028efd68%2112000033654655429%21sea%21CA%214143424543%21X&curPageLogUid=2Y4tKg5bDQtm&utparam-url=scene%3Asearch%7Cquery_from%3A
* Pin Sockets
    * https://www.aliexpress.com/item/1005005007385963.html?spm=a2g0o.order_list.order_list_main.73.56a61802KwvkZu
* 5 x Micro USB Data Cables
    * https://www.aliexpress.com/gcp/300000512/nnmixupdatev3?spm=a2g0o.productlist.main.15.3912WuUeWuUeYa&productIds=1005005758280774&pha_manifest=ssr&_immersiveMode=true&disableNav=YES&channelLinkTag=nn_newgcp&sourceName=mainSearchProduct&utparam-url=scene%3Asearch%7Cquery_from%3A 
* Wiring Diagram (included in the repo) 

# Installation
## Install the Required Libraries:
1. Clone the repository:
```
git clone https://github.com/yourusername/wireless-buzzer-system.git
```
2. Open the project in Arduino IDE or PlatformIO.
3. ESP-NOW: Available through the Arduino Library Manager.
4. WiFi: Included with the ESP32 core for Arduino.
5. LiquidCrystal_PCF8574: Available through the Arduino Library Manager.
6. Upload the Code to the ESP32 Boards:
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
