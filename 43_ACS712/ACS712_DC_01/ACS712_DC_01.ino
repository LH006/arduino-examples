/*  Arduino = DC전류값  ACS712 */
void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensor = analogRead(A0);
  int valordsaida = map(sensor, 0, 1023, -5, 5);
  Serial.print("Amperes: ");
  Serial.println(valordsaida);
  delay(100);
}


