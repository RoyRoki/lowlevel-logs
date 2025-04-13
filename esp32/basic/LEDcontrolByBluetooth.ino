
#include "BluetoothSerial.h"


// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;


// GPIO where LED is connected to
const int ledPin =  4;
// Handle received and sent messages
String message = "";
char incomingChar;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  // Bluetooth device name
  SerialBT.begin("ESP32"); //your mobile phone should detect this name, 'ESP32'
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
    // put your main code here, to run repeatedly:
  
  const char* myCString = "LED is ON";


  // Read received messages (LED control command)
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  // Check received message and control output accordingly
  if (message =="led_on"){
    digitalWrite(ledPin, HIGH);
    const char* myCString = "The LED is ON";
    // Iterate through each character in the C-string
    for (size_t i = 0; myCString[i] != '\0'; ++i) {
      uint8_t currentChar = static_cast<uint8_t>(myCString[i]);
      // Do something with the character (currentChar)
      SerialBT.write(currentChar);
      // For example, print the string:
      // Serial.print(currentChar);
}
  }
  else if (message =="led_off"){
    digitalWrite(ledPin, LOW);
    const char* myCString = "The LED is OFF";
    // Iterate through each character in the C-string
    for (size_t i = 0; myCString[i] != '\0'; ++i) {
      uint8_t currentChar = static_cast<uint8_t>(myCString[i]);
      // Do something with the character (currentChar)
      SerialBT.write(currentChar);
      // For example, print the string:
      Serial.print(currentChar);
  }
  delay(20);
}
}