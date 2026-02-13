//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// [소스] 아무튼 이렇게 표현하고 아두이노 가상시뮬레이터에서 그 결과를 살펴볼까요.
class Calc
{
  private:
    int a = 0;
    int b = 0;
  public:
    Calc(int val1, int val2) {
      a = val1;
      b = val2;
    }
    int AAAA(); //변수이름
    int BBBB();
};

int Calc::AAAA() { //클래스 외부로 빼면
  return a + b;
}

int Calc::BBBB() { //클래스 외부로 빼면
  return a - b;
}

Calc obj(2, 3); //객체변수 선언 //클래스 룰을지키는 obj한개을 만들고 거기에 2,3값을 넣어라

void setup()
{
  Serial.begin(9600);
  Serial.println(obj.AAAA());
}

void loop()
{
  char val1=0;
  Calc obj(8, 8); //객체변수 선언 //클래스 룰을지키는 obj한개을 만들고 거기에 2,3값을 넣어라
  Serial.println(obj.BBBB());
  delay(1000);
}

// [결과]
// 5
// 0
