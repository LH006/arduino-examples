/* ---------------------------------------------------------------------
  사용 CPU : [ESP8266] NodeMCU
  날    짜 :
  버    전 : Ver 0.05
  작 성 자 :
  컴파일러 : 아두이노
  참    고 :
  내    용 : (웹 서버) 릴레이 모듈 – AC 기기 제어 (버튼)
  ------------------------------------------------------------------- */


//--------------------------------------------------------------------
//  I N C L U D E  …을 (부분·요소 등으로서) 포함하다
//--------------------------------------------------------------------
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

//-------------------------------------------------------------------
//    P I N 정보 예) (Key Switch)(LCD Data bit 0)(LED)
//  예) #define Pin_XXXX  A0
//  예) const int XXXX = 12;
//-------------------------------------------------------------------
#define RELAY_NO    true    // Set to true to define Relay as Normally Open (NO)
#define NUM_RELAYS  5       // 제어하려는 릴레이의 수를 정의 (5로 설정)

//--------------------------------------------------------------------
//  G L O B A L   V A R I A B L E (전역  변수 선언)
//--------------------------------------------------------------------

int relayGPIOs[NUM_RELAYS] = {5, 4, 14, 12, 13}; // 어레이 변수에서 릴레이를 제어할 ESP8266 GPIO를 정의

// 변수에 네트워크 이름 비번
const char* ssid = "LH";
const char* password = "79427942";

const char* PARAM_INPUT_1 = "relay";
const char* PARAM_INPUT_2 = "state";

//--------------------------------------------------------------------
// PROGMEM = R"rawliteral( HTML 내용 )rawliteral";
//
//--------------------------------------------------------------------
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta name="author" content="환&승" />
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

  <body>
    <h2>스위치</h2>
    <h2>습도 온도</h2>
    %BUTTONPLACEHOLDER%
    
    <script>
      function toggleCheckbox(element) {
      var xhr = new XMLHttpRequest();
      if(element.checked){ xhr.open("GET", "/update?relay="+element.id+"&state=1", true); }
      else { xhr.open("GET", "/update?relay="+element.id+"&state=0", true); }
      xhr.send();
      }
    </script>
  </body>
</html>
)rawliteral";

AsyncWebServer server(80); // Create AsyncWebServer object on port 80

//--------------------------------------------------------------------
// 웹 페이지의 버튼 섹션으로 자리 표시
//--------------------------------------------------------------------
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons ="";
    for(int i=1; i<=NUM_RELAYS; i++){
      String relayStateValue = relayState(i);
      buttons+= "<h4>릴레이(Relay) #" + String(i) + " - GPIO " + relayGPIOs[i-1] + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" "+ relayStateValue +"><span class=\"slider\"></span></label>";
    }
    return buttons;
  }
  return String();
}

//--------------------------------------------------------------------
// 릴레이
//--------------------------------------------------------------------
String relayState(int numRelay){
  if(RELAY_NO){
    if(digitalRead(relayGPIOs[numRelay-1])){
      return "";
    }
    else {
      return "checked";
    }
  }
  else {
    if(digitalRead(relayGPIOs[numRelay-1])){
      return "checked";
    }
    else {
      return "";
    }
  }
  return "";
}

//--------------------------------------------------------------------
// 설정
//--------------------------------------------------------------------
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Set all relays to off when the program starts - if set to Normally Open (NO), the relay is off when you set the relay to HIGH
  for(int i=1; i<=NUM_RELAYS; i++){
    pinMode(relayGPIOs[i-1], OUTPUT);
    if(RELAY_NO){
      digitalWrite(relayGPIOs[i-1], HIGH);
    }
    else{
      digitalWrite(relayGPIOs[i-1], LOW);
    }
  }
  
  // Wi-Fi 접속하기
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi 연결중..");
  }

  // 접속된 IP Address 출력
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?relay=<inputMessage>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    String inputMessage2;
    String inputParam2;
    // GET input1 value on <ESP_IP>/update?relay=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1) & request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam2 = PARAM_INPUT_2;
      if(RELAY_NO){
        Serial.print("켜기 ");
        digitalWrite(relayGPIOs[inputMessage.toInt()-1], !inputMessage2.toInt());
      }
      else{
        Serial.print("NC ");
        digitalWrite(relayGPIOs[inputMessage.toInt()-1], inputMessage2.toInt());
      }
    }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage + inputMessage2);
    request->send(200, "text/plain", "OK");
  });
  // Start server
  server.begin();
}

//--------------------------------------------------------------------
// 반복
//--------------------------------------------------------------------
void loop() {
}
