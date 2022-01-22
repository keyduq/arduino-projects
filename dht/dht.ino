#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN D5
#define DHTTYPE DHT11

const int rs=D6, en=D7, d5=D3, d4=D2, d3=D1, d2=D0;
LiquidCrystal lcd(rs, en, d5, d4, d3, d2);
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  dht.begin();
  lcd.begin(16, 2);
}

void loop(){
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print((int)dht.readTemperature());
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humedad: ");
  lcd.print((int)dht.readHumidity());
  lcd.print("%");

  delay(1000);
}
