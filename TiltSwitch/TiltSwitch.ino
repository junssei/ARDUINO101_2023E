#define TILT_SWITCH_PIN 12  // Define the pin connected to the tilt switch
#define LED_PIN 13         // Built-in LED on Arduino

void setup() {
    pinMode(TILT_SWITCH_PIN, INPUT_PULLUP);  // Use internal pull-up resistor
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);  // Initialize serial monitor
}

void loop() {
  int tiltState = digitalRead(TILT_SWITCH_PIN);  // Read the tilt switch state

  if (tiltState == LOW) {  // Tilt switch is activated (closed circuit)
      digitalWrite(LED_PIN, HIGH);  // Turn on LED
      Serial.println("Tilt Detected! LED ON");
  } else {
      digitalWrite(LED_PIN, LOW);  // Turn off LED
      Serial.println("No Tilt. LED OFF");
  }
  delay(100);  // Small delay for stability
}