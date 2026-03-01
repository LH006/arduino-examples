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
  Serial.println("Test");
  delay(500);
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

