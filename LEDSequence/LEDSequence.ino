const int lowestPin = 2;  // First LED pin
const int highestPin = 9; // Last LED pin
const int potPin = A0;    // Potentiometer connected to A0

void setup() {
    for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
        pinMode(thisPin, OUTPUT);
    }
}

void loop() {
    int potValue = analogRead(potPin);   // Read potentiometer value (0-1023)
    int delayTime = map(potValue, 0, 1023, 10, 500); // Map value to 10-500ms range

    // LED Chase Forward
    for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
        digitalWrite(thisPin, HIGH);
        delay(delayTime);
    }

    // LED Chase Backward (Turning off)
    for (int thisPin = highestPin; thisPin >= lowestPin; thisPin--) {
        digitalWrite(thisPin, LOW);
        delay(delayTime);
    }

    // LED Chase Backward (Turning on)
    for (int thisPin = highestPin; thisPin >= lowestPin; thisPin--) {
        digitalWrite(thisPin, HIGH);
        delay(delayTime);
    }

    // LED Chase Forward (Turning off)
    for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
        digitalWrite(thisPin, LOW);
        delay(delayTime);
    }
}
