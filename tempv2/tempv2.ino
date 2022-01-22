#include <DHT.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "RTClib.h"
#include <ESP8266WiFi.h>

#define DHTPIN D5
#define DHTTYPE DHT11

// Network SSID
const char* ssid = "CocoWifi_EXT";
const char* wifiPwd = "kRqXUdpGgz8zj6";

DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
int timeChange = 5000;
String tempString;
String humidityString;
String currentTime;
char temp[6];
char humidity[4];
char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

void convertIntToChar(int data, char *output) {
  String dataString = String(data);
  dataString.toCharArray(output, dataString.length());
}

void setup(void) {
  Serial.begin(115200);

  #ifndef ESP8266
    while (!Serial); // wait for serial port to connect. Needed for native USB
  #endif
  
  Wire.begin();
  dht.begin();
  u8g2.begin();
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
  u8g2.setFontMode(0);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Connect Wifi
  WiFi.hostname("Arduino");
  WiFi.begin(ssid, wifiPwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wifi connected");

  // Mostrar IP
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop(void) {
  u8g2.firstPage();
  DateTime now = rtc.now();
  String hours = String(now.hour());
  String minutes = String(now.minute());
  if (now.hour() < 10) {
    hours = "0" + hours;
  }
  if (now.minute() < 10) {
    minutes = "0" + minutes;
  }
  currentTime = hours + ":" + minutes;
//  strcpy(currentTime, now.hour());
//  strcat(currentTime, ":");
//  strcat(currentTime, now.minute());
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(currentTime);
  Serial.println();
  do {
//    u8g2.setFont(u8g2_font_open_iconic_embedded_1x_t);
//    u8g2.drawGlyph(120, 8, 80);
    u8g2.clear();
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawGlyph(32, 24, 259);
    u8g2.drawGlyph(32, 56, 152);
    u8g2.setFont(u8g2_font_ncenB14_tf);
    tempString = String((int)dht.readTemperature()) + "°C";
    tempString.toCharArray(temp, 6);
    u8g2.drawUTF8(56, 24, temp);
    humidityString = String((int)dht.readHumidity()) + "%";
    humidityString.toCharArray(humidity, 4);
    u8g2.drawUTF8(56, 56, humidity);
  } while ( u8g2.nextPage() );
  delay(timeChange);
  do {
    u8g2.clear();
    
    u8g2.drawUTF8(40, 24, currentTime.c_str());
    u8g2.drawUTF8(32, 56, daysOfTheWeek[now.dayOfTheWeek()]);
  } while ( u8g2.nextPage() );
  delay(timeChange);
}
