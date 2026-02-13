#define Key01 0x1 //숫자1
#define Key02 0x2 //숫자2

const unsigned int BAUD_RATE = 9600;

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  int aaa = 0;

    switch (aaa) {
      case Key01:
        Serial.println("Press /////'1'/////");
        break;      
      case Key02:
        Serial.println("Press /////'2'/////");
        break;

      case 0x3:               //계속 누르고있을경우
        //Serial.println("");
        interlock = 1;
        break;
      default:                       //아무값이 없으면
        Serial.println("Press // 사용 안함(선택에 없는 버튼) //");
        break;
    }

