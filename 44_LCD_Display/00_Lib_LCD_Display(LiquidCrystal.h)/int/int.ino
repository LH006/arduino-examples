int AAA(int AA) {
  if (AA > 100) {
    AA = 1;
  } else {
    AA = 0;
  }
  return AA;
}

//=========================================
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Var : ");
  Serial.println(AAA(1000));
}
//========================================
