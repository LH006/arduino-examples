***
# []
#### 예제1
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
