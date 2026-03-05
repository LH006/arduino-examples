//#define _DEBUG

volatile short sVal;
volatile byte byArr[2];
int32_t frequency = 120000;
bool success = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
#ifdef _DEBUG /////////////////////////////////////////////////
  {
    Serial.print(frequency);
    delay(500);
  }
#endif /////////////////////////////////////////////////////////
}



  if (warn_failsafe == 2)      beep_code('L','N','N','D');                 //failsafe "find me" signal
  else if (warn_failsafe == 1) beep_code('S','M','L','M');                 //failsafe landing active         
  else if (warn_noGPSfix == 1) beep_code('S','S','N','M');       
  else if (beeperOnBox == 1)   beep_code('S','S','S','M');                 //beeperon
  else if (warn_vbat == 4)     beep_code('S','M','M','D');       
  else if (warn_vbat == 2)     beep_code('S','S','M','D');       
  else if (warn_vbat == 1)     beep_code('S','M','N','D');           
  else if (warn_runtime == 1 && f.ARMED == 1)beep_code('S','S','M','N'); //Runtime warning            
  else if (toggleBeep > 0)     beep(50);                                   //fast confirmation beep
  else { 
    buzzerIsOn = 0;
    BUZZERPIN_OFF;
  } 







///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void wheel_left_right(byte rx_byte2)
{
  // if (조건1) { ... } else if (조건2) { ... } else { ... }
  if (rx_byte2 == STEERING_WHEEL_LEFT_MIN)
  {
    g_spider_status[1] = STEERING_WHEEL_LEFT_MIN; // 운전방향 좌회전 (최소속도) : 81 7F(127)
  }
  else if (g_data_rx == STEERING_WHEEL_LEFT_MAX)
  {
    g_spider_status[1] = STEERING_WHEEL_LEFT_MAX; // 운전방향 좌회전 (최고속도) : 81 41(65)
  }
  else if (g_data_rx == STEERING_WHEEL_RIGHT_MIN)
  {
    g_spider_status[1] = STEERING_WHEEL_RIGHT_MIN; // 운전방향 우회전 (최소속도) : 81 01(1)
  }
  else if (g_data_rx == STEERING_WHEEL_RIGHT_MAX)
  {
    g_spider_status[1] = STEERING_WHEEL_RIGHT_MAX; // 운전방향 우회전 (최고속도) : 81 3F(63)
  }
}

