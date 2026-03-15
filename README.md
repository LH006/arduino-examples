[Arduino] 예제)
==========================

# 즐겨찾기
- [C언어 Web 연습 실행](https://www.mycompiler.io/ko/online-c++-compiler)
- [링크3] ([sources](doc/installing.rst#using-git-version))

# Arduino project
*

# Contents
  * 내용 목록
- 설명문:
  - [내용1](#Contents-1) - 공백표시
  - [내용2](#Contents-2)
  - [내용3](#using-platformio)
  - [내용4](#building-with-make)
- [내용5](#documentation)
- [내용6](#issues-and-support) 

---
# 예제1)

### Contents 2
---
#### [LED 횟수]
```Cpp
const int ledPin = 13;      // LED 핀 번호
unsigned long previousMillis = 0; // 마지막 동작 시간 저장
const long interval = 500;  // 깜빡임 간격 (0.5초)

int blinkCount = 0;         // 남은 깜빡임 횟수
int ledState = LOW;         // LED 현재 상태

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 예시: 특정 조건에서 5회 깜빡임 명령을 내림
  if (millis() % 10000 == 0) { // 10초마다 5번 깜빡이게 설정 (예시 조건)
    startBlink(5);
  }

  updateBlink(); // 루프 내내 체크하며 깜빡임 실행
}

// 깜빡임 횟수를 설정하는 함수
void startBlink(int count) {
  if (blinkCount == 0) { // 이미 동작 중이 아닐 때만 설정
    blinkCount = count * 2; // 켜고 끄는 게 한 세트이므로 2배
  }
}

// delay 없이 LED 상태를 업데이트하는 함수
void updateBlink() {
  if (blinkCount > 0) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // 시간 업데이트

      // LED 상태 반전
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
        blinkCount--; // 한 번 켜졌다가 꺼질 때 횟수 차감
      }
      digitalWrite(ledPin, ledState);
    }
  }
}
```