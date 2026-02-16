/*
포트(예: 80, 443, 1720)에서 클라이언트의 접속을 기다리는 리스닝(Listening) 상태를 유지합
*/

// 기본 라이브러리
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <StreamString.h>
// 추가
#include "pins_user.h"

#ifndef STASSID
#define STASSID "LH"
#define STAPSK "77994422"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

const int led = Pin_LED;

///////////////////////////////////////////////////
// 페이지 루트
///////////////////////////////////////////////////
void handleRoot()
{
  digitalWrite(led, 1);
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  StreamString temp;
  temp.reserve(500); // Preallocate a large chunk to avoid memory fragmentation
  temp.printf("\
<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 연습</title>\
    <style>\
      body { background-color: #cccccc11; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>ESP8266 연습1</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <img src=\"/test.svg\" />\
    <p>LED: %02d</p>\
  </body>\
</html>",
              hr, min % 60, sec % 60, led);
  server.send(200, "text/html", temp.c_str()); // 보내기
  digitalWrite(led, 0);
}
//////////////////////////////////////////////////////

void handleNotFound()
{
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
///////////////////////////////////////////////////////////////////////
void drawGraph()
{
  String out;
  out.reserve(2600);
  char temp[70];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10)
  {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}
////////////////////////////////////////////////////////////////////////////////////////
void setup(void)
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  Serial.print("접속중");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("연결성공(SSID) : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);        // 루트 페이지
  server.on("/test.svg", drawGraph); // 그래픽
  server.on("/inline", []()
            { server.send(200, "text/plain", "this works as well"); });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
///////////////////////////////////////////////////////////////////////////
void loop(void)
{
  server.handleClient();
  MDNS.update();
}
