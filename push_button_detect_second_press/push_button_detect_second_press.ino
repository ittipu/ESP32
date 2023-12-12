#define BUTTON_PIN 13  // GPIO21 pin connected to button

// Variables will change:
int lastState = HIGH;  // the previous state from the input pin
int currentState;      // the current reading from the input pin
int press_time = 0;
void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  if (lastState == LOW && currentState == HIGH) {
    Serial.println("The state changed from LOW to HIGH");
    press_time++;
    if (press_time == 1) {
      Serial.println("1");
    }
    if (press_time == 2) {
      Serial.println("2");
      press_time = 0;
    }
  }
  // save the last state
  lastState = currentState;
}