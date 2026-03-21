////////////////////////////////////
  for (int joystick = 0; joystick < 255; joystick++) {
    Serial.println(joystick);
    radio.write( &joystick, sizeof(joystick) );
     }
////////////////////////////////////
void InitIO(){ 
  for(int i = 0; i < 17; i++) pinMode(i, INPUT); 
  pinMode(virbrationMotorPin,OUTPUT);
  digitalWrite(virbrationMotorPin,LOW);  // Stop shacking of the gamepad
}
////////////////////////////////////

void DataUpdate(){
  
  for(int i = 3; i < 17; i++)  buttonState[i] = digitalRead(i);
  buttonState[0] = analogRead(0);
  buttonState[1] = analogRead(1);
  for(int i = 0; i < 4; i++)  joystick[i] = analogRead(i);
  for(int i = 4; i < 6; i++)  AnalogButton[i-4] = analogRead(i);
  
}
////////////////////////////////////