#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal.h>

#define BUTTON_PIN 13

#define DHTPIN 8
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE); 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint8_t menuSelected;

unsigned long previousMillis;
unsigned long delayMS;
float hum;  //Variabile in cui verrà inserita la % di umidità  
float temp; //Variabile in cui verrà inserita la temperatura    

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), changeDisplayMenu, RISING);

  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  lcd.clear();
  menuSelected = 0;

  previousMillis = 0;
  delayMS = 2000;
}

void loop() {
  changeReadValues();
  
  writeTemperature();
  writeHumidity();
}

void changeReadValues() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= delayMS) {
    previousMillis = currentMillis;
    // read humidity and temperature
    hum = dht.readHumidity();
    temp = dht.readTemperature();
  }
}

void changeDisplayMenu() {
  menuSelected++;
  menuSelected = menuSelected % 3;  

  Serial.print("Current selection: ");
  Serial.println(menuSelected);
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
