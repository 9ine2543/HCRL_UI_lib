#include <Arduino.h>
#include "UI.h"

UI ui;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ui.begin();
  ui.Lcd.fillScreen(BLACK);
  ui.Lcd.setCursor(100, 100);
  ui.Lcd.setTextColor(WHITE);
  ui.Lcd.setTextSize(1);
  ui.Lcd.printf("Display Test!");

  ui.addNode("TEST",0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  ui.update();
  Serial.println(ui.BtnB.read());
}