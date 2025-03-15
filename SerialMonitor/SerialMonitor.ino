String input;
const int LED1 = 2; 
const int LED2 = 3; 
const int LED3 = 4; 

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW); 
  digitalWrite(LED3, LOW);

  Serial.println("Please input any color of LED:");
}

void loop() {
  while(Serial.available()) {
    input = Serial.readString();// read the incoming data as string

    input.toLowerCase();
    if(input == "green"){
      if(digitalRead(LED3)){
        Serial.println("Green is turned off");
        digitalWrite(LED3, LOW);
      } else {
        Serial.println("Green is turned on");
        digitalWrite(LED3, HIGH);
      }
    }
    
    if (input == "blue"){
      if(digitalRead(LED2)){
        digitalWrite(LED2, LOW);
        Serial.println("Blue is turned off");
      } else {
        digitalWrite(LED2, HIGH);
        Serial.println("Blue is turned on");
      }
    }
    
    if (input == "yellow"){
      if(digitalRead(LED1)){
        digitalWrite(LED1, LOW);
        Serial.println("Yellow is turned off");
      } else {
        digitalWrite(LED1, HIGH);
        Serial.println("Yellow is turned on");
      }
    }

    if(input == "off"){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW); 
      digitalWrite(LED3, LOW);
      Serial.println("All LEDs is turned off");
    } else if (input == "on"){
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH); 
      digitalWrite(LED3, HIGH);
      Serial.println("All LEDs is turned on");
    }

    Serial.println("Please input any color of LED:");
    delay(500);
  }
}