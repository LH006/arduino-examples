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