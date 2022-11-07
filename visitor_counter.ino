#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD (0x27, 16, 2);

#define L_YL63 12
#define R_YL63 14

#define isLempty digitalRead(L_YL63)
#define isRempty digitalRead(R_YL63)

void setup() {
  pinMode(L_YL63, INPUT);
  pinMode(R_YL63, INPUT);


  LCD.init();
  LCD.backlight();

  LCD.setCursor(0, 0);
  LCD.print("Visitors: 00/??");
}

void loop() {
  LCD.setCursor(0, 1);
  LCD.print(isLempty);

  LCD.setCursor(2, 1);
  LCD.print(isRempty);
   
  delay(500);
}
