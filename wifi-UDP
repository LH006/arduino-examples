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