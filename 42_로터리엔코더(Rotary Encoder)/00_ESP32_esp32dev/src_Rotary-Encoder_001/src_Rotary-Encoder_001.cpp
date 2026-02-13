/************************************
 *  사용 CPU :
 *  날    짜 :
 *  버    전 :
 *  작 성 자 :
 *  컴파일러 :
 *  참    고 :
 *  내    용 :
 *************************************/
#include <Arduino.h>

#define Interrupt_ok // 인터럽트 사용하기
// #define Interrupt_No // 인터럽트 사용안함

/////////////////////////////////////////////////////////////////
//  P I N 정보
/////////////////////////////////////////////////////////////////
#if defined(ESP32)
#define PIN_ROTARY_ENCODER_A_S2_CLK 16 // Output A
#define PIN_ROTARY_ENCODER_B_S1_DT 27  // Output B
#define PIN_ROTARY_ENCODER_SW 36
#endif

#if defined(ESP8266)
#define PIN_ROTARY_ENCODER_A_S2_CLK 32
#define PIN_ROTARY_ENCODER_B_S1_DT 21
#define PIN_ROTARY_ENCODER_SW 25
#endif

#if defined(__AVR_ATmega2560__)
#define PIN_ROTARY_ENCODER_A_S2_CLK 12 // Output A
#define PIN_ROTARY_ENCODER_B_S1_DT 13  // Output B
#define PIN_ROTARY_ENCODER_SW 14       // Switch
#endif

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO_EVERY)
// Example for Arduino UNO with input signals on pin 2 and 3
#define PIN_ROTARY_ENCODER_A_S2_CLK A2
#define PIN_ROTARY_ENCODER_B_S1_DT A3
#endif

////////////////////////////////////////////////////////////////
//  G L O B A L   V A R I A B L E (전역  변수 선언)
////////////////////////////////////////////////////////////////
int counter = 0; // 회전 카운터 측정용 변수
int change;      // 엔코더 변한값
static int oldA; // static 정적변수(자동으로 0초기화) // 직전 CLK의 신호상태 저장용 변수
int oldB = 1;    //

int newA = 1; // CLK의 현재 신호상태 저장용 변수
int newB = 1;
String currentDir = ""; // 현재 회전 방향 출력용 문자열 저장 변수

////////////////////////////////////////////////////////////////
// 엔코더 값 알기
// -1,0,+1의 값중 하나를 반환합니다.
////////////////////////////////////////////////////////////////
int getEncoderTurn(void)
{
  int result = 0;
  newA = digitalRead(PIN_ROTARY_ENCODER_A_S2_CLK);
  newB = digitalRead(PIN_ROTARY_ENCODER_B_S1_DT);

  if (newA != oldA || newB != oldB) // 변한 값이 있으면 실행
  {
    if (oldA == HIGH && newA == LOW) // DT핀의 신호를 확인해서 엔코더의 회전 방향을 확인함
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}

////////////////////////////////////////////////////////////////
// 엔코더 값 알기
// 인터럽트 발생시 실행되는 함수
// int Interrupt_Encoder() //int 인터럽트 안됨
////////////////////////////////////////////////////////////////
void IRAM_ATTR Interrupt_Encoder()
{
  newA = digitalRead(PIN_ROTARY_ENCODER_A_S2_CLK); // CLK의 현재 상태를 읽어서
  if (newA != oldA && newA == 0)                   // CLK핀의 신호가 변경되고, , 그 상태가 LOW이면
  {
    // counter++; // 연습

    //  DT핀의 신호를 확인해서 엔코더의 회전 방향을 확인함.
    if (digitalRead(PIN_ROTARY_ENCODER_B_S1_DT) != newA) // 신호가 다르다면 시계방향 회전
    {
      counter++; // 카운팅 용 숫자 1 증가
      change = 1;
    }
    else // 신호가 같다면 반시계방향 회전
    {
      counter--; // 카운팅 용 숫자 1 감소
      change = -1;
    }
  }
  oldA = newA; // 마지막 상태 변수 저장
}

////////////////////////////////////////////////////////////////
// 설정
////////////////////////////////////////////////////////////////
void setup()
{
  pinMode(PIN_ROTARY_ENCODER_A_S2_CLK, INPUT); // 엔코더의 핀들을 입력으로 설정
  pinMode(PIN_ROTARY_ENCODER_B_S1_DT, INPUT);  // 엔코더의 핀들을 입력으로 설정
  pinMode(PIN_ROTARY_ENCODER_SW, PULLUP);      // 엔코더의 스위치 핀 입력으로 설정

  // digitalWrite(PIN_ROTARY_ENCODER_SW, HIGH);
  Serial.begin(115200);

#if defined(Interrupt_ok)
  // 외부 인터럽트 선언, 핀의 상태가 변하면 Interrupt_Encoder함수 실행
  attachInterrupt(PIN_ROTARY_ENCODER_A_S2_CLK, Interrupt_Encoder, FALLING); // 인터럽트 체크함수
  attachInterrupt(PIN_ROTARY_ENCODER_B_S1_DT, Interrupt_Encoder, FALLING);
// LOW    :   LOW 상태일 때
// CHANGE :  입력 값이 변할때(HIGH에서 LOW 또는 LOW에서 HIGH)
// RISING :  LOW -> HIGH로 변할때
// FALLING :  HIGH -> LOW로 변할때
// HIGH   :  HIGH 상태일 때 (rduino Due, Zero, MKR1000 만 허용)
#endif
}

//////////////////////////////////////////////////////////////
// 반복
//////////////////////////////////////////////////////////////
void loop()
{
  change = 0;

#if defined(Interrupt_No)
  int change = getEncoderTurn();
  counter = counter + change;
#endif

  if (digitalRead(PIN_ROTARY_ENCODER_SW) == LOW) // 엔코더값 리셋
  {
    // counter = 0;
    // currentDir = "카운터 값 리셋";
  }
  delay(1);

  // 프린트용
  if (change == 0)
  {
    currentDir = "회전 정지";
  }
  else
  {
    if (change == 1)
    {
      currentDir = "시계방향 회전";
    }
    else
    {
      currentDir = "반시계 방향 회전";
    }
  }

  Serial.print("newA:");
  Serial.print(newA);
  Serial.print(", newB:");
  Serial.print(newB);
  Serial.print(", change:");
  Serial.print(change);
  Serial.print(", 엔코더카운터값 : ");
  Serial.print(counter);
  Serial.print(", 회전방향: ");
  Serial.println(currentDir); // 회전방향 출력
}

/**********************************************************
 * 메모장


***********************************************************/