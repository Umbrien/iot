#include <LiquidCrystal_I2C.h> // https://github.com/johnrickman/LiquidCrystal_I2C

// pinout
//
// left YL-63
// OUT - D6
// GND - GND
// VCC - 3V3
//
// right YL-63
// OUT - D5
// GND - GND
// VCC - 3V3
//
// I2C atached to 1602
// GND - GND
// VCC - Vin
// SDA - D2
// SCL - D1


LiquidCrystal_I2C LCD (0x27, 16, 2);

#define L_YL63 12
#define R_YL63 14

#define isLempty digitalRead(L_YL63)
#define isRempty digitalRead(R_YL63)

void print00(int startIndex, int rowIndex, int num) {
  if (num < 0 || num >= 10) {
    LCD.setCursor(startIndex, rowIndex);
    LCD.print(num);
  } else {
    LCD.setCursor(startIndex, rowIndex);
    LCD.print(0);
    LCD.setCursor(startIndex + 1, rowIndex);
    LCD.print(num);
  }
}

int visitors = 0;
#define maxVisitors 3

void setup() {
  pinMode(L_YL63, INPUT);
  pinMode(R_YL63, INPUT);

  LCD.init();
  LCD.backlight();

  LCD.setCursor(0, 0);
  LCD.print("Visitors: 00/??");

}

void loop() {

  print00(10, 0, visitors);
  print00(13, 0, maxVisitors);

  if (visitors == maxVisitors) {
    LCD.setCursor(0, 1);
    LCD.print("limit     ");
  } else if (visitors > maxVisitors) {
    LCD.setCursor(0, 1);
    LCD.print("OVERLIMIT!");
  } else {
    LCD.setCursor(0, 1);
    LCD.print("          ");
  }

  if (!isLempty) {
    visitors++;

     delay(1000);
     return;
  } else if (!isRempty) {
    visitors--;

     delay(1000);
  }
}
