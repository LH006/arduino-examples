bool AAA(bool AA) {
  AA = false;
  //AA = true;
  return AA;
}

//=========================================
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Var : ");
  Serial.println(AAA(1));
}
//========================================
