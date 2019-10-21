#ifndef _Node_H_
  #define _Node_H_

    #include <Arduino.h>

    class Node
    {
      public:
        Node();
        Node(String label , byte index , byte icon, byte mode);
        String getLabel();
        String label ;
        byte index;
        byte icon;
        byte mode;
        byte data;

      private:
        
    };

#endif