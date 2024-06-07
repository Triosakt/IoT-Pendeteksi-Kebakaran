#include "DHTesp.h"
#include <LiquidCrystal_I2C.h>

const int DHT_PIN = 15;
const int BUZZER = 18;

DHTesp dhtSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);//buzzer
  pinMode(5,OUTPUT);//led merah
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  lcd.init();
  lcd.backlight();
}

void loop() {
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  digitalWrite(BUZZER,HIGH) ; //Turn on active buzzer
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(data.temperature, 2) + " C");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 1);

delay(1000);
  lcd.clear();
  if (data.temperature < 20){
    lcd.print("AMAN");
    digitalWrite(5, LOW);
    noTone(BUZZER);
  }

  else if (data.temperature > 32){
    lcd.print("BAHAYA API!!!");
    digitalWrite(5, HIGH);
    tone(BUZZER,165);
  }

  else if (data.temperature > 20 < 32){
    lcd.print("TIDAK ADA API");
    digitalWrite(5, LOW);
    noTone(BUZZER);
  }

}