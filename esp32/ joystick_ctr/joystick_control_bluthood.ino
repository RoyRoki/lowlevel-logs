#include <BluetoothSerial.h>

BluetoothSerial ESP_BT;  // Create BluetoothSerial object

const int joystick_x_pin = A0;
const int joystick_y_pin = A3;
const int joystick_sw_pin = 4;

void setup() {
  Serial.begin(115200);  // Start serial communication with PC for debugging
  pinMode(joystick_sw_pin, INPUT_PULLUP);
  ESP_BT.begin("ESP32_Joystick");  // Start Bluetooth with device name "ESP32_Joystick"
  Serial.println("Bluetooth Device is ready to pair!");
}

void loop() {
  int x_adc_val = analogRead(joystick_x_pin);
  int y_adc_val = analogRead(joystick_y_pin);
  int sw_state = digitalRead(joystick_sw_pin);

  // Convert ADC values to voltage (optional)
  float x_volt = (x_adc_val * 3.3) / 4095;
  float y_volt = (y_adc_val * 3.3) / 4095;

  // Print joystick data to Bluetooth serial
  String joystick_data = String(x_volt) + "," + String(y_volt) + "," + String(sw_state);
  ESP_BT.println(joystick_data);  // Send joystick data over Bluetooth

  delay(100);  // Small delay to prevent spamming data
}
