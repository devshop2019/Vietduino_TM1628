#include "tm1628ts.h"

//https://www.onetransistor.eu/2017/06/tm1628-7segment-display-arduino.html

//#define __UNO__
#define __ESP__

#if defined(__UNO__)
#define _DIO__PIN     9
#define _CLK__PIN     8
#define _STB__PIN     7

#else

#define _DIO__PIN     D5
#define _CLK__PIN     D6
#define _STB__PIN     D7

#endif

TM1628ts disp(_CLK__PIN, _DIO__PIN, _STB__PIN);

void setup() {
  Serial.begin(115200);

  Serial.println("Start! lan 2");
  
//  pinMode(13, OUTPUT);
//  digitalWrite(13, HIGH);
  
  Serial.println("Start11111111111");
  
  disp.init(5); // start with lowest intensity

  Serial.println("Start2222222222");
  
  delay(1000);
//  digitalWrite(13, LOW);

  for (int i = 8; i > 0; i--) {
    disp.putDigitAt(3, i);
//    disp.putNumberAt(i, 1, false, 2);
    
//    disp.putDigitAt(16, i);
    ShowREG();
    disp.writeBuffer();
    delay(10);
    Serial.println("Start3333333333333");
  }

while(0){
  if(Serial.available()){
    String k = Serial.readStringUntil('\n');
    int kVal = k.toInt();
    Serial.println(kVal);

    disp.tm_buffer[6] = disp.tm_digit[kVal];
    
//    disp.putDigitAt(1, k.toInt());
    ShowREG();
    disp.writeBuffer();
    disp.clearBuffer();
  }
}
Serial.println("Start44444444444");
  delay(300);

  for (int i = 7; i > 0; i--) {
    disp.clearBuffer(i);
    disp.writeBuffer();
    delay(150);
    Serial.println("Start555555555555");
  }
  
}

void loop() {
  byte rcv = disp.getKeyboard();

  digitalWrite(13, rcv > 0 ? HIGH : LOW);
  disp.clearBuffer();
  
//  disp.putNumberAt(rcv, 1, false, 10);

  disp.tm_buffer[6] = disp.tm_digit[2];
  
  disp.writeBuffer(); // command 3
  Serial.println(rcv, BIN);
  delay(100);
}

void ShowREG(){
  Serial.println(F("=======REG========"));
  for(int cf = 0; cf < 14; cf++){
    
    Serial.print(disp.tm_buffer[cf], HEX);
    Serial.print(F(" "));
  }
  Serial.println();
  Serial.println(F("=================="));
}


//void putDigitAt(byte digit, int pos)
//{
//        if ((pos < 0) || (pos > 7))
//                return;
//
//        for (int i = 0; i < 7; i++)
//                bitWrite(tm_buffer[i * 2], pos, bitRead(tm_digit[digit], 6 - i));
//}
