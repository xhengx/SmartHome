#include "HomeSensors.h"


HomeSensors s;
void setup() {

  Serial.begin(115200);
 
}

void loop() {
  // put your main code here, to run repeatedly:
   String req = "{\"request_sensors\" : true, \"control\":{\"set_curtain_on\":true}}";
   String result = s.recive_request(req);
   Serial.println("res:" + result);
  delay(100000);
}


