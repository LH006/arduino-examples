const char *service_name = "PROV_Kitchen";
char deviceName_1[] = "Kitchen Light";

// GPIO Setup
static uint8_t RelayPin1 = 23;
static uint8_t RelayPin2 = 19;

////////////////////////////////////////////////////////////
bool AAA(bool AA) {
  AA = false;
  //AA = true;
  return AA;
}
////////////////////////////////////////////////////////////
int AAA(int AA) {
  if (AA > 100) {
    AA = 1;
  } else {
    AA = 0;
  }
  return AA;
}
////////////////////////////////////////////////////////////
