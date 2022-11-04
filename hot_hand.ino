#define DIOD 14
#define BLUE 2
#define PIN_YL63 5

// Данные с датчика Y63
#define barrier digitalRead(PIN_YL63)

void setup() {
  pinMode(DIOD, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(PIN_YL63, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (barrier == LOW) {
    digitalWrite(DIOD, HIGH);
  } else {
    digitalWrite(DIOD, LOW);
  }
   Serial.println(barrier);
}
