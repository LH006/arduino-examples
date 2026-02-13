#if defined(ESP8266)
#include <ESP8266WiFi.h> //ESP8266
#elif defined(ESP32)
#include <WiFi.h> //ESP32
#endif

#include "mylogin.h"
// 1. 설정 정보 입력
// const char *g_kWifi_ssid = YOUR_WIFI_SSID;
// const char *g_kWifi_password = YOUR_WIFI_PASSWORD;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n--- WiFi 설정 메뉴 ---");
  Serial.println("형식: SSID,비밀번호 (예: MyWiFi,12345678)");
}
///////////////////////////////////////////////////////////////////////
void loop()
{
  if (Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    input.trim(); // 공백 및 개행문자 제거

    int commaIndex = input.indexOf(',');
    if (commaIndex != -1)
    {
      String newSSID = input.substring(0, commaIndex);
      String newPass = input.substring(commaIndex + 1);

      Serial.print("연결 시도 중: ");
      Serial.println(newSSID);

      WiFi.disconnect(); // 기존 연결 해제
      WiFi.begin(newSSID.c_str(), newPass.c_str());

      int retry = 0;
      while (WiFi.status() != WL_CONNECTED && retry < 20)
      {
        delay(500);
        Serial.print(".");
        retry++;
      }

      if (WiFi.status() == WL_CONNECTED)
      {
        Serial.println("\n연결 성공!");
        Serial.print("IP 주소: ");
        Serial.println(WiFi.localIP());
      }
      else
      {
        Serial.println("\n연결 실패. 설정을 확인하세요.");
      }
    }
    else
    {
      Serial.println("잘못된 형식입니다. 'SSID,비밀번호' 형태로 입력하세요.");
    }
  }
}
///////////////////////////////////////////////////////////////////////
