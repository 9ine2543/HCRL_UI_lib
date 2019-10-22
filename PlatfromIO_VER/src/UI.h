/**
    LCD:
        lcd.setBrightness(uint8_t brightness);
        Lcd.drawPixel(int16_t x, int16_t y, uint16_t color);
        Lcd.drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
        Lcd.fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        Lcd.fillScreen(uint16_t color);
        Lcd.drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        Lcd.drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color);
        Lcd.fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        Lcd.fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,int16_t delta, uint16_t color);
        Lcd.drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        Lcd.fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        Lcd.drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
        Lcd.fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
        Lcd.drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
        Lcd.drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h),
        Lcd.drawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg, uint8_t size);
        Lcd.setCursor(uint16_t x0, uint16_t y0);
        Lcd.setTextColor(uint16_t color);
        Lcd.setTextColor(uint16_t color, uint16_t backgroundcolor);
        Lcd.setTextSize(uint8_t size);
        Lcd.setTextWrap(boolean w);
        Lcd.printf();
        Lcd.print();
        Lcd.println();
        Lcd.drawCentreString(const char *string, int dX, int poY, int font);
        Lcd.drawRightString(const char *string, int dX, int poY, int font);
        Lcd.drawJpg(const uint8_t *jpg_data, size_t jpg_len, uint16_t x, uint16_t y);
        Lcd.drawJpgFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);
        Lcd.drawBmpFile(fs::FS &fs, const char *path, uint16_t x, uint16_t y);

    Button:
        BtnA/B/C.read();
        BtnA/B/C.isPressed();
        BtnA/B/C.isReleased();
        BtnA/B/C.wasPressed();
        BtnA/B/C.wasReleased();
        BtnA/B/C.wasreleasedFor()
        BtnA/B/C.pressedFor(uint32_t ms);
        BtnA/B/C.releasedFor(uint32_t ms);
        BtnA/B/C.lastChange();
 */
// #define ESP32

#ifndef _UI_H_
  #define _UI_H_
  
  #if defined(ESP32)

    #include <Arduino.h>
    #include <Wire.h>
    #include <SPI.h>
    #include "FS.h"
    #include "SD.h"

    #include "Display.h"
    #include "Node.h"
    #include "Vector.h"
    #include "utility/Config.h"
    #include "utility/Button.h"


    class UI
    {
      public:
        UI();
        void begin(uint16_t bgColor = 0, bool LCDEnable = true, bool SDEnable = true, bool SerialEnable = true);
        void update(bool isConnected);
        void setBrightness(uint8_t brightness);
		void addNode(String Label, byte icon, byte mode);

		//Mutator Method
        int getData(int index);
		float getDout(int index);
		String getLabel(int index);
		String getSubLabel(int index);

		//Accessor Method
        void write(int index, float data);
		void setLabel(int index, String label);
		void setSubLabel(int index, String sub);

		//Text Modification Method
		void setLabelColor(int index, uint16_t selected, uint16_t notSelected);
		void setLabelColor(int index, uint16_t notSelected);
		void setSubLabelColor(int index, uint16_t color);
		void setIconColor(int index, uint16_t on, uint16_t off);
		void setIconColor(int index, uint16_t color);
		void setDoutColor(int index, uint16_t color);

        // Button API
        #define DEBOUNCE_MS 10
        Button BtnA = Button(BUTTON_A_PIN, true, DEBOUNCE_MS);
        Button BtnB = Button(BUTTON_B_PIN, true, DEBOUNCE_MS);
        Button BtnC = Button(BUTTON_C_PIN, true, DEBOUNCE_MS);


        // LCD
        Display Lcd = Display();

        Vector<Node> n;
        

      private:
          bool isInited;
          Vector<int> dataIn;
          Vector<float> dataOut;
          byte index = 0;
          byte icheck = 0;
          
		  uint16_t backgroundColor = 0;

		  int last_page;

		  bool last_status;
    };
  #else
    #error “This library only supports boards with ESP32 processor.”
  #endif
#endif
