
#include "UI.h"

#define BLK_PWM_CHANNEL 7 // LEDC_CHANNEL_7

UI::UI() : isInited(0) {
}

void UI::begin(bool LCDEnable, bool SDEnable, bool SerialEnable) {
  // Correct init once
  if (isInited == true) {
    return;
  } else {
    isInited = true;
  }

  // UART
  if (SerialEnable == true) {
    Serial.begin(115200);
    Serial.flush();
    delay(50);
    Serial.print("M5Stack initializing...");
  }

  // LCD INIT
  if (LCDEnable == true) {
    Lcd.begin();
  }

  // TF Card
  if (SDEnable == true) {
    SD.begin(TFCARD_CS_PIN, SPI, 40000000);
  }

  if (SerialEnable == true) {
    Serial.println("OK");
  }
}


void UI::update() {
  //Button update
  BtnA.read();
  BtnB.read();
  BtnC.read();
  
  node.update();
  // n[0].update();

}

void UI::setBrightness(uint8_t brightness) {
  ledcWrite(BLK_PWM_CHANNEL, brightness);
}

int UI::getData(int index){
    return dataIn[index];
}

void UI::addNode(String Label,byte icon,byte mode){
    node.add(Label,1,icon,mode);
    // n.PushBack(node); 
}

void UI::writeData(int index,int data){
    
}

