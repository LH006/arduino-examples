# [print]

### 개행 문자(\n)
- 16진수: 0x0A
- 10진수: 10 (ASCII 코드 10번)
- 8진수: \012
- Line Feed = (LF)
- Unix / Linux / macOS: \n (Line Feed, LF) 하나만 사용하며, 16진수 값은 0x0A
- Windows: \r\n = (Carriage Return + Line Feed, CRLF) 조합 =16진수 값은 0x0D 0x0A


#### 예제
```cpp
void printData(){
//  for(int i = 0; i < 17; i++)  Serial.print(buttonState[i]),Serial.print(" ");
//  for(int i = 0; i < 4; i++)  Serial.print(joystick[i]),Serial.print(" ");
//  for(int i = 0; i < 2; i++)  Serial.print(AnalogButton[i]),Serial.print(" ");
//  Serial.println("");
  Serial.print("Button Pressed:");
  for(int i = 0; i < 2; i++)  if(buttonState[i] < 100)  Serial.print(Buttons[i]),Serial.print(",");
  for(int i = 3; i < 17; i++)  if(buttonState[i] == 0)  Serial.print(Buttons[i]),Serial.print(",");
  Serial.println("");
  Serial.print("Analog Sticks:");
  for(int i = 0; i < 4; i++)  Serial.print(joystick[i]),Serial.print(",");
  for(int i = 0; i < 2; i++)  Serial.print(AnalogButton[i]),Serial.print(",");
  Serial.println("");
  Serial.println(inputCommand);
}
```

## Serial.print()
- ▷ 문자열
- Serial.print("hello!")
- Serial.print(65) 6하고5로 표시됨
- 그 값을 그냥 출력하게 됩니다. 2개로 출력

## Serial.println(val,format)
- ▷ 줄바꿈
- Serial.println("Hi!!")
- Serial.print("OK\n")
- 시리얼포트로 ASCII형식으로 출력

## Serial.printf()
-﻿ Serial.printf("%u bytes written in %u ms\r\n", 1024 * 512, end);

## Serial.println(val,format)
- ▷ format:
---
>- ▷ 진법
>- BIN (2진법)
>- OCT (8진법)
>- DEC (10진법)
>- HEX (16진법)
>- Serial.print(78, BIN)의 출력은 1001110
>- Serial.print(78, OCT)의 출력은 116
>- Serial.print(78, DEC)의 출력은 78
>- Serial.print(78, HEX)의 출력은 4E
---
>- ▷ 소수점
>- 소수를 보낼 때는 format에 있는 수만큼 소수점 아래 자리수를 표시할 수 있습니다.
(기본값은 두자리입니다.)
>- Serial.print(1.23456, 0) 의 출력은 1
>- Serial.print(1.23456, 2) 의 출력은 1.23
>- Serial.print(1.23456, 4) 의 출력은 1.2346
---

## Serial.write 차이
- https://m.blog.naver.com/dokkosam/221382458541
- Serial.write(65); //65에 해당하는 아스키값은 A로 출력

## Serial.available()
- ▷ available() 함수는 현재 시리얼 통신에 값이 있는지 없는지 확인하는 함수로 값이있다면 True를 반환

## Serial.read()
- 시리얼 모니터에서 입력한 값을 읽어오게됩니다.
- 시리얼 통신 버퍼에서 데이터를 읽어들인다
- [결과]
- 입력란에 abc를 입력하고 전송을 클릭하면 아래와 같은 결과가 나옵니다.
- 만약 println을 사용하지 않고 write()함수를 사용하게 된다면 아스키값인 abc가 그대로 출력해볼수 있습니다. 이때 변수 r의 형은 byte로 변경해 줘야합니다.

## Serial.readBytes(buffer, length)
- 문자를 읽어 버퍼에 저장한다. 만약 지정한 길이만큼의 문자를 읽었다면 종료된다.

## serialEvent () 함수 사용하기
- ▶ 시리얼에 값이 생성되는 이벤트가 발생되면 serialEvent()함수가 호출됩니다.
- [예제]
```CPP
String inputString="";
boolean stringComplete = false;
void setup() {
Serial.begin(9600); 
inputString.reserve(200);
}

void loop() {
if (stringComplete) {
      Serial.println(inputString);
      inputString=""; 
      stringComplete=false;
    }
}

void serialEvent() { while(Serial.available()) { char inChar=(char)Serial.read(); inputString += inChar; if(inChar=='\n') { stringComplete = true; } } }
[결과]
입력란에 abc를 입력하고 전송을 클릭하면 아래와 같은 결과가 나옵니다.
```



# 예제
---
#### 예제
```C++
printf("PACKET TYPE=%s, CHAN=%02d, RSSI=%02d,"
       " ADDR2=%02x:%02x:%02x:%02x:%02x:%02x\n",
       wifi_sniffer_packet_type2str(type),
       ppkt->rx_ctrl.channel,
       ppkt->rx_ctrl.rssi,
       hdr->addr2[0], hdr->addr2[1], hdr->addr2[2],
       hdr->addr2[3], hdr->addr2[4], hdr->addr2[5]);
```
#### 예제2
```C++
SerialBT.print("PACKET_TYPE= " + String(wifi_sniffer_packet_type2str(type)) + " CHAN= " + String(ppkt->rx_ctrl.channel) + " RSSI= " + String(ppkt->rx_ctrl.rssi) + " ADDR2= " + String(hdr->addr2[0], HEX) + ":" + String(hdr->addr2[1], HEX) + ":" + String(hdr->addr2[2], HEX) + ":" + String(hdr->addr2[3], HEX) + ":" + String(hdr->addr2[4], HEX) + ":" + String(hdr->addr2[5], HEX) + "\n");
```
***
# [문자열]
#### 예제1
```C++
  stringOne = String("You added ");
  stringTwo = String("this string");
  stringThree = String();

  // adding a constant integer to a String:
  stringThree =  stringOne + 123;
  Serial.println(stringThree);    // 출력표시 "You added 123"

  // adding a constant long integer to a String:
  stringThree = stringOne + 123456789;
  Serial.println(stringThree);    // 출력표시 "You added 123456789"

  // adding a constant character to a String:
  stringThree =  stringOne + 'A';
  Serial.println(stringThree);    // 출력표시 "You added A"

  // adding a constant string to a String:
  stringThree =  stringOne +  "abc";
  Serial.println(stringThree);    // 출력표시 "You added abc"

  stringThree = stringOne + stringTwo;
  Serial.println(stringThree);    // 출력표시 "You added this string"

  // adding a variable integer to a String:
  int sensorValue = analogRead(A0);
  stringOne = "Sensor value: ";
  stringThree = stringOne  + sensorValue;
  Serial.println(stringThree);    // 출력표시 "Sensor value: 401"

  // adding a variable long integer to a String:
  stringOne = "millis() value: ";
  stringThree = stringOne + millis();
  Serial.println(stringThree);    // 출력표시 "The millis: 345345"
```
***
#### 예제2
```C++
#ifdef _DEBUG
  {
    Serial.print(frequency);
    delay(500);
  }
#endif
```
```cpp
﻿char c1 = 'a'; // 문자 a 할당
char c2 = 'b'; // 문자 b 할당
char lineFeed = '\n'; // 제어 문자 \n 할당
printf("%c%c%c%c", c1, lineFeed, c2, lineFeed); // 제어 문자도 %c로 출력할 수 있음
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
결과
a
b
```
