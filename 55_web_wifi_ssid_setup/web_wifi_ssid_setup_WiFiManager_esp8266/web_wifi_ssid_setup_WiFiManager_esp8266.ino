#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#elif defined(ESP32)
#include <WiFi.h> //ESP32
#endif


//#include <DNSServer.h>
#include <WiFiManager.h>  // 라이브러리 설치

#include "mylogin.h"
// 1. 설정 정보 입력
// const char *g_kWifi_ssid = YOUR_WIFI_SSID;
// const char *g_kWifi_password = YOUR_WIFI_PASSWORD;

////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
    Serial.begin(115200);

    // WiFiManager 객체 생성
    WiFiManager wifiManager;

    // 저장된 설정으로 연결 시도, 실패 시 "AutoConnectAP" 이름의 AP 생성
    // 비밀번호를 넣고 싶다면 wifiManager.autoConnect("보드이름", "비번");
    if (!wifiManager.autoConnect("ESP8266_Config_AP"))
    {
        Serial.println("연결 실패 및 타임아웃 발생");
        delay(3000);
        ESP.reset(); // 재시작
        delay(5000);
    }

    // 연결 성공 시 출력
    Serial.println("WiFi 연결 성공! :)");
    Serial.print("IP 주소: ");
    Serial.println(WiFi.localIP());
}
////////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
    // 여기에 본인의 프로젝트 루프 코드를 작성하세요.
}