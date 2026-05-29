#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <elapsedMillis.h>

#define DHTPIN 4
#define DHTTYPE DHT21
#define RELAY1_PIN 17
#define RELAY3_PIN 26

unsigned long sensorInterval = 500;
unsigned long displayInterval = 1000;

DHT dht(DHTPIN, DHTTYPE);
elapsedMillis sensorMillis;
elapsedMillis displayMillis;

LiquidCrystal_I2C lcd(0x27, 20, 4);
const int soilPin = 34;

int soilValue;
int soilPercentage;
float temperature;
float humidity;

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Selamat Datang!");
  delay(3000);
  lcd.clear();

  pinMode(soilPin, INPUT);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);

  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY3_PIN, LOW);

  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Monitoring");
  lcd.setCursor(0, 1);
  lcd.print("Suhu   : ");
  lcd.setCursor(0, 2);
  lcd.print("K.Udara: ");
  lcd.setCursor(0, 3);
  lcd.print("K.Tanah: ");
}

void loop() {

  // Baca sensor
  if (sensorMillis >= sensorInterval) {

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    soilValue = analogRead(soilPin);
    soilPercentage = map(soilValue, 4095, 0, 0, 100);
    soilPercentage = constrain(soilPercentage, 0, 100);

    sensorMillis = 0;
  }

  // Tampilkan ke LCD
  if (displayMillis >= displayInterval) {

    lcd.setCursor(9, 1);
    lcd.print("     ");
    lcd.setCursor(9, 1);
    if (isnan(temperature)) {
      lcd.print("Err");
    } else {
      lcd.print(temperature, 1);
      lcd.print(char(223));
      lcd.print("C");
    }

    lcd.setCursor(9, 2);
    lcd.print("     ");
    lcd.setCursor(9, 2);
    if (isnan(humidity)) {
      lcd.print("Err");
    } else {
      lcd.print(humidity, 1);
      lcd.print("%");
    }

    lcd.setCursor(9, 3);
    lcd.print("     ");
    lcd.setCursor(9, 3);
    lcd.print(soilPercentage);
    lcd.print("%");

    displayMillis = 0;
  }

  // Kontrol Relay 1 (fan)
  if (!isnan(temperature) && !isnan(humidity)) {
    if (temperature > 24 && humidity > 75) {
      digitalWrite(RELAY1_PIN, HIGH);
    } else {
      digitalWrite(RELAY1_PIN, LOW);
    }
  }

  // Kontrol Pompa
  if (soilPercentage < 30) {
    digitalWrite(RELAY3_PIN, HIGH);
  } else {
    digitalWrite(RELAY3_PIN, LOW);
  }
}
