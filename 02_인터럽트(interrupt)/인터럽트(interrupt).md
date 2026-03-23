# 인터럽트(interrupt)
- 인터럽트 : 즉시 처리해야 하는 특수한 이벤트의 발생
- 인터럽트 서비스 루틴 (interrupt service routine, 이하 ISR)
- ISR : 인터럽트 서비스 루틴, 인터럽트가 발생했을 때 호출되는 함수

## 우노 보드
- 우노의 경우 인터럽트를 처리
- 핀은 2번과 3번 핀인데 각각 INT0, INT1
- (인터럽트 0번, 인터럽트 1번)
- attachInterrupt( pin, ISR, mode) 함수
- attatchInterrupt() 함수는 통상 setup() 함수 안에서 사용되어 초기에 인터럽트를 설정
- pin 값은 우노의 경우 0(또는 INT0 ), 1 (또는 INT1) 둘 중 하나이다.
- 2번 핀의 경우 0을, 3번 핀의 경우 1을 입력해야 한다는 것에 주의해야 한다. 혼동을 피하기 위해서 INT0, INT1 상수를 이용할 것을 권한다.
- ISR은 인터럽트가 걸렸을 때 호출할 함수의 이름이다.
- mode 는 RISING / FALLING / CHANGE / LOW 중 하나
- ISR은 입력 인수를 받을 수 없고 출력도 void형이어야 한다.
