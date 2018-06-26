

// include the library code:
#include <LiquidCrystal.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


unsigned long timer = 0;
int tt;
int input;
int input_q;
int f=0;
unsigned long input_tt=0;



ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  f^=0x1;
  if(tt==0xff)timer++;
  if(digitalRead(9))input_tt++;
  else input_tt=0;
  digitalWrite(0,f&0x01);
  
}








void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Time in ms:");


  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 16000;            // compare match register 16MHz/1000
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS10);    // No prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts

   pinMode(9,INPUT);
   pinMode(0,OUTPUT);
  
}

void loop() {
  if(input_tt>50)input=0x01;
  else input=0x00;

  if(input==1&& input_q==0){
    tt=0xff;
   // if(timer>50){
      lcd.setCursor(0, 1);
      lcd.print("                ");
      
   // }
    timer=0;
  }
  if(input==0&& input_q==1)tt=0x00;

  //if(timer>100){
    lcd.setCursor(0, 1);
    lcd.print(timer);
  //}
  
  input_q=input;
}
