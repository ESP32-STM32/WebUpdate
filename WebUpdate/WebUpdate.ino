#include "WIFI.h"

void setup(void) {
  initWIFI();
}

void loop(void) {
  handleUP();
}

/* #define LED 2

unsigned long tmrLED;

void setup(void) {
  pinMode(LED, OUTPUT);
}

void loop(void) {
  led();
}

void led() {
  if (millis() - tmrLED >= 500) {
    tmrLED = millis();
    digitalWrite(LED, !digitalRead(LED));
  }
} */
