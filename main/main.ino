#include <NewPing.h>
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// Audio Setup
#define SHIELD_RESET  -1
#define SHIELD_CS     7
#define SHIELD_DCS    6
#define CARDCS 4
#define DREQ 3

// Adjust Volume
#define VOLUME 20

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);


// Sensor Setup
#define TRAPCM 10
#define SONAR_NUM 10
NewPing sonar[SONAR_NUM] = {
  NewPing(0, 0, TRAPCM),
  NewPing(1, 1, TRAPCM),
  NewPing(2, 2, TRAPCM),
  NewPing(3, 3, TRAPCM), 
  NewPing(4, 4, TRAPCM),
  NewPing(5, 5, TRAPCM),
  NewPing(10, 10, TRAPCM),
  NewPing(11, 11, TRAPCM),
  NewPing(12, 12, TRAPCM),
  NewPing(13, 13, TRAPCM)
};


void setup() {
  Serial.begin(115200);

  // Audio
  musicPlayer.begin();
  SD.begin(CARDCS);
  SD.open("/");
  musicPlayer.setVolume(VOLUME,VOLUME);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  printDirectory(SD.open("/"), 0);

}



void loop () {
    for (uint8_t i = 0; i < SONAR_NUM; i++) {
    delay(20);

    int dist = sonar[i].ping_cm();
    if (dist != 0) {
      musicPlayer.playFullFile("/1.mp3"); 
    }
    Serial.print(i);
    Serial.print("=");
    Serial.print(dist);
    Serial.print("cm ");
  }
  Serial.println();
}



void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}