
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Tome Demo!");
  // Frequency: 10KHz, duration: 5s
  tone(D13, 10000, 5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
