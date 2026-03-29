```cpp
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "와이파이_이름"
#define STAPSK  "와이파이_비밀번호"
#endif

unsigned int localPort = 8888;      // 수신할 포트 번호
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; // 데이터를 담을 버퍼

WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("연결 완료! IP 주소: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localPort); // UDP 포트 열기
}

void loop() {
  int packetSize = Udp.parsePacket(); // 들어온 패킷 확인
  if (packetSize) {
    Serial.printf("받은 패킷 크기: %d bytes\n", packetSize);
    
    // 버퍼에 데이터 읽기
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0; // 문자열 끝 표시
    
    Serial.print("내용: ");
    Serial.println(packetBuffer);

    // 보낸 쪽으로 답장 보내기 (선택 사항)
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("ACK: 메시지 잘 받았습니다!");
    Udp.endPacket();
  }
}
```
# 실행 및 테스트 방법
* 시리얼 모니터 확인: 코드를 업로드한 후 시리얼 모니터(보드레이트 115200)를 열어 ESP8266이 할당받은 IP 주소를 확인합니다. (예: 192.168.0.15)
* 테스트 도구 사용: PC에서 UDP 패킷을 보내기 위해 별도의 툴이 필요합니다.

* 추천 도구: Packet Sender (무료/오픈소스)
* 패킷 전송 설정:
* Address: ESP8266의 IP 주소
* Port: 8888
* Protocol: UDP
* Message: "Hello ESP8266!" 입력 후 Send 클릭

# 핵심 포인트 요약
* 비연결성: TCP처럼 connect() 과정 없이 바로 parsePacket()으로 데이터를 기다립니다.
* 속도: 오버헤드가 적어 센서 데이터를 실시간으로 수초 내에 수만 번 전송해야 하는 프로젝트에 유리합니다.
* 주의사항: 공유기 환경에 따라 방화벽 설정이 필요할 수 있으며, 같은 와이파이 망(LAN) 안에서 테스트하는 것이 가장 확실합니다.