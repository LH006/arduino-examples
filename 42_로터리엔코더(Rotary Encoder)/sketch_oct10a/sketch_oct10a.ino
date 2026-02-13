// Encoder pins configureren.
int pinEncA = D5;
int pinEncB = D6;

static byte abOud;       // Initialiseer status.
volatile int teller = 0; // rotatie teller.
int teller_oud;          // oude rotatie teller.

// Waarden voor variabel getal reserveren.
enum {BufSize = 6};
char tellerStr[BufSize];

/////////////////////////////////////////////
//
/////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  
  // Encoder pinnen instellen.
  pinMode(pinEncA, INPUT);
  pinMode(pinEncB, INPUT);

  // Interrupts instellen (pin hoog-laag verandering).
  // Interrupt 0 = Pin 2 op de Arduino UNO.
  // Interrupt 1 = Pin 3 op de Arduino UNO.
  attachInterrupt(0, pinActie, CHANGE);
  attachInterrupt(1, pinActie, CHANGE);
}


////////////////////////////////////////////////////
//
////////////////////////////////////////////////////
void loop() {
  // IF loop wanneer er aan de encoder is gedraaid.
  if (teller_oud != teller) {
    teller_oud = teller;
    snprintf(tellerStr, BufSize, "%d", teller);  // Converteer de "teller" INT naar STR (tbv OLED scherm)
  }
  Serial.print("Encoder: ");
  Serial.println(tellerStr);
  }

///////////////////////////////////////////////////////////////////
// Wanneer een interrupt heeft plaatsgevonden, lees de input pinnen, bereken nieuwe status, pas de telling aan.
//////////////////////////////////////////////////////////////////
void pinActie() {
  enum { upMask = 0x66, downMask = 0x99 };
  byte abNieuw = (digitalRead(pinEncA) << 1) | digitalRead(pinEncB);
  byte criteria = abNieuw ^ abOud;
  if (criteria == 1 || criteria == 2) {
    if (upMask & (1 << (2 * abOud + abNieuw / 2)))
      teller++;    // tel naar boven.
    else teller--; // tel naar beneden.
  }
  abOud = abNieuw; // bewaar nieuwe status.
}


/*// OLED scherm loop.
    u8g.firstPage();
    do {
      u8g.drawStr(0, 10, "Encoder:");

      u8g.drawBox(0, 14, 128, 16);    // Teken een witte rechthoek, 0px vanaf links, 14px van boven, 128px breed, 16px hoog.
      u8g.setColorIndex(0);           // zet kleur negatief (pixel uit).
      u8g.setScale2x2();              // maak het lettertype 2x groter.
      u8g.drawStr(25, 14, tellerStr); // print "teller" tekst.

      u8g.undoScale();                // zet het lettertype weer terug.
      u8g.setColorIndex(1);           // zet de kleur positief (pixel aan).
    } while( u8g.nextPage() );
  }
  // Overige code...
*/
