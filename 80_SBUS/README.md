[Arduino] 예제)
==========================

# 즐겨찾기
- [네이버 카페](https://cafe.naver.com/lsg20004/954)

# Arduino project
*

# 내용 목록
-
-

---
# 소스

#### []
```Cpp
#include "SBUS.h"
// 먼저 SBUS 라이브러리의 헤더를 추가해줍니다.
// SBUS가 아두이노의 serial1 rx에 연결되어있다고 선언합니다.
// 이는 아두이노마다 다르게 설정될 수 있습니다.
SBUS x8r(Serial1);
// 채널 수, failsafe, 손실 프레임에 대한 변수 선언입니다.
uint16_t channels[16];
bool failSafe;
bool lostFrame;

void setup() {
  // SBUS 통신을 시작합니다.
  x8r.begin();
}

void loop() {
  // 수신기로부터 SBUS패킷이 들어왔는지 확인합니다.
  if(x8r.read(&channels[0], &failSafe, &lostFrame)){
    x8r.write(&channels[0]);
  }
}
```
