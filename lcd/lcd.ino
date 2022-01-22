#include <LiquidCrystal.h>

const int rs=D6, en=D7, d5=D3, d4=D2, d3=D1, d2=D0;
LiquidCrystal lcd(rs, en, d5, d4, d3, d2);


//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  Serial.printf("starting...");
  lcd.begin(16, 2);
  lcd.print("Habla menor");
}

void loop() {
}
