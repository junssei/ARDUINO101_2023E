#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();       // initialize the LCD
  lcd.clear();      // clear the LCD display
  lcd.backlight();  // Make sure backlight is on
  Serial.begin(9600);  // Start serial communication at 9600 baud rate

  // Print a message on both lines of the LCD.
  lcd.setCursor(2, 0);  //Set cursor to character 2 on line 0
  lcd.print("Water Sensor");
}

void loop() {
  int value = analogRead(A0);  // Reading the analog value from pin A0
  lcd.setCursor(7, 1);
  lcd.print(value);  // Read the analog value of the sensor and print it to the serial monitor
  lcd.print("   "); // Displaying empty spaces to clear previous characters
}