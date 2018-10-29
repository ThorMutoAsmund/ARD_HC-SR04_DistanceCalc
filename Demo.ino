#include <Arduino.h>

#include <TM1637Display.h>
#include <Ultrasonic.h>

#define BTN 1
#define CLK 2
#define DIO 3
#define TRIG 4
#define ECHO 5

// Default 3000us = 50 cm
#define MAX_TIMEOUT 30000

TM1637Display display(CLK, DIO);
Ultrasonic ultrasonic(TRIG, ECHO, MAX_TIMEOUT);

void setup()
{
  Serial.begin(9600);
  pinMode(BTN, INPUT);
  delayMicroseconds(100);
}

void loop()
{
  long infinte = MAX_TIMEOUT /29 / 2;
  uint8_t blank[] = { 0,0,0,0 };
  uint8_t inf[] = { SEG_G,SEG_G,SEG_G,SEG_G };
  long range;
  display.setBrightness(0x0f);
  display.setSegments(blank);
  delay(250);
  display.setSegments(inf);

  while(1)
  {
    int buttonState = digitalRead(BTN);
    if (buttonState == LOW) {
      display.setSegments(blank);
      delay(250);

      // turn LED on:
      range = ultrasonic.Ranging(CM);
      if (range == infinte)
      {
        Serial.println("infinite" );
        display.setSegments(inf);
      }
      else{
        Serial.print(range); // CM or INC
        Serial.println(" cm" );
        display.showNumberDec(range, false, 4, 0);
      }
      while (buttonState == LOW)
      {
        buttonState = digitalRead(BTN);
      }
   }
  }
}

// void loop2()
// {
//   uint8_t data[] = { SEG_G,SEG_G,SEG_G,SEG_G };
//   display.setBrightness(0x0f);

//   display.showNumberDec(4773, false, 4, 0);    
//   delay(TEST_DELAY);

//   data[0] = 0;
//   data[1] = SEG_B | SEG_C | SEG_G;
//   data[2] = SEG_G;
//   data[3] = 0;
//   display.setSegments(data);
//   delay(TEST_DELAY);

//   display.showNumberDec(2930, false, 4, 0);    
//   delay(TEST_DELAY);

//   data[0] = 0;
//   data[1] = SEG_D | SEG_G;
//   data[2] = SEG_D | SEG_G;
//   data[3] = 0;
//   display.setSegments(data);
//   delay(TEST_DELAY);

//   display.showNumberDec(4773+2930, false, 4, 0);    
  // delay(TEST_DELAY);


  // uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  // data[0] = display.encodeDigit(1);
  // data[1] = display.encodeDigit(2);
  // data[2] = display.encodeDigit(8);
  // data[3] = display.encodeDigit(0);
	// display.setSegments(data, 4, 0);
  // delay(TEST_DELAY);



  // for (int i=0; i<=9999; i+=1) {
  //   display.showNumberDec(i, false, 4, 0);    
  // }


  // // Done!
  // display.setSegments(SEG_DONE);

//   while(1);
// }

// void unused()
// {
//   int k;
//   uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
//   display.setBrightness(0x0f);

//   // All segments on
//   display.setSegments(data);
//   delay(TEST_DELAY);

//   // Selectively set different digits
//   data[0] = 0b01001001;
//   data[1] = display.encodeDigit(1);
//   data[2] = display.encodeDigit(2);
//   data[3] = display.encodeDigit(3);

//   for(k = 3; k >= 0; k--) {
// 	display.setSegments(data, 1, k);
// 	delay(TEST_DELAY);
// 	}

//   display.setSegments(data+2, 2, 2);
//   delay(TEST_DELAY);

//   display.setSegments(data+2, 2, 1);
//   delay(TEST_DELAY);

//   display.setSegments(data+1, 3, 1);
//   delay(TEST_DELAY);


//   // Show decimal numbers with/without leading zeros
//   bool lz = false;
//   for (uint8_t z = 0; z < 2; z++) {
// 	for(k = 0; k < 10000; k += k*4 + 7) {
// 		display.showNumberDec(k, lz);
// 		delay(TEST_DELAY);
// 	}
// 	lz = true;
//   }

//   // Show decimal number whose length is smaller than 4
//   for(k = 0; k < 4; k++)
// 	data[k] = 0;
//   display.setSegments(data);

// 	// Run through all the dots
// 	for(k=0; k <= 4; k++) {
// 		display.showNumberDecEx(0, (0x80 >> k), true);
// 		delay(TEST_DELAY);
// 	}

//   display.showNumberDec(153, false, 3, 1);
//   delay(TEST_DELAY);
//   display.showNumberDec(22, false, 2, 2);
//   delay(TEST_DELAY);
//   display.showNumberDec(0, true, 1, 3);
//   delay(TEST_DELAY);
//   display.showNumberDec(0, true, 1, 2);
//   delay(TEST_DELAY);
//   display.showNumberDec(0, true, 1, 1);
//   delay(TEST_DELAY);
//   display.showNumberDec(0, true, 1, 0);
//   delay(TEST_DELAY);

//   // Brightness Test
//   for(k = 0; k < 4; k++)
// 	data[k] = 0xff;
//   for(k = 0; k < 7; k++) {
//     display.setBrightness(k);
//     display.setSegments(data);
//     delay(TEST_DELAY);
//   }
  
//   // On/Off test
//   for(k = 0; k < 4; k++) {
//     display.setBrightness(7, false);  // Turn off
//     display.setSegments(data);
//     delay(TEST_DELAY);
//     display.setBrightness(7, true); // Turn on
//     display.setSegments(data);
//     delay(TEST_DELAY);  
//   }

//   // Negative numbers
//   display.showNumberDec(-1);
//   delay(TEST_DELAY);
//   display.showNumberDec(-12);
//   delay(TEST_DELAY);
//   display.showNumberDec(-123);
//   delay(TEST_DELAY);
//   display.showNumberDec(-1, true);
//   delay(TEST_DELAY);
//   display.showNumberDec(-12, true);
//   delay(TEST_DELAY);
//   display.showNumberDec(-123, true);
//   delay(TEST_DELAY);

//   // Done!
//   display.setSegments(SEG_DONE);

//   while(1);
// }

