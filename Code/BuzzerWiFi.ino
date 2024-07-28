// include libraries 
#include <esp_now.h>
#include <WiFi.h> 

// variables 
int int_value; 

// setting up the variables for buzzer buttons 
#define Button1 16 
#define Button2 17
#define Button3 18
#define Button4 19
const int ledPin = 5; 

// variable for storing the button status 
int stateButton1 = 0;
int stateButton2 = 0;
int stateButton3 = 0;
int stateButton4 = 0;

bool press1 = false; 
bool press2 = false; 
bool press3 = false; 
bool press4 = false; 

// MAC address of main 
uint8_t broadcastAddress[] = {0xFC, 0xB4, 0x67, 0x74, 0x2F, 0x0C}; 

// data structure
typedef struct buttonpress {
  String button; 
} buttonpress;

// create a structured object 
buttonpress myData; 

// peer info 
esp_now_peer_info_t peerInfo; 

// callback functionfor when data is sent 
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t"); 
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// callback functions when data is received
void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
  const uint8_t* mac = recv_info->src_addr; 
  memcpy(&myData, incomingData, sizeof(myData));

  if (myData.button == "clear") {
    clearButtons(); 
  }
}

void clearButtons () {
  press1 = false; 
  Serial.print("Button 1: ");
  Serial.println(press1);
  press2 = false; 
  Serial.print("Button 2: ");
  Serial.println(press2);
  press3 = false; 
  Serial.print("Button 3: ");
  Serial.println(press3);
  press4 = false; 
  Serial.print("Button 4: ");
  Serial.println(press4);
}

void setup() {
  Serial.begin(115200); 
  WiFi.mode(WIFI_STA);

  // initializing the button pins as input 
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);
  pinMode(Button4, INPUT);
  pinMode(ledPin, OUTPUT);w

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
  memcpy(peerInfo.peer_addr, broadcastAddress, 6); 
  peerInfo.channel = 0;
  peerInfo.encrypt = false; 

  // add peer 
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  stateButton1 = digitalRead(Button1);
  stateButton2 = digitalRead(Button2);
  stateButton3 = digitalRead(Button3);
  stateButton4 = digitalRead(Button4);

  if (stateButton1 == HIGH && press1 == false) {
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println("Button1");
    myData.button = "A1";
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    press1 = true; 
    
  }
  else if (stateButton2 == HIGH && press2 == false) {
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println("Button2");
    myData.button = "B1";
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    press2 = true; 
  } 
  else if (stateButton3 == HIGH && press3 == false) {
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println("Button3");
    myData.button = "C1";
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    press3 = true; 
  }
  else if (stateButton4 == HIGH && press4 == false) {
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println("Button4");
    myData.button = "D1";
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    press4 = true; 
  }
  else {
    // turn LED off
    digitalWrite(ledPin, LOW);
    stateButton1 = 0;
    stateButton2 = 0;
    stateButton3 = 0;
    stateButton4 = 0;
  }

  //if (result == ESP_OK) {
  //  Serial.println("Sent");
  //}
  //else {
  //  Serial.println("Didn't go through");
  //}

}
