/////////////////////////////////
//  사용 CPU : ESP8266
//  날    짜 :
//  버    전 : Ver
//  작 성 자 : seung seung
//  컴파일러 :
//  참    고 :
//  내    용 :
//////////////////////////////////

//////////////////////////////////
// P I N 정보
/////////////////////////////////
#define Pin_CLK D5
#define Pin_DT D6
#define Pin_SW D7
#define Pin_LED1 D1
#define Pin_LED2 D2
#define Pin_LED3 D3

/////////////////////////////////
//  G L O B A L   V A R I A B L E (전역  변수 선언)
//////////////////////////////////
int encoderVal = 0;
static int oldA = HIGH; //정적변수(자동으로 0초기화)
static int oldB = HIGH; //정적변수(자동으로 0초기화)

/////////////////////////////////
// 설정
////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode (Pin_CLK, INPUT);
  pinMode (Pin_DT, INPUT);
  pinMode (Pin_SW, INPUT);
  digitalWrite (Pin_SW, HIGH);
  pinMode (Pin_LED1, OUTPUT);
  pinMode (Pin_LED2, OUTPUT);
  pinMode (Pin_LED3, OUTPUT);

}

//////////////////////////////////
// 엔코더 값 알기
//////////////////////////////////
int getEncoderTurn(void)
{
  int result = 0;
  int newA = digitalRead(Pin_CLK);
  int newB = digitalRead(Pin_DT);
  if (newA != oldA || newB != oldB)
  {
    if (oldA == HIGH && newA == LOW)
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}

/////////////////////////////////////
// 반복
/////////////////////////////////////
void loop() {
  int change = getEncoderTurn();
  encoderVal = encoderVal + change;
  if (digitalRead(Pin_SW) == LOW)
  {
    encoderVal = 0;
  }

  if ((encoderVal) <= -10) // -10보다 작다면
  {
    digitalWrite(Pin_LED1, HIGH);
    digitalWrite(Pin_LED2, LOW);
    digitalWrite(Pin_LED3, LOW);
  }
  else if ((encoderVal) < 10) //10보다 작다면
  {
    digitalWrite(Pin_LED1, LOW);
    digitalWrite(Pin_LED2, HIGH);
    digitalWrite(Pin_LED3, LOW);
  }
  else                       // 둘다 아니다면
  {
    digitalWrite(Pin_LED1, LOW);
    digitalWrite(Pin_LED2, LOW);
    digitalWrite(Pin_LED3, HIGH);
  }
}
