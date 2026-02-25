////////////////////////////////////////////////////////////////////////////////
//  사용 CPU : [ESP8266] NodeMCU
//  날    짜 :
//  버    전 : Ver 0.05
//  작 성 자 :
//  컴파일러 : 아두이노
//  참    고 :
//  내    용 : (웹 서버) 릴레이 모듈 – AC 기기 제어 (버튼)
//            DNS
//            OTA
//            Web
//            WebSocket
//            Button
//            FS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  I N C L U D E  …을 (부분·요소 등으로서) 포함하다
////////////////////////////////////////////////////////////////////////////////
// 1) 시스템 라이브러리
#ifdef ESP32
// #include <WiFi.h>
// #include <AsyncTCP.h> //추가 라이브러리
#elif defined(ESP8266)
#include <ESP8266WiFi.h>       //기본
#include <ESP8266WebServer.h>  //기본
#include <LittleFS.h>          //드라이브 만들기
#endif

// #include <Arduino.h>      //기본
// #include <WiFiClient.h>   //기본
// #include <ESP8266mDNS.h>  //기본 //MDNS
// #include <StreamString.h> //기본
//  2) 추가 라이브러리
#include <WiFiManager.h>  //추가 라이브러리
// 3) 사용자 라이브러리
#include "pins_user_esp8266.h"  //핀 설정
#include "ini.h"                //핀 설정

////////////////////////////////////////////////////////////////////////////////
//  G L O B A L   V A R I A B L E (전역  변수 선언)
////////////////////////////////////////////////////////////////////////////////

int relayGPIOs[RELAYS_CONTROL_TOTAL] = { RELAYS_CONTROL_1, RELAYS_CONTROL_2, RELAYS_CONTROL_3, RELAYS_CONTROL_4, RELAYS_CONTROL_5 };  // 어레이 변수에서 릴레이를 제어할 ESP8266 GPIO를 정의

// 변수에 네트워크 이름 비번
// const char *ssid = "LH";
// const char *password = "77994422";

const char *PARAM_INPUT_1 = "relay";
const char *PARAM_INPUT_2 = "state";

// PROGMEM = R"rawliteral( HTML 내용 )rawliteral";  // R"rawliteral() // 그대로 출력
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta name="author" content="홈" />
    <meta charset="UTF-8" />
    <style>
      html {font-family: Arial; display: inline-block; text-align: center;}
      h2 {font-size: 3.0rem;}
      p {font-size: 3.0rem;}
      body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
      .switch {position: relative; display: inline-block; width: 120px; height: 68px}
      .switch input {display: none}
      .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
      .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
      input:checked+.slider {background-color: #2196F3}
      input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
    </style>
  </head>
  <H1>HOME</H1>
  <body>
    <a href="/led_control"><h2>led_control</h2></a>
    <a href='/setup'><h2>설정</h2></a>
    <a href='/1'><h2>1</h2></a>
    <a href='/2'><h2>2</h2></a>
    <a href='/3'><h2>3</h2></a>
    <a href='/4'><h2>4</h2></a>
  </body>
</html>
)rawliteral";

// 객체 생성
ESP8266WebServer server(80);  // 객체 생성 // Create webServer object on port 80
WiFiClient client;            // 클라이언트 객체 생성
WiFiManager wifiManager;      // WiFiManager 객체 생성
// ESP8266WiFiMulti WiFiMulti;
////////////////////////////////////////////////////////////////////////////////
// 설정
////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);  // Serial port for debugging purposes
  Serial.println(SERIAL_COPYRIGHT);
  delay(1000);
  fs_filesystem_ini();  //FS 저장공간 사용하기

  pinMode(Pin_LED, OUTPUT);  // 출력으로 설정
  pinMode(RELAYS_CONTROL_1, OUTPUT);
  pinMode(RELAYS_CONTROL_2, OUTPUT);
  pinMode(RELAYS_CONTROL_3, OUTPUT);
  pinMode(RELAYS_CONTROL_4, OUTPUT);
  pinMode(RELAYS_CONTROL_5, OUTPUT);

  digitalWrite(Pin_LED, 0);
  wifi_init();
  server.on("/", handle_Root);  // 호출 URL에 처리할 함수을 지정
  server.on("/setup", handle_setup);
  server.on("/led_control", handle_led_control);
  server.on("/text", []() {
    server.send(200, "text/plain", "이런식 일반텍스트도 작동함");
  });  // plain => 일반텍스트 파일
  server.onNotFound(handle_NotFound);

  server.on("/1", handle_1);  // 페이지
  server.on("/2", handle_2);  // 페이지
  server.on("/3", handle_3);  // 페이지  //구글 확인
  server.on("/4", handle_4);  // 페이지  //이건 입력 값이있으면 실행
}

////////////////////////////////////////////////////////////////////////////////
// 반복
////////////////////////////////////////////////////////////////////////////////
void loop() {
  server.handleClient();  // 브라우저로 부터 전달되는 요청을 처리
  // MDNS.update();
  // server.available();
}

////////////////////////////////////////////////////////////////////////////////
// Setup_WIFI()
////////////////////////////////////////////////////////////////////////////////
void wifi_init() {
  WiFi.mode(WIFI_STA);
  // WiFiManager wifiManager; // WiFiManager 객체 생성

  // 저장된 설정으로 연결 시도, 실패 시 "AutoConnectAP" 이름의 AP 생성
  // 비밀번호를 넣고 싶다면 wifiManager.autoConnect("보드이름", "비번");
  if (!wifiManager.autoConnect("ESP8266_Config_AP")) {
    Serial.println("연결 실패 및 타임아웃 발생");
    delay(3000);
    ESP.reset();  // 재시작
    delay(5000);
  }

  // 연결 성공 시 출력
  Serial.println("WiFi 연결 성공!");
  Serial.print("IP 주소: ");
  Serial.println(WiFi.localIP());  // 접속된 IP Address 출력

  // if (MDNS.begin("esp8266"))
  //{
  //   Serial.println("MDNS responder started"); // 표시되야 가능함
  // }

  server.begin();  // Start server
  Serial.println("HTTP server 시작됨");
}

///////////////////////////////////////////////////
// 홈페이지 루트
///////////////////////////////////////////////////
void handle_Root() {
  Serial.println("홈페이지 메인");
  server.send(200, "text/html", index_html);  // 요청 받은 내용에 맞게 응답 메세지를 만들어서 전달(보내기)
                                              // server.send(200, "text/plain", message_html); 텍스트 파일로 보여주기
                                              // server.send(200, "image/svg+xml", out);
  /*
   // 시간값 가져오기
  #include <time.h>
  long timezone = 2;
  byte daysavetime = 1;

    Serial.println("Contacting Time Server");
    configTime(3600 * timezone, daysavetime * 3600, "time.nist.gov", "0.pool.ntp.org", "1.pool.ntp.org");
    struct tm tmstruct;
    delay(2000);
    tmstruct.tm_year = 0;
    getLocalTime(&tmstruct, 5000);
    Serial.printf("\nNow is : %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct.tm_year) + 1900, (tmstruct.tm_mon) + 1, tmstruct.tm_mday, tmstruct.tm_hour, tmstruct.tm_min, tmstruct.tm_sec);
    Serial.println("");
  */
}
///////////////////////////////////////////////////
//
///////////////////////////////////////////////////
void handle_setup() {
  Serial.println("설정");

  // R"rawliteral() // 그대로 출력
  char setup_html[] = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta name="author" content="홈" />
    <meta charset="UTF-8" />
  </head>

  <body>
    <a href="/"><h2>홈</h2></a>

  </body>
</html>
)rawliteral";

  server.send(200, "text/html", setup_html);  // 보내기
}
///////////////////////////////////////////////////
//
///////////////////////////////////////////////////
void handle_led_control() {
  Serial.println("led 제어");

  // PROGMEM = R"rawliteral( HTML 내용 )rawliteral";
  const char message_html[] = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta name="author" content="web 버튼" />
    <meta charset="UTF-8" />

    <style>
      html {font-family: Arial; display: inline-block; text-align: center;}
      h2 {font-size: 3.0rem;}
      p {font-size: 3.0rem;}
      body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
      .switch {position: relative; display: inline-block; width: 120px; height: 68px}
      .switch input {display: none}
      .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
      .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
      input:checked+.slider {background-color: #2196F3}
      input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
      .card {background-color: #F8F7F9; box-shadow: 2px 2px 12px 1px rgba(140, 140, 140, .5); padding-top: 1px; padding-bottom: 1px}
      .button {padding: 15px 50px; font-size: 24px; text-align: center; color: #fff; background-color: #0f8b8d; border-radius: 5px; -webkit-tap-highlight-color: rgba(0, 0, 0, 0)}
      .state {}
    </style>
  </head>

  <body>
    <p><a href="/">Main Page</a></p>
    <p></p>
    <div class="card">
      <h2>버튼 1</h2>
      <p class="state">상태 : <span id="id_state_button1">%STATE_BUTTON1%</span></p>
      <p><button id="id_button_Mode" class="button">BUTTON1</button></p>
    </div>
    <p></p>
    <div class="card">
      <h2>스위치 2</h2>
      <p class="state">상태 : <span id="id_state_button2">%STATE_BUTTON2%</span></p>
      <p><button id="id_button_Fan" class="button">BUTTON2</button></p>
    </div>
    <p></p>
    <div class="card">
      <h2>스위치 3</h2>
      <p class="state">상태 : <span id="id_state_button3">%STATE_BUTTON3%</span></p>
      <p><button id="id_button_Led" class="button">BUTTON3</button></p>
    </div>
    <p></p>
    <div class="card">
      <h2>스위치 4</h2>
      <p class="state">상태 : <span id="id_state_button4">%STATE_BUTTON4%</span></p>
      <p><button id="id_button_Led" class="button">BUTTON4</button></p>
    </div>
    <p></p>
    <div class="card">
      <h2>스위치 5</h2>
      <p class="state">상태 : <span id="id_state_button5">%STATE_BUTTON5%</span></p>
      <p><button id="id_button_Led" class="button">BUTTON5</button></p>
    </div>
    <p></p>

  </body>
</html>
)rawliteral";

  server.send(200, "text/html", message_html);  // 보내기 html
}
//////////////////////////////////////////////////////
void handle_NotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n실제 값(Arguments): ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

///////////////////////////////////////////////////
// 페이지 1
///////////////////////////////////////////////////
void handle_1() {
  Serial.println("페이지1");
  StreamString temp;
  temp.reserve(500);  // Preallocate a large chunk to avoid memory fragmentation
  temp.printf("\
<html>\
  <head>\
    <meta http-equiv='refresh' content='3'/>\
    <meta charset='UTF-8'/>\
    <title>LED 상태 점검(3초마다 갱신)</title>\
    <style>\
      body { background-color: #cccccc11; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>LED 상태 순차</h1>\
    <a href='/'><h2>홈</h2></a>\
    <p>보드 LED 상태 : %2d</p>\
  </body>\
</html>",
              digitalRead(Pin_LED));
  server.send(200, "text/html", temp.c_str());  // 보내기

  if (digitalRead(Pin_LED)) {
    digitalWrite(Pin_LED, 0);
  } else {
    digitalWrite(Pin_LED, 1);
  }
  delay(1000);
}
///////////////////////////////////////////////////
// 페이지 루트
///////////////////////////////////////////////////
void handle_2() {

  String message = "<html><head><meta http-equiv='refresh' content='3'/><meta charset='UTF-8'/>";
  message += "\n<title>LED 상태 점검(3초 갱신)</title>";
  message += "<style>body { background-color: #cccccc11; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
  message += "</head>";
  message += "<p><body><a href='/'><h1>HOME</h1></a></body></p>";
  message += "<p><body><h1>LED1 상태 : ";
  message += digitalRead(Pin_LED) ? "꺼짐(OFF)" : "켜짐(ON)";
  message += "</h1></body></p></html>\n";

  server.send(200, "text/html", message);

  /*
    String inputMessage;
    String inputParam;
    String inputMessage2;
    String inputParam2;

  // 메세지에 들어오면 켜기 / 끄기
    // GET input1 value on <ESP_IP>/update?relay=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1) & request->hasParam(PARAM_INPUT_2))
    {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam2 = PARAM_INPUT_2;
      if (RELAY_NO)
      {
        Serial.print("켜기 ");
        digitalWrite(relayGPIOs[inputMessage.toInt() - 1], !inputMessage2.toInt());
      }
      else
      {
        Serial.print("NC ");
        digitalWrite(relayGPIOs[inputMessage.toInt() - 1], inputMessage2.toInt());
      }
    }
    else
    {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage + inputMessage2);
    request->send(200, "text/plain", "OK");
    */
}

///////////////////////////////////////////////////
// 페이지 3
///////////////////////////////////////////////////
void handle_3() {
  // WiFiClient client; // WiFiClient 클래스를 사용하여 TCP 연결 생성
  // WiFiClient client = server.available(); // WiFiClient 클래스를 사용하여 TCP 연결 생성

  // Server 정보 설정: HTTP GET 요청 보낼 서버의 host와 port 설정
  const char *host = "google.com";
  const uint16_t port = 80;
  static bool wait;  // 정적 변수를 사용하여 한 번만 연결을 시도하도록 함

  if (!client.connect(host, port))  // 서버에 연결 시도
  {
    Serial.println("구글 연결 실패");  // 실패시 5초후 다시 시도 반복
    delay(5000);
    return;
  }

  // Server에 데이터 전송
  Serial.println("구글 연결 성공");
  if (client.connected())  // 연결됨 확인
  {
    client.print("GET / HTTP/1.1\n");           // GET 요청(메서드) + /(루트)(URL) + HTTP1.1버전 사용
    client.print("Host : www.google.com\n\n");  // 200 ok(성공) //400 not
  }
  delay(1000);

  // Server로부터 응답 출력
  Serial.println("원격 서버에서 받은값 있는지 확인");
  while (client.available()) {
    Serial.print(client.read());
  }

  Serial.println("\n연결 종료 중");
  client.stop();

  // 한 번만 연결을 시도한 후 30초 대기
  if (wait) {
    delay(30000);
    digitalWrite(Pin_LED, 0);
  }
  wait = true;
}
///////////////////////////////////////////////////
// 페이지 루트4
///////////////////////////////////////////////////
void handle_4()
// void drawGraph()
{
  String out;
  out.reserve(2600);
  char temp[70];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  server.send(200, "image/svg+xml", out);
}

////////////////////////////////////////////////////////////////////////////////
// 웹 페이지의 버튼(상태 알려주기) 섹션으로 자리 표시
// 클라이언트 실행하면 처음 한번실행
// %이로 시작하는값(아마도 함수에 지정)
// MCU보드에거 가져와서 클라이언트에 표시
/////////////////////////////////////////////////
String processor(const String &var) {
  // Serial.print("processor()실행 서버지금에 상태 클라이언트 알려주기값 : ");
  // Serial.println(var);
  if (var == "BUTTONPLACEHOLDER")
  // Serial.println("클라이언트 %BUTTONPLACEHOLDER% 넣어야 될 값이 머야?");
  {
    String buttons = "";
    for (int i = 1; i <= RELAYS_CONTROL_TOTAL; i++) {
      String relayStateValue = relayState(i);
      // buttons += "<h4>릴레이(Relay) #" + String(i) + " - GPIO " + relayGPIOs[i - 1] + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" " + relayStateValue + "><span class=\"slider\"></span></label>";
      buttons += "<h4>릴레이(Relay) #</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" " + relayStateValue + "><span class=\"slider\"></span></label>";
    }
    return buttons;
  }
  return String();
}

////////////////////////////////////////////////////////////////////////////////
// 릴레이상태 가져오기
////////////////////////////////////////////////////////////////////////////////
String relayState(int numRelay) {
  if (RELAY_NO) {
    if (digitalRead(relayGPIOs[numRelay - 1])) {
      return "";
    } else {
      return "checked";
    }
  } else {
    if (digitalRead(relayGPIOs[numRelay - 1])) {
      return "checked";
    } else {
      return "";
    }
  }
  return "";
}

////////////////////////////////////////////////////////////////////////////////
// LittleFS filesystem
////////////////////////////////////////////////////////////////////////////////
void fs_filesystem_ini() {
  Serial.println("");
  Serial.println("Formatting LittleFS filesystem");
  LittleFS.format();
  Serial.println("Mount LittleFS");
  if (!LittleFS.begin()) {
    Serial.println("LittleFS 를 마운트하는 동안 오류 발생");
    return;
  }
  /*
  listDir("/");
  deleteFile("/hello.txt");
  writeFile("/hello.txt", "Hello ");
  appendFile("/hello.txt", "World!\n");
  listDir("/");
  */

  // LittleFS.end();
  // Serial.println("Now mount it");
}

/////////////////////////////////////////
// 시리얼 출력 하기
/////////////////////////////////////////
void Serial_Out(int var) {
  switch (var) {
    case 1:
      Serial.print("Connected to ");
      Serial.println();
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    case 2:
      Serial.print("온도 =");
      //Serial.print(State_Temperature, DEC);
      Serial.println("°C");
      Serial.print("습도 =");
      //Serial.print(State_Humidity, DEC);
      Serial.println("%");
      break;
    default:
      break;
  }
}
////////////////////////////////////////////////////////////////////////////////
// 릴레이 출력 제어
////////////////////////////////////////////////////////////////////////////////
/*
String relayState1(int numRelay)
{
  // Set all relays to off when the program starts - if set to Normally Open (NO), the relay is off when you set the relay to HIGH
  for (int i = 1; i <= RELAYS_CONTROL_TOTAL; i++)
  {
    pinMode(relayGPIOs[i - 1], OUTPUT);
    if (RELAY_NO)
    {
      digitalWrite(relayGPIOs[i - 1], HIGH);
    }
    else
    {
      digitalWrite(relayGPIOs[i - 1], LOW);
    }
  }
}
*/
////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/*
void sendGoogleChatMessage(String message)
{
  if (WiFi.status() == WL_CONNECTED) // 정상연결 되면
  {
    WiFiClientSecure client;

    // SSL 인증서 검증을 건너뜁니다 (간편한 연결을 위해 사용)
    client.setInsecure();

    HTTPClient http;

    // HTTP 요청 시작
    if (http.begin(client, webhook_url))
    {
      http.addHeader("Content-Type", "application/json; charset=UTF-8");

      // 구글 채팅 규격에 맞는 JSON 페이로드 생성
      String payload = "{\"text\": \"" + message + "\"}";

      Serial.println("Sending message to Google Chat...");
      int httpCode = http.POST(payload); // POST 요청 전송

      if (httpCode > 0)
      {
        String response = http.getString();
        Serial.printf("[HTTP] 응답 코드: %d\n", httpCode);
        Serial.println("[HTTP] 응답 내용: " + response);
      }
      else
      {
        Serial.printf("[HTTP] 요청 실패, 에러: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end(); // 자원 해제
    }
  }
  else
  {
    Serial.println("WiFi 연결 끊김");
  }
}
//////////////////////////////////////////////////////////
void sendGoogleChatMessage1(String message)
{
  WiFiClientSecure client;
  client.setInsecure(); // SSL 인증서 검증 건너뛰기

  if (client.connect("chat.googleapis.com", 443))
  {
    String payload = "{\"text\": \"" + message + "\"}";
    client.println("POST " + String(webhook_url) + " HTTP/1.1");
    client.println("Host: chat.googleapis.com");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(payload.length());
    client.println();
    client.println(payload);
    client.stop();
  }
}
*/

/*
메모장




///////////////////////////////////////////////////////////////////////












void server_start() {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;

  httpd_uri_t index_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };

  //Serial.printf("Starting web server on port: '%d'\n", config.server_port);
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &index_uri);
  }
}



*/