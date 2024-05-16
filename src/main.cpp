#include <Arduino.h>

#include <wifiConnect.h>
#include <user.h>
#include <fProcess.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Fingerprint.h>




const String SSID = "Kilicarslan";
const String PASSWD = "14531453";



//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
WifiConnect connect(SSID, PASSWD);

User usr("bedir");
fProcess fp;

void setup() {

  fp.delDB();
  usr.setID(12);

  Serial.begin(9600);
  connect.Initialize();
  //fp.Initialize();
  fp.enRoll(usr);

  delay(20);

}


void loop(){

  while (!fp.logIn()) {
    Serial.println(" >>");
    delay(1000);
  }
  User u("");
  uint8_t temp_id;
  if ((temp_id = fp.logIn())) {
    
    u.setID(temp_id);
    //connect.matchTrue();
  }
  Serial.print("user id : "); Serial.println(u.getID());



}
