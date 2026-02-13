
int buttonState = 0;         // variable for reading the pushbutton status
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin


byte portStatus[TOTAL_PORTS]; // each bit: 1=pin is digital input, 0=other/ignore
byte previousPINs[TOTAL_PORTS];

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(3, INPUT_PULLUP); //조이스틱에 달린(가운데버튼) 스위치 핀설정입니다.
  pinMode(ledPin, OUTPUT);
}

void loop() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
  
  int sensorValue = analogRead(A0);
  delay(1);        // delay in between reads for stability
}
