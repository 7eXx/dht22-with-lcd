#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal.h>

#define BUTTON_PIN 2

#define DHTPIN 8
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE); 

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

volatile uint8_t menuSelected = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

unsigned long previousMillis = 0;
const unsigned long delayMS = 2000;

float hum = 0;  //Variabile in cui verrà inserita la % di umidità  
float temp = 0; //Variabile in cui verrà inserita la temperatura
float minTemp = 1000, maxTemp = -1000;
float minHum = 1000, maxHum = -1000;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), changeDisplayMenu, FALLING);

  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  updateReadValues();

  Serial.print("Current selection: ");
  Serial.println(menuSelected);

  lcd.clear();
  switch (menuSelected) {
    case 0:
      displayTempHum();
      break;
    case 1:
      displayMinMaxTemp();
      break;
    case 2:
      displayMinMaxHum();
      break;
  }

  delay(500);
}

void updateReadValues() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= delayMS) {
    previousMillis = currentMillis;
    // read humidity and temperature
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    if (temp < minTemp) minTemp = temp;
    if (temp > maxTemp) maxTemp = temp;

    if (hum < minHum) minHum = hum;
    if (hum > maxHum) maxHum = hum;
  }
}

void changeDisplayMenu() {
  unsigned long currentTime = millis();
  // Simple debounce
  if (currentTime - lastDebounceTime >= debounceDelay) {
    menuSelected = (menuSelected + 1) % 3;
    lastDebounceTime = currentTime;
  }
}

void displayTempHum() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(hum);
  lcd.print(" %");
}

void displayMinMaxTemp() {
  lcd.setCursor(0, 0);
  lcd.print("MinT: ");
  lcd.print(minTemp);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("MaxT: ");
  lcd.print(maxTemp);
  lcd.print(" C");
}

void displayMinMaxHum() {
  lcd.setCursor(0, 0);
  lcd.print("MinH: ");
  lcd.print(minHum);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("MaxH: ");
  lcd.print(maxHum);
  lcd.print(" %");
}
