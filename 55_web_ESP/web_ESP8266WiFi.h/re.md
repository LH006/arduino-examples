# ESP32 - ESP8266
## aaa
```C++
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#elif defined(ESP32)
#include <WiFi.h> //ESP32
#endif
```

[소켓 시리얼 모니터](
https://github.com/tzapu/WebSocketSerialMonitor/tree/master)