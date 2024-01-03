// Pin definitions
const int redPin = 9;     // Connect the red pin of RGB LED to digital pin 9
const int greenPin = 10;  // Connect the green pin of RGB LED to digital pin 10
const int bluePin = 11;   // Connect the blue pin of RGB LED to digital pin 11

const int buttonPins[] = { 2, 3, 4, 5, 6 };  // Button pins

const int buzzerPin = 12;  // Connect the buzzer to digital pin 7

void setup() {
  // Initialize RGB LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize button pins as inputs with internal pull-ups
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Initialize buzzer pin as output
  pinMode(buzzerPin, OUTPUT);

  // Beep the buzzer for 3 seconds
  beepBuzzer(3000);

  // Turn on and off all LEDs
  controlLEDs(1, 1, 1);  // Turn on all LEDs
  delay(2000);
  controlLEDs(0, 0, 0);  // Turn off all LEDs
}

void loop() {
  // Check button states and perform actions
  if (digitalRead(buttonPins[0]) == LOW) {         // Button 1 pressed
    controlLEDs(1, 1, 0);                          // Yellow
  } else if (digitalRead(buttonPins[1]) == LOW) {  // Button 2 pressed
    controlLEDs(1, 0, 1);                          // Magenta
  } else if (digitalRead(buttonPins[2]) == LOW) {  // Button 3 pressed
    controlLEDs(1, 1, 1);                          // White
  } else if (digitalRead(buttonPins[3]) == LOW) {  // Button 4 pressed
    blinkAllLEDs();
  } else if (digitalRead(buttonPins[4]) == LOW) {  // Button 5 pressed
    controlLEDs(0, 0, 0);                          // Turn off all LEDs
  }
}

// Function to control RGB LED using digital signals
void controlLEDs(int red, int green, int blue) {
  digitalWrite(redPin, red);
  digitalWrite(greenPin, green);
  digitalWrite(bluePin, blue);
}

// Function to blink all LEDs in a loop
void blinkAllLEDs() {
  for (int i = 0; i < 5; i++) {
    controlLEDs(0, 0, 0);  // no light
    delay(500);
    controlLEDs(0, 0, 1);  // blue
    delay(500);
    controlLEDs(0, 1, 0);  // green
    delay(500);
    controlLEDs(0, 1, 1);  // cyan
    delay(500);
    controlLEDs(1, 0, 0);  // red
    delay(500);
    controlLEDs(1, 0, 1);  // magenta
    delay(500);
    controlLEDs(1, 1, 0);  // yellow
    delay(500);
    controlLEDs(1, 1, 1);  // Red
    delay(500);
  }
}

// Function to beep the buzzer for a specified duration
void beepBuzzer(int duration) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration);
  digitalWrite(buzzerPin, LOW);
}
