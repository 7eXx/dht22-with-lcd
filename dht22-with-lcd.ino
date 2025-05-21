#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 8
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE); 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint32_t delayMS;
float hum;  //Variabile in cui verrà inserita la % di umidità  
float temp; //Variabile in cui verrà inserita la temperatura    

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  lcd.clear();

  delayMS = 2000;
}

void loop() {
  delay(delayMS);
  // read humidity and temperature
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  
  writeTemperature();
  writeHumidity();
}

void writeTemperature() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");
}

void writeHumidity() {
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(hum);
  lcd.print(" %");
}
