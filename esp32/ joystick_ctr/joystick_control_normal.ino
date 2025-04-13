#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad bleGamepad;

const int joystick_x_pin = A0;
const int joystick_y_pin = A3;
const int joystick_sw_pin = 4;

// Calibration values (using your readings)
const int x_center = 1840;
const int y_center = 1820;

void setup() {
  Serial.begin(115200);
  pinMode(joystick_sw_pin, INPUT_PULLUP);
  Serial.println("Starting BLE work!");
  bleGamepad.begin();
}

void loop() {
  if (bleGamepad.isConnected()) {
    int x_adc_val = analogRead(joystick_x_pin);
    int y_adc_val = analogRead(joystick_y_pin);
    int sw_state = digitalRead(joystick_sw_pin);

    // Apply Calibration and Scaling with Clamping
    int x_mapped = map(x_adc_val, 0, 4095, -32767, 32767);
    int y_mapped = map(y_adc_val, 0, 4095, -32767, 32767);

    // Center the values
    x_mapped -= map(x_center, 0, 4095, -32767, 32767);
    y_mapped -= map(y_center, 0, 4095, -32767, 32767);

    // Clamping to prevent values outside the valid range
    x_mapped = constrain(x_mapped, -32767, 32767);
    y_mapped = constrain(y_mapped, -32767, 32767);

    bleGamepad.setAxes(x_mapped, y_mapped, 0, 0, 0, 0, 0, 0);

    if (sw_state == LOW) {
      bleGamepad.press(BUTTON_1);
    } else {
      bleGamepad.release(BUTTON_1);
    }
  }
  delay(50); // Reduced delay for responsiveness
}