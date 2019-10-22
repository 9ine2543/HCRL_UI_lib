#include <Arduino.h>
#include <UI.h>

UI Ui;
void setup(void)
{
  //Begin the Ui class with LIGHTGREY background (default = BLACK)
  Ui.begin(LIGHTGREY);
  Ui.setBrightness(100);

  //Add 18 node (MAX)
  for(int i = 0 ;i<8;i++){
    Ui.addNode("Input", 0, INPT);
	Ui.addNode("Output", 0, OUPT);
  }
  Ui.addNode("Input", 0, INPT);
  Ui.addNode("Input", 0, INPT);

  //Do some modification
  Ui.setSubLabel(1, "HUMID");
  Ui.setLabel(1, "Living");
  Ui.setLabelColor(1,CYAN);
  Ui.setSubLabel(3, "TEMP");
  Ui.setLabel(3, "Bed");
  Ui.setLabelColor(3, NAVY);
  Ui.setSubLabel(5, "FLOW");
  Ui.setLabel(5, "Outside");
  Ui.setLabelColor(5, GREEN);
    
}

bool con;
long last;
float i = 0;

void loop(void)
{
  //Try to update some data (Dout) and Connection Status (con)
  if (millis() - last > 3000) {
	  if (i < 500) i += 0.05;
	  else i = 0;
	  Ui.write(1, i);
	  Ui.write(3, i);
	  Ui.write(5, i);
	  Ui.write(7, i);
	  Ui.write(9, i);
	  Ui.write(11, i);
	  Ui.write(13, i);
	  Ui.write(15, i);
    con = !con;
    last = millis();
  }


  //Update Screen and Switch
  Ui.update(con);
}