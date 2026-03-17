# [HAL] DAC
### (Digital to Analog Converter)
* ESP32 = 8bit 2개
   *
   *
* 

### [# 사용법]
* https://jeonhj.tistory.com/m/34

 
### [# DAC 분해 능력]
* 6비트 : 64 3.2V, 기준 50 mV
* 8비트: 256 (0~255)
* 10비트: 1024 (0~1023)
* 12비트: 4096 (0~4095(0x00000FFF))
   * 3.3V / 4096스텝 = 0.806mV(전압스텝)
   * 2048스탭 / 4096스텝 × 3.3V = 1.65V





#### [12bit DAC 모듈]
* 0부터 Vref+ 에 인가된 전압을 4096(2^12)개로 쪼개어 출력으로 보냅
* VREF: VREF+ 핀에 인가된 전압
* DOR: Data Output Register로 여기에 0~4095값이 쓰여짐





---
## [# 예제]

### [특정 전압 출력하기]
```c++
#include <driver/dac.h> // DAC 드라이버 포함

void setup() {
  // 25번 핀(DAC_CHANNEL_1) 활성화
  dac_output_enable(DAC_CHANNEL_1);
}

void loop() {
  // 1.65V 출력 (255의 절반인 127 설정)
  dac_output_voltage(DAC_CHANNEL_1, 127);
  delay(1000);

  // 3.3V 출력 (최대값 255)
  dac_output_voltage(DAC_CHANNEL_1, 255);
  delay(1000);
}
```

### [삼각파(Sawtooth) 만들기]
```c++
void loop() {
  for (int i = 0; i < 256; i++) {
    dac_output_voltage(DAC_CHANNEL_1, i);
    delayMicroseconds(100); // 이 간격으로 주파수 조절
  }
}

```

---
#### [Vref+ 가 3.3V, 4096 경우]
* 3.3V * 1 / 4095 = 0.000806
* Digital Value 1당 0.000806V가 출력
---
#### [DAC 채널 1의 출력을 2V로 설정]
* DOR: Data Output Register
* = 2V * 4095 / 3.3V 
* = 2481.82 ≒ 2482 
---
 
```c++
HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2482);
HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
```
