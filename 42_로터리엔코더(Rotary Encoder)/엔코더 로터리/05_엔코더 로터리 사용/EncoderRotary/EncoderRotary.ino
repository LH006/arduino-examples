int swPin = 2;  // 로터리 엔코더 푸쉬 버튼
int dtPin = 3;  // 로터리 엔코더 dtPin
int clkPin = 4; // 로터리 엔코더 clkPin

int count = 0;  // 로터리 엔코더 회전 정도를 숫자로 표시하기 위한 변수

void setup() {
  pinMode(swPin, INPUT_PULLUP);   // 엔코더 푸쉬버튼, 풀업 입력으로 설정
  pinMode(clkPin, INPUT_PULLUP);  // 엔코더 CLK핀, 풀업 입력으로 설정
  pinMode(dtPin, INPUT_PULLUP);   // 엔코더 DT핀, 풀업 입력으로 설정

  // DT핀을 외부인터럽터로 설정, 
  // 상승엣지(RISING) 모드, 인터럽트가 발생하면 direcSensing()함수 실행
  attachInterrupt(digitalPinToInterrupt(dtPin), direcSensing, RISING);
  
  Serial.begin(9600);
  Serial.println("- 엔코더 로터리 측정 시작 -");
  Serial.println(count);
}

void loop() {
  if(!digitalRead(swPin)){  // 엔코더 로터리가 눌려지면 실행(swPin = LOW)
    count=0; Serial.println(count);  // 카운트 값 리셋
    delay(1000);
  }
}

void direcSensing() {
  if (digitalRead(clkPin) == LOW) { // 시계방향 회전이라면
    count++;
  } else{            // 반시계방향 회전이라면
    count--;
  }
  Serial.println(count);
}
