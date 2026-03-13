struct joystick_str
{
};
struct joystick_str joustick_1[];
struct joystick_str joustick_2[];
////////////////////////////////////////////////////////////////
struct data_status
{
  int16_t int_throttle;
  int16_t int_pitch;
  int16_t roll;
  int16_t yaw;
  boolean joy_button_l;
  boolean joy_button_r; // = false
  boolean aux1_button;
  boolean aux2_button;
  float battery_voltage;
};
struct data_status str_data_status;	// 생성


//사용방법
  str_data_status.joy_button_l = digitalRead(PIN_JOYSTICK_SW_L);
  str_data_status.joy_button_r = digitalRead(PIN_JOYSTICK_SW_R);
  str_data_status.battery_voltage = battery_value(0);
/////////////////////////////////////////////////////////////////
