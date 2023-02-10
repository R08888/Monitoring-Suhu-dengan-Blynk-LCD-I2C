#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "MVL0V-6emdEBLETnnYMWS3ho7SvKVYxf";
char ssid[] = "TexasKost";// Your WiFi credentials.
char pass[] = "eviudahpwt";// Set password to "" for open networks.

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX [hubungkan pin rx esp -> pin tx arduino dan pin tx esp -> pin rx arduino]

#define ESP8266_BAUD 9600// Your ESP8266 baud rate:

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 4          // What digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
DHT dht(DHTPIN, DHTTYPE);


void setup() {  
  Serial.begin(9600);
  
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

  timer.setInterval(1000L, sendSensor);
  
  lcd.begin();
  lcd.backlight();  
  dht.begin();

}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  
}

void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
  lcd.setCursor(0, 0); //menentukan posisi kursor pada LCD. Argumen pertama adalah posisi horizontal (dari kiri ke kanan) dan argumen kedua adalah posisi vertikal (dari atas ke bawah). Dalam contoh di atas, posisi kursor akan ditempatkan pada kolom ke-0 baris ke-0.
  lcd.print("H : ");
  lcd.print(h);
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("T : ");
  lcd.print(t);
  lcd.print("C");
}