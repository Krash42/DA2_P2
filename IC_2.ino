//www.nfeweekly.com
//2017.9.2
#include <DS3231.h>
//CLOCK_COD
DS3231 clock;
RTCDateTime dt;

//LED_COD
byte seven_seg_digits[21] = { B11110100,  // = 0
                              B11100000,  // = 1
                              B01001010,  // = 2
                              B10110010,  // = 3
                              B01000110,  // = 4
                              B10100110,  // = 5
                              B11111010,  // = 6
                              B11101100,  // = 7
                              B11011010,  // = 8
                              B01100110,   // = 9
                              B11111101,  // = 10
                              B01100001,  // = 11
                              B11011011,  // = 12
                              B11110011,  // = 13
                              B01100111,  // = 14
                              B10110111,  // = 15
                              B10111111,  // = 16
                              B11100001,  // = 17
                              B11111111,  // = 18
                              B11100111,  // = 19
                              B10011110,  // = E
                            };


// connect to the ST_CP of 74HC595 (pin 3,latch pin)
int latchPin7 = 3;
// connect to the SH_CP of 74HC595 (pin 4, clock pin)
int clockPin7 = 4;
// connect to the DS of 74HC595 (pin 2)
int dataPin7 = 2;

//8LED_A
int datapin8_A = 6; 
int clockpin8_A = 7;
int latchpin8_A = 8;

//8LED_B
int datapin8_B = 10; 
int clockpin8_B = 11;
int latchpin8_B = 12;

// We'll also declare a global variable for the data we're
// sending to the shift register:

byte dataA = 0;
byte dataB = 0;

void setup() {
  //Clock_COD
  Serial.begin(9600);

  // Initialize DS3231
  Serial.println("Initialize DS3231");;
  clock.begin();

  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);

  // Set from UNIX timestamp
  // clock.setDateTime(1397408400);

  // Manual (YYYY, MM, DD, HH, II, SS
  // clock.setDateTime(2016, 12, 9, 11, 46, 00);

  //LED_COD
  // Set latchPin, clockPin, dataPin as output
  pinMode(latchPin7, OUTPUT);
  pinMode(clockPin7, OUTPUT);
  pinMode(dataPin7, OUTPUT);

//8LED_A
  pinMode(datapin8_A, OUTPUT);
  pinMode(clockpin8_A, OUTPUT);  
  pinMode(latchpin8_A, OUTPUT);

//8LED_B
  pinMode(datapin8_B, OUTPUT);
  pinMode(clockpin8_B, OUTPUT);  
  pinMode(latchpin8_B, OUTPUT);
  
}

// display a number on the digital segment display
void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin7, LOW);

  // the original data (bit pattern)
  shiftOut(dataPin7, clockPin7, LSBFIRST, seven_seg_digits[digit]);

  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin7, HIGH);
}

//BokHors
byte BH_h_tens = 1,BH_h_ones = 1, BH_m = 1;
byte SSCS;
byte spkmin10, spkmin1, spksec10, spksec1;
byte pinkmin10, pinkmin1, pinksec10, pinkh;


//BH_h_tens = clock.dateFormat("h", dt) / 10;
//BH_h_ones = clock.dateFormat("h", dt) - BH_h_tens * 10;

//uint8_t ones,tens,hundreds;
//
//hundreds = number/100;
//number = number-hundreds*100;
//
//tens = number/10;
//ones = number-tens*10;


void shiftWrite8_A(int desiredPinA, boolean desiredStateA)
{
// This function lets you make the shift register outputs
// HIGH or LOW in exactly the same way that you use digitalWrite().

  bitWrite(dataA,desiredPinA,desiredStateA); //Change desired bit to 0 or 1 in "data"
  
  // Now we'll actually send that data to the shift register.
  // The shiftOut() function does all the hard work of
  // manipulating the data and clock pins to move the data
  // into the shift register:

  shiftOut(datapin8_A, clockpin8_A, MSBFIRST, dataA); //Send "data" to the shift register

  //Toggle the latchPin to make "data" appear at the outputs
  digitalWrite(latchpin8_A, HIGH); 
  digitalWrite(latchpin8_A, LOW); 
}

void shiftWrite8_B(int desiredPinB, boolean desiredStateB)
{
// This function lets you make the shift register outputs
// HIGH or LOW in exactly the same way that you use digitalWrite().

  bitWrite(dataB,desiredPinB,desiredStateB); //Change desired bit to 0 or 1 in "data"
  
  // Now we'll actually send that data to the shift register.
  // The shiftOut() function does all the hard work of
  // manipulating the data and clock pins to move the data
  // into the shift register:

  shiftOut(datapin8_B, clockpin8_B, MSBFIRST, dataB); //Send "data" to the shift register

  //Toggle the latchPin to make "data" appear at the outputs
  digitalWrite(latchpin8_B, HIGH); 
  digitalWrite(latchpin8_B, LOW); 
}



void Aplj()
{
  int index;

//7Seg
  byte Plus10;
  if (dt.hour>=13 && dt.hour<=21)
  {
  BH_h_tens = (dt.hour) / 12;
  BH_h_ones = (dt.hour) - BH_h_tens * 12;
  Plus10 = BH_h_ones + 10;
  
  sevenSegWrite(Plus10);
  }
  else if(dt.hour >= 22 && dt.hour <= 23)
  {
  BH_h_ones = (dt.hour) - 22;
  Plus10 = BH_h_ones + 10;
  
  sevenSegWrite(Plus10);
  }
  else
  {
  BH_h_tens = (dt.hour) / 10;
  BH_h_ones = (dt.hour) - BH_h_tens * 10;
  Plus10 = BH_h_ones + 10;
  
  sevenSegWrite(Plus10);
  }


//The Other Spks
  Spkmin10_A();
  Spksec10_A();
  Spksec1_A();
  Spkmin1_A();

    delay(2000);
}



void Capr()
{
  int index;

//Pinks
  pinksec10 = random(0,5);
  pinkh = random(0,9);

//7Seg
  sevenSegWrite(pinkh);
  

//The Other Spks
  Spkmin10_A();
  Pinksec10_A();
  Spksec1_A();
  Spkmin1_A();

  delay(100);
}

void EEEK()
{
  spkmin10 = 0;
  spkmin1 = 0;
  spksec10 = 0;
  spksec1 = 0;
  sevenSegWrite(20);
  
  Spkmin10_A();
  Spksec10_A();
  Spksec1_A();
  Spkmin1_A(); 

  delay(10000);
}

void M_PIE()
{
  delay(5000);
  }


//Pinks
void Pinksec10_A()
{
  if(pinksec10 == 1) 
  {
     shiftWrite8_A(4, LOW);
     shiftWrite8_A(3, LOW);
     shiftWrite8_B(4, LOW);
     shiftWrite8_B(6, LOW);
  }
  else if(pinksec10 == 2) 
  {
     shiftWrite8_A(4, HIGH);
     shiftWrite8_A(3, LOW);
     shiftWrite8_B(4, LOW);
     shiftWrite8_B(6, LOW);
  }
  else if(pinksec10 == 3) 
  {
     shiftWrite8_A(4, LOW);
     shiftWrite8_A(3, HIGH);
     shiftWrite8_B(4, LOW);
     shiftWrite8_B(6, LOW);
  }
  else if(pinksec10 == 4) 
  {
     shiftWrite8_A(4, LOW);
     shiftWrite8_A(3, LOW);
     shiftWrite8_B(4, HIGH);
     shiftWrite8_B(6, LOW);
  }
  else if(pinksec10 == 5) 
  {
     shiftWrite8_A(4, LOW);
     shiftWrite8_A(3, LOW);
     shiftWrite8_B(4, LOW);
     shiftWrite8_B(6, HIGH);
  }
   else
  {
     shiftWrite8_A(4, HIGH);
     shiftWrite8_A(3, HIGH);
     shiftWrite8_B(4, HIGH);
     shiftWrite8_B(6, HIGH);
  }
}

//Spks
void Spkmin10_A()
{
  if(spkmin10 == 0) 
  {
     shiftWrite8_A(0, LOW);
     shiftWrite8_A(2, LOW);
     shiftWrite8_B(0, LOW);
     shiftWrite8_B(7, LOW);
  }
  else if(spkmin10 == 1) 
  {
     shiftWrite8_A(0, HIGH);
     shiftWrite8_A(2, LOW);
     shiftWrite8_B(0, LOW);
     shiftWrite8_B(7, LOW);
  }
  else if(spkmin10 == 2) 
  {
     shiftWrite8_A(0, LOW);
     shiftWrite8_A(2, HIGH);
     shiftWrite8_B(0, LOW);
     shiftWrite8_B(7, LOW);
  }
  else if(spkmin10 == 3) 
  {
     shiftWrite8_A(0, LOW);
     shiftWrite8_A(2, LOW);
     shiftWrite8_B(0, HIGH);
     shiftWrite8_B(7, LOW);
  }
  else if(spkmin10 == 4) 
  {
     shiftWrite8_A(0, LOW);
     shiftWrite8_A(2, LOW);
     shiftWrite8_B(0, LOW);
     shiftWrite8_B(7, HIGH);
  }
   else
  {
     shiftWrite8_A(0, HIGH);
     shiftWrite8_A(2, HIGH);
     shiftWrite8_B(0, HIGH);
     shiftWrite8_B(7, HIGH);
  }
}

void Spksec10_A()
{
  if(spksec10 == 0) 
  {
     shiftWrite8_A(4, LOW);
     shiftWrite8_A(3, LOW);
     shiftWrite8_B(4, LOW);
     shiftWrite8_B(6, LOW);
  }
  else if(spksec10 == 1) 
  {
     shiftWrite8_A(4, HIGH);
     shiftWrite8_A(3, LOW);
     shiftWrite8_B(4, LOW);
     shiftWrite8_B(6, LOW);
  }
  else if(spksec10 == 2) 
  {
     shiftWrite8_A(4, LOW);
     shiftWrite8_A(3, HIGH);
     shiftWrite8_B(4, LOW);
     shiftWrite8_B(6, LOW);
  }
  else if(spksec10 == 3) 
  {
     shiftWrite8_A(4, LOW);
     shiftWrite8_A(3, LOW);
     shiftWrite8_B(4, HIGH);
     shiftWrite8_B(6, LOW);
  }
  else if(spksec10 == 4) 
  {
     shiftWrite8_A(4, LOW);
     shiftWrite8_A(3, LOW);
     shiftWrite8_B(4, LOW);
     shiftWrite8_B(6, HIGH);
  }
   else
  {
     shiftWrite8_A(4, HIGH);
     shiftWrite8_A(3, HIGH);
     shiftWrite8_B(4, HIGH);
     shiftWrite8_B(6, HIGH);
  }
}


void Spksec1_A()
{
  if(spksec1 == 0) 
  {
     shiftWrite8_A(5, LOW);
     shiftWrite8_A(6, LOW);
     shiftWrite8_B(1, LOW);
     shiftWrite8_B(2, LOW);
  }
   else if(spksec1 == 1) 
  {
     shiftWrite8_A(5, HIGH);
     shiftWrite8_A(6, LOW);
     shiftWrite8_B(1, LOW);
     shiftWrite8_B(2, LOW);
  }
  else if(spksec1 == 2) 
  {
     shiftWrite8_A(5, LOW);
     shiftWrite8_A(6, HIGH);
     shiftWrite8_B(1, LOW);
     shiftWrite8_B(2, LOW);
  }
  else if(spksec1 == 3) 
  {
     shiftWrite8_A(5, LOW);
     shiftWrite8_A(6, LOW);
     shiftWrite8_B(1, HIGH);
     shiftWrite8_B(2, LOW);
  }
  else if(spksec1 == 4) 
  {
     shiftWrite8_A(5, LOW);
     shiftWrite8_A(6, LOW);
     shiftWrite8_B(1, LOW);
     shiftWrite8_B(2, HIGH);
  }
  else if(spksec1 == 5) 
  {
     shiftWrite8_A(5, HIGH);
     shiftWrite8_A(6, HIGH);
     shiftWrite8_B(1, HIGH);
     shiftWrite8_B(2, HIGH);
  }
  else if(spksec1 == 6) 
  {
     shiftWrite8_A(5, HIGH);
     shiftWrite8_A(6, HIGH);
     shiftWrite8_B(1, LOW);
     shiftWrite8_B(2, LOW);
  }
  else if(spksec1 == 7) 
  {
     shiftWrite8_A(5, HIGH);
     shiftWrite8_A(6, LOW);
     shiftWrite8_B(1, HIGH);
     shiftWrite8_B(2, LOW);
  }
  else if(spksec1 == 8) 
  {
     shiftWrite8_A(5, HIGH);
     shiftWrite8_A(6, LOW);
     shiftWrite8_B(1, LOW);
     shiftWrite8_B(2, HIGH);
  }
  else if(spksec1 == 9) 
  {
     shiftWrite8_A(5, LOW);
     shiftWrite8_A(6, HIGH);
     shiftWrite8_B(1, HIGH);
     shiftWrite8_B(2, LOW);
  }
  else
  {
     shiftWrite8_A(5, LOW);
     shiftWrite8_A(6, HIGH);
     shiftWrite8_B(1, LOW);
     shiftWrite8_B(2, HIGH);
  }
}

void Spkmin1_A()
{
  if(spkmin1 == 0) 
  {
     shiftWrite8_A(1, LOW);
     shiftWrite8_A(7, LOW);
     shiftWrite8_B(5, LOW);
     shiftWrite8_B(3, LOW);
  }
   else if(spkmin1 == 1) 
  {
     shiftWrite8_A(1, HIGH);
     shiftWrite8_A(7, LOW);
     shiftWrite8_B(5, LOW);
     shiftWrite8_B(3, LOW);
  }
  else if(spkmin1 == 2) 
  {
     shiftWrite8_A(1, LOW);
     shiftWrite8_A(7, HIGH);
     shiftWrite8_B(5, LOW);
     shiftWrite8_B(3, LOW);
  }
  else if(spkmin1 == 3) 
  {
     shiftWrite8_A(1, LOW);
     shiftWrite8_A(7, LOW);
     shiftWrite8_B(5, HIGH);
     shiftWrite8_B(3, LOW);
  }
  else if(spkmin1 == 4) 
  {
     shiftWrite8_A(1, LOW);
     shiftWrite8_A(7, LOW);
     shiftWrite8_B(5, LOW);
     shiftWrite8_B(3, HIGH);
  }
  else if(spkmin1 == 5) 
  {
     shiftWrite8_A(1, HIGH);
     shiftWrite8_A(7, HIGH);
     shiftWrite8_B(5, HIGH);
     shiftWrite8_B(3, HIGH);
  }
  else if(spkmin1 == 6) 
  {
     shiftWrite8_A(1, HIGH);
     shiftWrite8_A(7, HIGH);
     shiftWrite8_B(5, LOW);
     shiftWrite8_B(3, LOW);
  }
  else if(spkmin1 == 7) 
  {
     shiftWrite8_A(1, HIGH);
     shiftWrite8_A(7, LOW);
     shiftWrite8_B(5, HIGH);
     shiftWrite8_B(3, LOW);
  }
  else if(spkmin1 == 8) 
  {
     shiftWrite8_A(1, HIGH);
     shiftWrite8_A(7, LOW);
     shiftWrite8_B(5, LOW);
     shiftWrite8_B(3, HIGH);
  }
  else if(spkmin1 = 9) 
  {
     shiftWrite8_A(1, LOW);
     shiftWrite8_A(7, HIGH);
     shiftWrite8_B(5, HIGH);
     shiftWrite8_B(3, LOW);
  }
  else
  {
     shiftWrite8_A(1, LOW);
     shiftWrite8_A(7, HIGH);
     shiftWrite8_B(5, LOW);
     shiftWrite8_B(3, HIGH);
  }
}



void loop() 
{
  //LED_COD
  dt = clock.getDateTime();

//spks
  spkmin10 = (dt.minute) / 10;
  spkmin1 = (dt.minute) - spkmin10 * 10;
  spksec10 = (dt.second) / 10;
  spksec1 = (dt.second) - spksec10 * 10;
  
  SSCS = random(0,19);
  
  if(SSCS >= 1 && SSCS <= 3)
  {
    Aplj();
    }
  else
  {
    Capr();
    }
  
//  if (dt.hour>=13 && dt.hour<=21)
//  {
//  BH_h_tens = (dt.hour) / 12;
//  BH_h_ones = (dt.hour) - BH_h_tens * 12;
//  
//  sevenSegWrite(BH_h_ones);
//  }
//  else if(dt.hour >= 22 && dt.hour <= 23)
//  {
//  BH_h_ones = (dt.hour) - 22;
//  
//  sevenSegWrite(BH_h_ones);
//  }
//  else
//  {
//  BH_h_tens = (dt.hour) / 10;
//  BH_h_ones = (dt.hour) - BH_h_tens * 10;
//  
//  sevenSegWrite(BH_h_ones);
//  }
  // suspend 4 seconds
//  delay(900);

  ////CLOCK_COD
  //  dt = clock.getDateTime();
  //
//    Serial.print("Long number format:          ");
//    Serial.println(clock.dateFormat("d-m-Y H:i:s", dt));
  //
  //  Serial.print("Long format with month name: ");
  //  Serial.println(clock.dateFormat("d F Y H:i:s",  dt));
  //
//    Serial.print("Short format witch 12h mode: ");
//    Serial.println(clock.dateFormat("jS M y, h:ia", dt));
  //
  //  Serial.print("Today is:                    ");
  //  Serial.print(clock.dateFormat("l, z", dt));
  //  Serial.println(" days of the year.");
  //
  //  Serial.print("Actual month has:            ");
  //  Serial.print(clock.dateFormat("t", dt));
  //  Serial.println(" days.");
  //
  //  Serial.print("Unixtime:                    ");
  //  Serial.println(clock.dateFormat("U", dt));
  //
  //  Serial.println();
  //
  //  delay(1000);

}
