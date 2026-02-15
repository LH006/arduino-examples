//#define _DEBUG

volatile short sVal;
volatile byte byArr[2];
int32_t frequency = 120000;
bool success = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
#ifdef _DEBUG /////////////////////////////////////////////////
  {
    Serial.print(frequency);
    delay(500);
  }
#endif /////////////////////////////////////////////////////////
  Serial.println("Test");
  delay(500);
}

