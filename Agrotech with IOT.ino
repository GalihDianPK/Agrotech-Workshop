#include <WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <elapsedMillis.h>

#define DHTPIN 4         // Pin sensor DHT
#define DHTTYPE DHT21    // Tipe sensor DHT
#define RELAY1_PIN 17    // Pin relay 1 (bisa kamu gunakan untuk fan/dll)
#define RELAY3_PIN 26    // Pin relay 3 (pompa)

const char* ssid = "UGMURO-INET";           // Ganti dengan SSID WiFi kamu
const char* password = "Gepuk15000";        // Ganti dengan password WiFi kamu
const char* writeAPIKey = "R58804BMDAAZQ16H";  // Ganti dengan Write API Key ThingSpeak kamu
const unsigned long channelID = 3112227;        // Ganti dengan Channel ID ThingSpeak kamu

// Interval waktu (ms)
unsigned long thingSpeakInterval = 15000;
unsigned long sensorInterval = 500;
unsigned long displayInterval = 1000;

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);
elapsedMillis thingSpeakMillis;
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
  lcd.setCursor(0, 1);
  lcd.print("WS Agroteknologi IoT");
  lcd.setCursor(3, 3);
  lcd.print("-- UG MURO --");
  delay(5000);
  lcd.clear();
  delay(2000);

  pinMode(soilPin, INPUT);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, LOW);  // Relay 1 OFF saat mulai (sesuaikan jika aktif LOW/HIGH)
  digitalWrite(RELAY3_PIN, LOW);  // Pompa OFF saat mulai

  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client);

  // Tampilkan judul di LCD
  lcd.setCursor(5, 0);
  lcd.print("Monitoring");
  lcd.setCursor(0, 1);
  lcd.print("Suhu   : ");
  lcd.setCursor(0, 2);
  lcd.print("K.Udara: ");
  lcd.setCursor(0, 3);
  lcd.print("K.Tanah: ");
}

void loop() {
  if (sensorMillis >= sensorInterval) {
    // Baca sensor tiap 0.5 detik
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    delay(10);
    soilValue = analogRead(soilPin);
    soilPercentage = map(soilValue, 4095, 0, 0, 100);
    soilPercentage = constrain(soilPercentage, 0, 100);

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("% \t");
    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.print("*C \t");
    Serial.print("Soil: ");
    Serial.print(soilPercentage);
    Serial.println("%");

    sensorMillis = 0;
  }

  if (displayMillis >= displayInterval) {
    // Tampilkan data di LCD
    lcd.setCursor(5, 0);
    lcd.print("Monitoring");

    lcd.setCursor(9, 1);
    lcd.print("       "); // Clear area
    lcd.setCursor(9, 1);
    if (isnan(temperature)) {
      lcd.print("Err ");
    } else {
      lcd.print(temperature, 1);
    }
    lcd.setCursor(16, 1);
    lcd.print(char(223));
    lcd.print("C");

    lcd.setCursor(9, 2);
    lcd.print("       ");
    lcd.setCursor(9, 2);
    if (isnan(humidity)) {
      lcd.print("Err ");
    } else {
      lcd.print(humidity, 1);
    }
    lcd.setCursor(17, 2);
    lcd.print("%");

    lcd.setCursor(9, 3);
    lcd.print("       ");
    lcd.setCursor(9, 3);
    lcd.print(soilPercentage);
    lcd.setCursor(17, 3);
    lcd.print("%");

    displayMillis = 0;
  }

  // Kontrol Relay 1 berdasarkan suhu dan kelembaban
  if (!isnan(temperature) && !isnan(humidity)) {  // Pastikan data valid
    if (temperature > 24 && humidity > 75) {
      digitalWrite(RELAY1_PIN, HIGH); // Relay 1 menyala
    } else {
      digitalWrite(RELAY1_PIN, LOW);  // Relay 1 mati
    }
  } else {
    digitalWrite(RELAY1_PIN, LOW);  // Jika data error, matikan relay 1
  }

  // Kontrol Pompa (Relay 3) berdasarkan kelembaban tanah
  if (soilPercentage < 30) {
    digitalWrite(RELAY3_PIN, HIGH);  // Pompa NYALA
  } else {
    digitalWrite(RELAY3_PIN, LOW);   // Pompa MATI
  }

  if (thingSpeakMillis >= thingSpeakInterval) {
    // Kirim data ke ThingSpeak tiap 15 detik
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(3, soilPercentage);
    int x = ThingSpeak.writeFields(channelID, writeAPIKey);

    if (x == 200) {
      Serial.println("Update successful.");
    } else {
      Serial.println("Update failed. HTTP error code: " + String(x));
    }

    thingSpeakMillis = 0;
  }
}
