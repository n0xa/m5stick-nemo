/*
Last Updated: 30 Mar. 2018
By Anton Grimpelhuber (anton.grimpelhuber@gmail.com)
*/

// The TV-B-Gone for Arduino can use either the EU (European Union) or the NA (North America) database of POWER CODES
// EU is for Europe, Middle East, Australia, New Zealand, and some countries in Africa and South America
// NA is for North America, Asia, and the rest of the world not covered by EU

// Two regions!
#define NA 0 //set by a HIGH on REGIONSWITCH pin
#define EU 1 //set by a LOW on REGIONSWITCH pin

// What pins do what
#define LED 10 //LED indicator pin (built-in LED)
#define IRLED 9        //the IR sender LED / D5 on wemos D1 mini
#define TRIGGER 37       //the button pin / D6 on wemos D1 mini
#define REGIONSWITCH 39  //HIGH (1) = NA, LOW (0) = EU; Pin 5 / D1 (REGIONSWITCH) is HIGH (via in input pullup resistor) for North America, or you (the user) must wire it to ground to set the codes for Europe.

// Lets us calculate the size of the NA/EU databases
#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)));

// set define to 0 to turn off debug output
#define DEBUG 0
#define DEBUGP(x) if (DEBUG == 1) { x ; }

// Shortcut to insert single, non-optimized-out nop
#define NOP __asm__ __volatile__ ("nop")

// Not used any more on esp8266, so don't bother
// Tweak this if neccessary to change timing
// -for 8MHz Arduinos, a good starting value is 11
// -for 16MHz Arduinos, a good starting value is 25
#define DELAY_CNT 25

// Makes the codes more readable. the OCRA is actually
// programmed in terms of 'periods' not 'freqs' - that
// is, the inverse!
// #define freq_to_timerval(x) (F_CPU / 8 / x - 1)
#define freq_to_timerval(x) (x / 1000)

// The structure of compressed code entries
struct IrCode {
  uint8_t timer_val;
  uint8_t numpairs;
  uint8_t bitcompression;
  uint16_t const *times;
  uint8_t const *codes;
};

void xmitCodeElement(uint16_t ontime, uint16_t offtime, uint8_t PWM_code );
void quickflashLEDx( uint8_t x );
void delay_ten_us(uint16_t us);
void quickflashLED( void );
uint8_t read_bits(uint8_t count);
uint16_t rawData[300];
#define MAX_WAIT_TIME 65535 //tens of us (ie: 655.350ms)
IRsend irsend(IRLED);  // Set the GPIO to be used to sending the message.
extern const IrCode* const NApowerCodes[];
extern const IrCode* const EUpowerCodes[];
extern uint8_t num_NAcodes, num_EUcodes;
uint8_t bitsleft_r = 0;
uint8_t bits_r = 0;
uint8_t code_ptr;
volatile const IrCode * powerCode;
uint8_t read_bits(uint8_t count)
{
  uint8_t i;
  uint8_t tmp = 0;
  for (i = 0; i < count; i++) {
    if (bitsleft_r == 0) {
      bits_r = powerCode->codes[code_ptr++];
      bitsleft_r = 8;
    }
    bitsleft_r--;
    tmp |= (((bits_r >> (bitsleft_r)) & 1) << (count - 1 - i));
  }
  return tmp;
}
#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH
uint16_t ontime, offtime;
uint8_t i, num_codes;
uint8_t region;

void sendAllCodes()
{
  bool endingEarly = false; //will be set to true if the user presses the button during code-sending
  if (region == NA) {
    num_codes = num_NAcodes;
  } else {
    num_codes = num_EUcodes;
  }
  for (i = 0 ; i < num_codes; i++)
  {
    if (region == NA) {
      powerCode = NApowerCodes[i];
    }
    else {
      powerCode = EUpowerCodes[i];
    }
    const uint8_t freq = powerCode->timer_val;
    const uint8_t numpairs = powerCode->numpairs;
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(BIG_TEXT);
    M5.Lcd.setCursor(5, 1);
    M5.Lcd.println("TV-B-Gone");
    M5.Lcd.setTextSize(SMALL_TEXT);
    M5.Lcd.println("Front Key: Go/Pause");
    const uint8_t bitcompression = powerCode->bitcompression;
    code_ptr = 0;
    for (uint8_t k = 0; k < numpairs; k++) {
      uint16_t ti;
      ti = (read_bits(bitcompression)) * 2;
      offtime = powerCode->times[ti];  // read word 1 - ontime
      ontime = powerCode->times[ti + 1]; // read word 2 - offtime
      M5.Lcd.setTextSize(1);
      M5.Lcd.printf("rti = %d Pair = %d, %d\n", ti >> 1, ontime, offtime);
      rawData[k * 2] = offtime * 10;
      rawData[(k * 2) + 1] = ontime * 10;
      yield();
    }
    irsend.sendRaw(rawData, (numpairs * 2) , freq);
    // Hack: Set IRLED high to turn it off after each burst. Otherwise it stays on (active low)
    digitalWrite(IRLED, HIGH);
    yield();
    bitsleft_r = 0;
    delay_ten_us(20500);
    if (digitalRead(TRIGGER) == BUTTON_PRESSED)
    {
      while (digitalRead(TRIGGER) == BUTTON_PRESSED) {
        yield();
      }
      endingEarly = true;
      delay_ten_us(50000); //500ms delay
      quickflashLEDx(4);
      delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
      delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
      break; //exit the POWER code "for" loop
    }
  } 
  if (endingEarly == false)
  {
    delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
    delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
    quickflashLEDx(8);
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(BIG_TEXT);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("TV-B-Gone");
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.println("Front Key: Go/Pause");
  M5.Lcd.println("Side Key: Exit");
}

void delay_ten_us(uint16_t us) {
  uint8_t timer;
  while (us != 0) {
    for (timer = 0; timer <= DELAY_CNT; timer++) {
      NOP;
      NOP;
    }
    NOP;
    us--;
  }
}

void quickflashLED( void ) {
  digitalWrite(LED, LOW);
  delay_ten_us(3000);   // 30 ms ON-time delay
  digitalWrite(LED, HIGH);
}

void quickflashLEDx( uint8_t x ) {
  quickflashLED();
  while (--x) {
    delay_ten_us(25000);     // 250 ms OFF-time delay between flashes
    quickflashLED();
  }
}
