struct joystick_str
{
};
struct joystick_str joustick_1[];
struct joystick_str joustick_2[];

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct data_package_str
{
  byte j1PotX;
  byte j1PotY;
  byte j1Button;
  byte j2PotX;
  byte j2PotY;
  byte j2Button;
  byte pot1;
  byte pot2;
  byte tSwitch1;
  byte tSwitch2;
  byte button1;
  byte button2;
  byte button3;
  byte button4;
};
struct data_package_str data; // Create a variable with the above structure
