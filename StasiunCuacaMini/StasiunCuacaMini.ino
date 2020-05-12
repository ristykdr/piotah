#include <DHT.h>
#define DHTTYPE DHT22
//INISIASI PIN
uint8_t pinDHT = D7;

DHT dht(pinDHT,DHTTYPE); //INISIASI DHT

float suhu;
float kelembapan;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinDHT,INPUT);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

  Serial.print("Suhu : ");
  Serial.println(suhu);
  Serial.print("Kelambapan : ");
  Serial.println(kelembapan);

  delay(1000);

}
