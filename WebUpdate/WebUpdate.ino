#include "WIFI.h"

void setup(void) {
  initWIFI();
}

void loop(void) {
  handleUP();
}

/* #define LED 2

unsigned long tmrLED;
int ledState = 0;

void setup(void) {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop(void) {
  led();
}

void led() {
  if (millis() - tmrLED >= 500) {
    tmrLED = millis();
    digitalWrite(LED, ledState = !ledState);
  }
} */
