/*
  =====================================================================
  버    전 : Ver
  작 성 자 :
  컴파일러 : 아두이노
  참    고 : 
  내    용 : 
  =====================================================================
*/
///////////////////////////////////////////////////////////////////////////
#ifndef __INI_H__
#define __INI_H__

#define VER_VAR "1.0.0"

//#define EEPROM_SIZE 512
//#define EEPROM_INI 1
//#define EEPROM_WRITE 2

#define SERIAL_COPYRIGHT "Web S/W Ver.1.00 - Copyright (c) 2026 LH006"
//#define SERIAL_DISPAY_VER 1
//#define SERIAL_MENU_HOME  '1'      // 처음에 메뉴 한 번 출력


//#define SOUND_INTRO 1
//#define SOUND_SPOT 2
//#define SOUND_EMO 3
//#define SOUND_B 4


#define Pin_LED D4 // 보드 LED

#define RELAY_NO true // Set to true to define Relay as Normally Open (NO)
#define RELAYS_CONTROL_TOTAL 5  // 제어하려는 릴레이의 수를 정의 (5로 설정)
#define RELAYS_CONTROL_1 D5
#define RELAYS_CONTROL_2 D6
#define RELAYS_CONTROL_3 D7
#define RELAYS_CONTROL_4 D8
#define RELAYS_CONTROL_5 D9

#endif

///////////////////////////////////////////////////////////////////////////
// 변수에 네트워크 이름 비번
//#define YOUR_WIFI_SSID "LH"
//#define YOUR_WIFI_PASSWORD "77994422"

// 
//#define WEBHOOK_URL_GOOGLE "https://chat.google.com/room/AAQAyt1i_ys?cls=7"

// 
//#define ACCESTOKEN_KAKAO "ne0A6wbUXsj7L3MwhVjtYVgmrwzqa4IworDKgAAAF3PmFxtQ"