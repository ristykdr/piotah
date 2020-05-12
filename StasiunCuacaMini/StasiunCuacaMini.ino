#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

/*SSID dan Password*/
const char* ssid="FlashPlus";
const char* pass="rasahmelumelu";

ESP8266WebServer server(80);

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

  Serial.print("Mencoba menghubungkan ke ");
  Serial.println(ssid);

  /*Hubungkan ke hotspot*/
  WiFi.begin(ssid,pass);

  /*Cek hubungan ke hotspot*/
  while (WiFi.status()!=WL_CONNECTED){
      delay(1000);
      Serial.print("#");
    }
  Serial.print(" ");
  Serial.print("Terhubung ke WiFi : ");
  Serial.println(ssid);
  Serial.print("Dengan IP : ");
  Serial.println(WiFi.localIP());

  server.on("/",handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.print("HTTP Server sudah aktif");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handle_OnConnect(){
    suhu = dht.readTemperature();
    kelembapan = dht.readHumidity();
    server.send(200,"text/html",kirimHTML(suhu, kelembapan));
  }

void handle_NotFound(){
    server.send(404,"text/plain","Tidak Ditemukan");
  }

String kirimHTML(float nilaiSuhu, float nilaiKelembapan){
    String ptr ="<!DOCTYPE html> <html>\n";
    ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr +="<title>Stasiun Cuaca Mini</title>\n";
    ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
    ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
    ptr +="</style>\n";
    ptr +="</head>\n";
    ptr +="<body>\n";
    ptr +="<div id=\"webpage\">\n";
    ptr +="<h1>Laporan Suhu dan Kelembapan</h1>\n";
    
    ptr +="<p>Suhu : ";
    ptr +=(int)nilaiSuhu;
    ptr +=" C</p>";
    ptr +="<p>Kelembapan : ";
    ptr +=(int)nilaiKelembapan;
    ptr +=" %</p>";
    
    ptr +="</div>\n";
    ptr +="</body>\n";
    ptr +="</html>\n";

    return ptr;
  }
