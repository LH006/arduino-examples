/* 기본 핀 배열
#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#define PIN_WIRE_SDA (4)
#define PIN_WIRE_SCL (5)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif
#define LED_BUILTIN_AUX 16

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;


A0 17;
S3
S2
S1
SC
S0
SK

RX
TX

Pin_SPI_HD 11
Pin_SPI_WP 12
////////////////////////////////////////////////////
* RST
* ADC0	//TOUT
  - 최대 입력전압 : 0~1V
* ENABLE
* GPIO0	//D3	//FLASH 버튼
  - LOW 시작시 부팅 실패
  - 풀업
* GPIO1	//TXD0
  - 부팅시 디버그 출력
  - LOW 시작시 부팅 실패
  - 부팅시 HIGH 신호 출력됨
* GPIO2	//D4	//TXD1	//LED보드
  - 풀업
  - LOW 시작시 부팅 실패
  - 부팅시 HIGH 신호 출력됨
* GPIO3	//RXD0
  - 부팅시 HIGH 신호 출력됨
* GPIO4	//D2	//SDA(I2C)
* GPIO5	//D1	//SCL(I2C)
* GPIO6	//SDCLK
* GPIO7	//SDD0	//RXD2
* GPIO8	//SDD1	//TXD2
* GPIO9	//SDD2
  - 부팅시 HIGH 신호 출력됨
* GPIO10	//SDD3
  - 부팅시 HIGH 신호 출력됨
* GPIO11	//SDCMD
* GPIO12	//D6	//H_MISO(SPI)
* GPIO13	//D7	//H_MOSI(SPI)	//RXD2
* GPIO14	//D5	//H_SCLK(SPI)
* GPIO15	//D8	//H_CS(SPI)	//TXD2
  - HIGH 시작시 부팅 실패
* GPIO16	//WAKE	//USER
  - PWM 안됨
  - I2C 안됨
  - 잠에서 깨우기 버튼
  - 부팅시 HIGH 신호 출력됨
* GPIO17


///////////////////////////////////////////////////////////////
(1)CS(Chip Select)
: Serial Flash를 사용하기 위해서 Chap을 선택하는 신호.
(2)SCK(Serial Clock)
: Serial Flash를 동작 시키기 위한 Clock을 공급하는 신호.
(3)SI(Serial Input)
: 데이터 및 주소가 Serial Flash에 입력되는 신호.
(4)SO(Serial Output)
: 해당 데이터가 Serial Flash로부터 출력되는 신호.
(5)WP(Write Protect)
: 쓰기 금지를 하는 신호.
(6)Hold
: Serial Flash의 동작을 일시 정지 시키는 신호.
(7)Vcc(Device Power Supply)
: Serial Flash가 동작할 수 있도록 전원을 공급해주는 핀.
(8)GND(Ground)
////////////////////////////////////////////////////////////////
@ ESP8266 : 1pin ~ 22pin

#define nSPI_CS   4 ///< GPIO4  D2

digitalWrite(nSPI_CS, HIGH);
pinMode(nSPI_CS, OUTPUT); // GPIO4   D2  pin19  //CS 사용하기 위해서 Chap을 선택하는 신호.
pinMode(SCK, SPECIAL);    // GPIO14  D5  pin5  //SCLK(Serial Clock)
pinMode(MISO, SPECIAL);   // GPIO12  D6  pin6  //(Master Input Slave Output)- Master 기준으로 입력신호.
pinMode(MOSI, SPECIAL);   // GPIO13  D7  pin7  //(Master Output Slave Input)- Master 기준으로 출력 신호

* NSS(Negative Slave Select)- Slave를 선택하는 신호

*/

// #include <pins_arduino.h> //기본 보드 핀 설정값
//====================================
#ifndef __pins_user_h__   // 1. 헤더 가드: 정의되지 않았다면
#define __pins_user_h__

#define Pin_LED D3 // 보드 LED

#endif /* __pins_user_h__ */
