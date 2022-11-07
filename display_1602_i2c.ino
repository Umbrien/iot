#include <Wire.h>
#include <LiquidCrystal_I2C.h> // https://drive.google.com/file/d/1r2xpfnR91NdUvty2Bzwl92XjbdGcPpz8/view

LiquidCrystal_I2C LCD (0x27, 16, 2);

void setup() {
  LCD.init();
  LCD.backlight();

  // first 0 is character start point
  // second 0 is line (0 or 1 for 1602)
  LCD.setCursor(0, 0);
  LCD.print("YURII chort");

  LCD.setCursor(0, 1);
  LCD.print("CHORT yurii");

}
