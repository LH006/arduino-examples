# [HAL] DAC
### (Digital to Analog Converter)

### [사용법]
* https://jeonhj.tistory.com/m/34



#### [12bit DAC 모듈]
* 0부터 Vref+ 에 인가된 전압을 4096(2^12)개로 쪼개어 출력으로 보냅
* VREF: VREF+ 핀에 인가된 전압
* DOR: Data Output Register로 여기에 0~4095값이 쓰여짐

# [예제]
#### [Vref+ 가 3.3V일 경우]
* 3.3*1 / 4095 = 0.000806
* Digital Value 1당 0.000806V가 출력



```C++
HAL_StatusTypeDef HAL_DAC_Start(DAC_HandleTypeDef *hdac, uint32_t Channel);
// DAC Output Enable 함수
// hdac: dac 인스턴스
// Channel: DAC_CHANNEL_1 or DAC_CHANNEL_2

HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef *hdac, uint32_t Channel);
// DAC Output Disable 함수
// hadc: dac 인스턴스
// Channel: DAC_CHANNEL_1 or DAC_CHANNEL_2

HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Alignment, uint32_t Data);
// DAC Value 설정 함수
// hadc: dac 인스턴스
// Channel: DAC_CHANNEL_1 or DAC_CHANNEL_2
// Alignment: DAC_ALIGN_12B_R or DAC_ALIGN_12B_L or DAC_ALIGN_8B_R
// data: 0 ~ 4095 값
```