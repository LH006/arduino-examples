/* ---------------------------------------------------------------------
* 사용 CPU : ATmega328 		[CPU:16MZh]
* 날    짜 :
* 버    전 : Ver0.0
* 작 성 자 :
* 컴파일러 : 아두이노
* 참    고 : 
* 내    용 :
    -  LCD 핀  -
 * LCD R/W pin5 = 접지에 연결
 * LCD VSS pin1 = 접지에 연결
 * LCD VCC pin2 = +5V에 연결

* ------------------------------------------------------------------- */
/* -------------------------------------------------------------------
*    P I N 정보 예) (Key Switch)(LCD Data bit 0)(LED)
*  -------------------------------------------------------------------*/
#define LCD_RS_Pin 2
#define LCD_Enable_Pin 3
#define LCD_D4_Pin 4
#define LCD_D5_Pin 5
#define LCD_D6_Pin 6
#define LCD_D7_Pin 7 

/* --------------------------------------------------------------------
* I N C L U D E  …을 (부분·요소 등으로서) 포함하다
* --------------------------------------------------------------------- */
#include <LiquidCrystal.h>

/* --------------------------------------------------------------------
* 객체 선언 (create object)
* --------------------------------------------------------------------- */
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS_Pin, LCD_Enable_Pin, LCD_D4_Pin, LCD_D5_Pin, LCD_D6_Pin, LCD_D7_Pin);

/* --------------------------------------------------------------------
* G L O B A L   V A R I A B L E (전역  변수 선언)
* --------------------------------------------------------------------- */

/* --------------------------------------------------------------------
* 함수 선언
* --------------------------------------------------------------------- */

/* --------------------------------------------------------------------
* 포트 초기내용 설정(이니셜라이즈)
* --------------------------------------------------------------------- */
void setup() {
  lcd.begin(16, 2); //LCD 16X2 설정
  lcd.print("hello, world!");
}

void loop() {
  lcd.noDisplay();  // Turn off the display:
  delay(500);
  lcd.display();  // Turn on the display:
  delay(500);
  
    // set the cursor to column 0, line 1
   // (note: line 1 is the second row, since counting begins with 0):
   lcd.setCursor(0, 1);
   // print the number of seconds since reset:
   lcd.print(millis()/1000);
}

/*
-Blink: control of the block-style cursor. 
-Cursor: control of the underscore-style cursor. 
-Display: quickly blank the display without losing what's on it. 
-TextDirection: control which way text flows from the cursor. 
-Scroll: scroll text left and right. 
-Serial input: accepts serial input, displays it. 
-SetCursor: set the cursor position. 
-Autoscroll: shift text right and left. 
*/
