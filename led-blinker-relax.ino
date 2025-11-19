/*
  Button-switchable single LED blinker
   7.421Hz (relaxing, theta)
   18.55Hz (activity, upper-mid beta)


*/
int LED_PIN = 8;
int BUTTON_PIN = 7;

namespace MODES {
  constexpr double RELAX = 67.375; //7.421HZ or period of 134.75ms, or 67.375 msec half cycle
  constexpr double ACTIVITY = 26.955; //18.55HZ or period of 53.91ms, or 26.955 msec half cycle
};
double mode;
int buttonState;
int lastButtonState;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  mode = MODES::RELAX;
}

void switchMode() {
  if (mode == MODES::RELAX) {
    mode = MODES::ACTIVITY;
  } else {
    mode = MODES::RELAX;
  }
}

// the loop function runs over and over again forever
void loop() {
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_PIN, HIGH); //150 OHM absolute minimum series with LED, with an inlined 1k pot for brightness.
  delay(mode);                       // wait for half period
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_PIN, LOW);                 
  delay(mode);                       // wait for half period
  
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState && buttonState == LOW) {
    switchMode();
  }
  lastButtonState = buttonState;
}
