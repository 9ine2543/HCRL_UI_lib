#ifndef _Node_H_
  #define _Node_H_

    #include <Arduino.h>

    class Node
    {
      public:
        Node();
        Node(String label , byte index , byte icon, byte mode);

        String label;
		String subLabel;
        byte index;
        byte icon;
        byte mode;
        byte data;

		float dout;
		float last;

		uint16_t labelColorSelected;
		uint16_t labelColorNotSelected;
		uint16_t subLabelColor;
		uint16_t iconColorOn;
		uint16_t iconColorOff;
		uint16_t doutColor;

      private:
        
    };

#endif