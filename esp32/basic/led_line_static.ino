// Pin definitions for LEDs
const int ledPins[] = {2, 4, 5, 18, 19}; // GPIO pins for 5 LEDs
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Number of LEDs
const int delayTime = 200; // Delay in milliseconds between LED changes

void setup() {
  // Initialize LED pins as OUTPUT
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Turn off all LEDs initially
  }
}

void loop() {
  // Move line from first LED to last LED
  for (int i = 0; i < numLeds; i++) {
    setLedState(i, true);  // Turn on current LED
    delay(delayTime);      // Wait for some time
    setLedState(i, false); // Turn off current LED
  }
  
  // Move line from last LED back to the first LED
  for (int i = numLeds - 2; i > 0; i--) {
    setLedState(i, true);  // Turn on current LED
    delay(delayTime);      // Wait for some time
    setLedState(i, false); // Turn off current LED
  }
}

// Function to control a specific LED
void setLedState(int index, bool state) {
  digitalWrite(ledPins[index], state ? HIGH : LOW);
}
