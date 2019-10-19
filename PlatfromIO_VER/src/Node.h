#ifndef _Node_H_
  #define _Node_H_
  
  #if defined(ESP32)

    #include <Arduino.h>
    #include <Wire.h>
    #include <SPI.h>
    #include "FS.h"
    #include "SD.h"

    #include "Display.h"
    #include "Vector.h"
    #include "utility/Config.h"
    #include "utility/Button.h"


    class Node
    {
      public:
        Node();
        void add(String label , byte index , byte icon, byte mode);
        void update();

        #define DEBOUNCE_MS 10
        Button BtnA = Button(BUTTON_A_PIN, true, DEBOUNCE_MS);
        Button BtnB = Button(BUTTON_B_PIN, true, DEBOUNCE_MS);
        Button BtnC = Button(BUTTON_C_PIN, true, DEBOUNCE_MS);


        // LCD
        Display Lcd = Display();

      private:
        String label ;
        byte index;
        byte icon;
        byte mode;
        byte data;
    };

  #else
    #error “This library only supports boards with ESP32 processor.”
  #endif
#endif