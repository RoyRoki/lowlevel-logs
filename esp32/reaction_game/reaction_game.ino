// Pin definitions
const int startBtn = 12;

const int seqLEDs[3] = {14, 27, 26};
const int userBtns[2] = {25, 33};
const int userLEDs[2] = {32, 4};

// States
bool gameStarted = false;
bool ledsCompleted = false;
bool userPressed[2] = {false, false};
bool userDisqualified[2] = {false, false};
int winner = -1;

void setup() {
  Serial.begin(115200);

  pinMode(startBtn, INPUT_PULLUP);

  for (int i = 0; i < 3; i++) pinMode(seqLEDs[i], OUTPUT);
  for (int i = 0; i < 2; i++) {
    pinMode(userBtns[i], INPUT_PULLUP);
    pinMode(userLEDs[i], OUTPUT);
  }

  resetGame();
}

void loop() {
  // Start/Reset Button Logic
  if (digitalRead(startBtn) == LOW) {
    delay(200); // Debounce
    resetGame();
    startGame();
  }

  // Monitor early presses before sequence completes
  if (gameStarted && !ledsCompleted && winner == -1) {
    for (int i = 0; i < 2; i++) {
      if (!userDisqualified[i] && digitalRead(userBtns[i]) == LOW) {
        userDisqualified[i] = true;
        Serial.print("User ");
        Serial.print(i + 1);
        Serial.println(" disqualified for early press!");
      }
    }
  }

  // Monitor valid presses after sequence completes
  if (gameStarted && ledsCompleted && winner == -1) {
    for (int i = 0; i < 2; i++) {
      if (!userPressed[i] && digitalRead(userBtns[i]) == LOW) {
        userPressed[i] = true;

        if (userDisqualified[i]) {
          Serial.print("User ");
          Serial.print(i + 1);
          Serial.println(" was already disqualified.");
          continue;
        }

        // Check if opponent is disqualified
        int opponent = (i == 0) ? 1 : 0;
        if (userDisqualified[opponent]) {
          winner = i;
        } else {
          winner = i;
        }

        digitalWrite(userLEDs[i], HIGH);
        Serial.print("User ");
        Serial.print(i + 1);
        Serial.println(" wins!");
      }
    }
  }

  // If one user disqualified and other hasn’t pressed, they win by default
  if (ledsCompleted && winner == -1 &&
      ((userDisqualified[0] && !userDisqualified[1]) || (!userDisqualified[0] && userDisqualified[1]))) {

    winner = userDisqualified[0] ? 1 : 0;
    digitalWrite(userLEDs[winner], HIGH);
    Serial.print("User ");
    Serial.print(winner + 1);
    Serial.println(" wins by disqualification!");
  }
}

void resetGame() {
  Serial.println("Resetting game...");

  gameStarted = false;
  ledsCompleted = false;
  winner = -1;

  for (int i = 0; i < 2; i++) {
    userPressed[i] = false;
    userDisqualified[i] = false;
    digitalWrite(userLEDs[i], LOW);
  }

  for (int i = 0; i < 3; i++) digitalWrite(seqLEDs[i], LOW);
}

void startGame() {
  gameStarted = true;

  for (int i = 0; i < 3; i++) {
    digitalWrite(seqLEDs[i], HIGH);
    delay(1000);
    digitalWrite(seqLEDs[i], LOW);
  }

  ledsCompleted = true;
  Serial.println("GO!");
}
