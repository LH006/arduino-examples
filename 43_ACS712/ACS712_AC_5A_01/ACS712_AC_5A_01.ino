#define CURRENT_SENSOR A0


float current;
void setup() 
{
  Serial.begin(9600);
  pins_init();
}


void loop() {
  int sensor_max;
  sensor_max = getMaxValue();;
  current=(float)(sensor_max-512)/1024*5/185*1000000;
 Serial.print("Current[mA] : ");
 Serial.println(current,1);
}
void pins_init()
{
  pinMode(CURRENT_SENSOR,INPUT);
}
int getMaxValue()
{
  int sensorValue;
  int sensorMax = 0;
  uint32_t start_time = millis();
  while((millis()-start_time) <1000)
  {
    sensorValue = analogRead(CURRENT_SENSOR);
    if(sensorValue > sensorMax)
    {
      sensorMax = sensorValue;
    }
  }
  return sensorMax;
}

