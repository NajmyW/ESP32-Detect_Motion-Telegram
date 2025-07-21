#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h> 
#include <TimeLib.h> 
#define BOTtoken "1234:AbCdEF" // Enter the bottoken you got from botfather
// #define CHAT_ID "" // Enter your chatID you got from chatid bot
// CONFIG WIFI;
const char* ssid = "";// Enter your WIFI SSID
const char* password = ""; // Enter your WIFI Password

// TELEGRAM API;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// CONFIG TIME
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// VARIABEL PIN
int buzzer = 21;
int sensor = 4;
int led = 15;
int last_second;

void handleNewMessages(int numNewMessages,String waktu) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text; 

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";
    if (text == "cek") {
        bot.sendMessage("872315394", "HELLO "+from_name+"!\nESP32 Active & Sensors are still Active\n"+"\nPukul: "+waktu, "");
        bot.sendMessage("5419391894", "HELLO "+from_name+"!\nESP32 Active & Sensors are still Active\n"+"\nPukul: "+waktu, "");
    }
    if(text == "/cek") {
        bot.sendMessage("872315394", "HELLO "+from_name+"!\nESP32 Active & Sensors are still Active\n"+"\nPukul: "+waktu, "");
        bot.sendMessage("5419391894", "HELLO "+from_name+"!\nESP32 Active & Sensors are still Active\n"+"\nPukul: "+waktu, "");
    }
  } 
}
// SETUP
void setup() {
Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // CONFIG WIFI CONNECTED;
  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
    a++;
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  // CONFIG TELEGRAM CONNECTED;
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  bot.sendMessage("872315394", "Wifi Connected!", "");
  bot.sendMessage("5419391894", "Wifi Connected!", "");
  bot.sendMessage("872315394", "System has Started!!", "");
  bot.sendMessage("5419391894", "System has Started!!", "");

  // PINMODE CONNECTED
pinMode(sensor,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(led,OUTPUT);
}

// LOOP;
void loop() {
  // TIME/DATE NOW
  timeClient.update();
  unsigned long rawTime = timeClient.getEpochTime() + 28800;
  if (rawTime != last_second){
  time_t t = rawTime;
  int jam = hour(t);
  String jamStr = jam < 10 ? "0" + String(jam) : String(jam);
  int menit = minute(t);
  String menitStr = menit < 10 ? "0" + String(menit) : String(menit);
  int detik = second(t);
  String detikStr = detik < 10 ? "0" + String(detik) : String(detik);
  String hari;
  switch (weekday(t)){
    case 1 :
      hari = "Minggu";
      break;
    case 2 :
      hari = "Senin";
      break;
    case 3 :
      hari = "Selasa";
      break;
    case 4 :
      hari = "Rabu";
      break;
    case 5 :
      hari = "Kamis";
      break;
    case 6 :
      hari = "Jumat";
      break;
    case 7 :
      hari = "Sabtu";
      break;
    }
  int tgl = day(t);
  String tglStr = tgl < 10 ? "0" + String(tgl) : String(tgl);
  int bln = month(t);
  String blnStr = bln < 10 ? "0" + String(bln) : String(bln);
  int thn = year(t);
  String thnStr = String(thn);
  String tanggal = hari + " " + tglStr + "/" + blnStr + "/" + thnStr;
  String waktu = jamStr + ":" + menitStr + ":" + detikStr;
  delay(100);
  last_second = rawTime;

  // PROGRAM SENSOR 
  long kondisi = digitalRead(sensor);
  int i = 0;
switch(kondisi) {
  case 1:
    bot.sendMessage("872315394", "TERDETEKSI ADA PERGERAKAN DISEKITAR! \n--------------\nSejak: "+tanggal+"\nPukul: "+waktu, "");
    bot.sendMessage("5419391894", "TERDETEKSI ADA PERGERAKAN DISEKITAR! \n--------------\nSejak: "+tanggal+"\nPukul: "+waktu, "");
while (i < 15) {
    digitalWrite(led,HIGH);
    Serial.println("Terdeteksi ada pergerakan!");
    digitalWrite(buzzer,HIGH);
    delay(300);
    digitalWrite(buzzer,LOW);
    delay(200);
  i++;
}
    break;
  default:
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    Serial.println("Tidak ada pergerakan");
// int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
// while (numNewMessages) {
//       Serial.println("got response");
//       handleNewMessages(numNewMessages,waktu);
//       numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//     }
}
}
  }
