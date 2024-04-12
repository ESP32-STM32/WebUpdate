#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "web.h"

//#define LOCAL_ON  // Подключатся к домашней сети
#define AP_ON     // Создать точку доступа

const char* host = "esp32";  // http://ИМЯ_ХОСТА.local

#define LOCAL_SSID "iPhone 5s"  // Имя домашней WIFI сети
#define LOCAL_PASS "12345678"    // Пароль домашней WIFI сети

#define AP_SSID "ESP32"     // Имя точки доступа
#define AP_PASS "12345678"  // Пароль точки доступа

unsigned long tmrHandle;

WebServer server(80);

IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void initWIFI() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Запуск прошивки...");

#ifdef LOCAL_ON
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
#endif

#ifdef AP_ON
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
#endif

  MDNS.begin(host);
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", Web_page);
  });
  server.on("/update", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    },
    []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        Serial.printf("Фаил прошивки: %s\n", upload.filename.c_str());
        if (!Update.begin()) {  //начинаем с максимально доступного размера
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) {  //true, чтобы установить размер текущего прогресса
          Serial.printf("Прошивка завершена: %u\nПерезагрузка...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      } else {
        Serial.printf("Неожиданный сбой обновления (вероятно, разорвано соединение): статус=%d\n", upload.status);
      }
    });
  server.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.printf("\nОткройте http://%s.local в вашем браузере\n", host);
}

void handleUP() {
  if (millis() - tmrHandle >= 2) {
    tmrHandle = millis();
    server.handleClient();
  }
}
