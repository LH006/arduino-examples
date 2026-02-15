
#### 예제1
```
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
```
#ifdef _DEBUG
  {
    Serial.print(frequency);
    delay(500);
  }
#endif
```