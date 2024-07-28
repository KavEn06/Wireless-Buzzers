/*
  Main Buzzer Code
  ----------------
  This code runs on the main ESP32 development board in a wireless buzzer system designed for quiz or game setups. 
  It manages the central communication and control of the buzzer system, displaying the pressed buttons on an I2C 16x2 LCD display.
  The system supports 4 teams with 4 players each and uses the ESPNOW protocol for communication, achieving a latency 
  response time of approximately 2 milliseconds.

  Features:
  - Receives button press data from team buzzers
  - Displays the pressed buttons on an I2C 16x2 LCD
  - Manages the state of button presses to ensure correct game flow
  - Resets the system when the reset button is pressed

  Components:
  - 1 x ESP32 Development Board (Main Buzzer)
  - 1 x I2C 16x2 LCD Display
  - 1 x Push Button
  Author: Kavin Nimalarajan
*/

// include libraries
#include <esp_now.h>
#include <WiFi.h>
#include <LiquidCrystal_PCF8574.h>

// setting up the variables for reset button
#define reset 19

// variable for storing the button status
int statereset = 0;
int ind = 0; 
String buttons[4]; 
bool Apress = false; 
bool Bpress = false; 
bool Cpress = false; 
bool Dpress = false; 

// MAC address' of buzzers
uint8_t teamA[] = { 0xA8, 0x42, 0xE3, 0xBC, 0x72, 0xF8 }; // Change MAC address to suit your ESP32
uint8_t teamB[] = { 0xE4, 0x65, 0xB8, 0x79, 0x78, 0xB0 }; // Change MAC address to suit your ESP32
uint8_t teamC[] = { 0xA0, 0xA3, 0xB3, 0xAB, 0x84, 0x24 }; // Change MAC address to suit your ESP32
uint8_t teamD[] = { 0xE4, 0x65, 0xB8, 0x79, 0x82, 0xD0 }; // Change MAC address to suit your ESP32

// define I2C address for 16x2 LCD
#define I2C_ADDR 0x27
LiquidCrystal_PCF8574 lcd(I2C_ADDR);

// data structure
typedef struct buttonpress {
  String button;
} buttonpress;

// create a structured object
buttonpress myData;

// peer info
esp_now_peer_info_t peerInfo;

// callback function when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
// callback functions when data is received
void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
  const uint8_t* mac = recv_info->src_addr; 
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Data received: ");
  Serial.println(len);
  Serial.println("Button: ");
  Serial.println(myData.button);
  buttonSelect(myData.button); 
}

void buttonSelect(String button) {
  if (button[0] == 'A' && !Apress) {
    Apress = true; 
    buttons[ind] = button; 
    ind++;
  } 
  else if (button[0] == 'B' && !Bpress) {
    Bpress = true;
    buttons[ind] = button;
    ind++;
  }
  else if (button[0] == 'C' && !Cpress) {
    Cpress = true;
    buttons[ind] = button;
    ind++;
  }
  else if (button[0] == 'D' && !Dpress) {
    Dpress = true;
    buttons[ind] = button;
    ind++;
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Wire.begin();

  // initialize the LCD
  lcd.begin(16, 2);
  lcd.setBacklight(255); 

  // initializing the button pins as input
  pinMode(reset, INPUT);

  // initilize esp-now
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP_NOW");
    return;
  }

  // register received callback
  esp_now_register_recv_cb(OnDataRecv);

  // register send callback
  esp_now_register_send_cb(OnDataSent);

  // register peer
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // add buzzer A as peer 
  memcpy(peerInfo.peer_addr, teamA, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // add buzzer B as peer 
  memcpy(peerInfo.peer_addr, teamB, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // add buzzer C as peer 
  memcpy(peerInfo.peer_addr, teamC, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // add buzzer D as peer 
  memcpy(peerInfo.peer_addr, teamD, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  statereset = digitalRead(reset);

  lcd.setCursor(0, 0);
  lcd.print("Buttons:");

  String displayText = "";
  for (int i = 0; i < ind; i++) {
    displayText += buttons[i] + " ";
  }
  lcd.setCursor(0, 1);
  lcd.print(displayText); 

  if (statereset == HIGH) {
    myData.button = "clear";
    esp_now_send(0, (uint8_t *)&myData, sizeof(myData));
    ind = 0; 

    Apress = false; 
    Bpress = false; 
    Cpress = false; 
    Dpress = false; 

    for (int i = 0; i < 4; i++) {
      buttons[i] = "";
    }
  }

  delay(500);
  lcd.clear();
}
