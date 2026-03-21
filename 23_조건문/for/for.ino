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