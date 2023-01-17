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
  NewPing(5, 5, TRAPCM), 
  NewPing(8, 8, TRAPCM),
  NewPing(9, 9, TRAPCM),
  NewPing(10, 10, TRAPCM),
  NewPing(11, 11, TRAPCM),
  NewPing(12, 12, TRAPCM),
  NewPing(13, 13, TRAPCM)
};

int active[10] = {0,0,0,0,0,0,0,0,0,0};

const char *soundFiles[] = {
  "1.mp3",
  "2.mp3",
  "3.mp3",
  "4.mp3",
  "5.mp3",
  "6.mp3",
  "7.mp3",
  "8.mp3",
  "9.mp3",
  "10.mp3",
};

void setup() {
  Serial.begin(115200);

  // Audio
  musicPlayer.begin();
  SD.begin(CARDCS);
  SD.open("/");
  musicPlayer.setVolume(VOLUME,VOLUME);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

}



void loop () {
    for (uint8_t i = 0; i < SONAR_NUM; i++) {

    int dist = sonar[i].ping_cm();
    if (dist != 0) {
      if (active[i] == 0) {
        musicPlayer.startPlayingFile(soundFiles[i]);
        active[i] = 1;
      }
    }// if dist
    else {
      active[i] = 0;
    }

    Serial.print(i);
    Serial.print("=");
    Serial.print(dist);
    Serial.print("cm ");

    delay(30);
  }// for
  Serial.println();
}// loop


