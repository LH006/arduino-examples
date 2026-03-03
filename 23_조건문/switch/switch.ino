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

///////////////////////////////////////////////////////////////////////////////////////////
void setup() {
}

////////////////////////////////
// 반복
////////////////////////////////
void loop() {
  int Var = 1;

  switch (Var) {
    case 1:
      break;
    case 2:
      break;
    default :
      break;
  }
}

/*
//////////////////////////////////////
  char str = 'A';
  switch (str) {
    case 'A':
         break;
    case 'B':
      break;
    default :
      break;
  }

/////////////////////////////////////
  int main(void) {
  int num = 5;
  switch (num) {
  case 0 ... 5:
  printf("0이상 5이하 \n");
  break;
  case 6 ... 10:
  printf("6이상 10이하 \n");
  break;
  default: printf("범위를 벗어남 \n"); break;
  }
  return 0;
  }
  
////////////////////////////////////
Select Case ch
    case 1 To 10 :
    case 11,12,13 :
    case else:
End Select

  
*/
