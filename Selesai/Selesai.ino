#include <Tone.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// 'icon 1
 const unsigned char epd_bitmap_icons8_birthday_48 [] PROGMEM = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 
            0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x03, 0x01, 0x00, 0x00, 0xc0, 
            0xc1, 0x03, 0x03, 0x00, 0x00, 0xc0, 0xc1, 0x83, 0x03, 0x00, 0x00, 0xe0, 0x83, 0xc1, 0x07, 0x00, 
            0x00, 0xe0, 0x03, 0xc0, 0x07, 0x00, 0x00, 0xe0, 0x81, 0x81, 0x07, 0x00, 0x00, 0xc0, 0xc0, 0x03, 
            0x03, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x03, 0x01, 0x00, 0x00, 0xc0, 
            0xc1, 0x83, 0x03, 0x00, 0x00, 0xc0, 0xc1, 0x83, 0x03, 0x00, 0x00, 0xc0, 0xc1, 0x83, 0x03, 0x00, 
            0x00, 0xc0, 0xc1, 0x83, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x7f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 
            0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x8f, 0x3f, 0xfc, 0xe0, 0x00, 
            0x00, 0x01, 0x0c, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xc0, 0x03, 0x0e, 0x00, 0x00, 0xff, 0xff, 0xdf, 
            0x7f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 
            0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 
            0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 
            0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 
            0xff, 0x1f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0xff, 
            0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
      };

const unsigned char* gambarList[] = {
    epd_bitmap_icons8_birthday_48
};
const int jumlahGambar = 1;

unsigned long previousMillis = 0;
const long intervalGanti = 2000;

//====== Buzzer SET UP =====
Tone solo;
Tone bass;
Tone rythm;

const int t = 600;
const int tt = t * 2;
const int t14 = round(t * 1 / 4);
const int t24 = round(t * 2 / 4);
const int t34 = round(t * 3 / 4);

const int bassLedPin = A1;
const int rythmLedPin = A3;
const int soloLedPin = 7;

// Variabel baru untuk menghitung putaran
int loopCount = 0;
bool showSpecialMessage = false;
unsigned long messageStartTime = 0;
const long messageDuration = 4000;

void wait(Tone t) {
    while (t.isPlaying()) {
        tampilkanOLED();
    }
}

int bassLedState = LOW;
void switchBassLed() {
    bassLedState = !bassLedState;
    digitalWrite(bassLedPin, bassLedState);
}

int rythmLedState = LOW;
void switchRythmLed() {
    rythmLedState = !rythmLedState;
    digitalWrite(rythmLedPin, rythmLedState);
}

int soloLedState = LOW;
void switchSoloLed() {
    soloLedState = !soloLedState;
    digitalWrite(soloLedPin, soloLedState);
}

void setup(void) {
    u8g2.begin();
    tampilkanGambar();
    previousMillis = millis();

    pinMode(A0, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(bassLedPin, OUTPUT);
    pinMode(rythmLedPin, OUTPUT);
    pinMode(soloLedPin, OUTPUT);

    pinMode(2, OUTPUT);
    pinMode(8, OUTPUT);

    solo.begin(5);
    bass.begin(11);
    rythm.begin(0);

    solo.play(NOTE_D4, t34); switchSoloLed();
    wait(solo);
    solo.play(NOTE_D4, t14); switchSoloLed();
    wait(solo);
}

void tampilkanGambar() {
    u8g2.clearBuffer();
    u8g2.drawXBMP(39, 7, 48, 48, gambarList[0]);
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(52, 63, "22th");
    u8g2.sendBuffer();
}

void tampilkanPesanKhusus() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "HAPPY BIRTHDAY");
    u8g2.drawStr(0, 22, "SAYANGKU. JNGN");
    u8g2.drawStr(0, 34, "LUPA CUCI PIRING");
    u8g2.drawStr(0, 46, "HARI INI. ITU");
    u8g2.drawStr(0, 58, "KADOKU :v - frns");
    u8g2.sendBuffer();
}

void tampilkanOLED() {
    unsigned long currentMillis = millis();
    
    if (showSpecialMessage) {
        if (currentMillis - messageStartTime >= messageDuration) {
            showSpecialMessage = false;
            tampilkanGambar();
        }
        return;
    }

    if (currentMillis - previousMillis >= intervalGanti) {
        previousMillis = currentMillis;
        tampilkanGambar();
    }
}

void mainMusicLoop() {
   bass.play(NOTE_G3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_E4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);
      bass.play(NOTE_B3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_D4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);
      bass.play(NOTE_D4, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_G4, t); switchSoloLed();
            wait(rythm); 
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);

      bass.play(NOTE_D4, t); switchBassLed();
      rythm.play(NOTE_D5, t24); switchRythmLed();
            solo.play(NOTE_FS4, tt); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_FS5, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_A5, t14); switchRythmLed();
            wait(rythm);
      bass.play(NOTE_FS4, t); switchBassLed();
      rythm.play(NOTE_D5, t24); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_FS5, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_A5, t14); switchRythmLed();
            wait(rythm);
      bass.play(NOTE_A4, t); switchBassLed();
      rythm.play(NOTE_D5, t24); switchRythmLed();
            solo.play(NOTE_D4, t34); switchSoloLed();
            wait(rythm);        
      rythm.play(NOTE_FS5, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_A5, t14); switchRythmLed();    
            solo.play(NOTE_D4, t14); switchSoloLed();
            wait(rythm);

      bass.play(NOTE_D4, t); switchBassLed();
      rythm.play(NOTE_D5, t24); switchRythmLed();
            solo.play(NOTE_E4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_FS5, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_A5, t14); switchRythmLed();
            wait(rythm);        
      bass.play(NOTE_FS4, t); switchBassLed();
      rythm.play(NOTE_D5, t24); switchRythmLed();
            solo.play(NOTE_D4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_FS5, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_A5, t14); switchRythmLed();
            wait(rythm);         
      bass.play(NOTE_A4, t); switchBassLed();
      rythm.play(NOTE_D5, t24); switchRythmLed();
            solo.play(NOTE_A4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_FS5, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_A5, t14); switchRythmLed();
            wait(rythm);  


      bass.play(NOTE_G3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_G4, tt); switchSoloLed();
            wait(rythm);        
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);
      bass.play(NOTE_B3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);        
      bass.play(NOTE_D4, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_D4, t34); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();       
            solo.play(NOTE_D4, t14); switchSoloLed();
            wait(rythm);

      bass.play(NOTE_G3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_D5, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);        
      bass.play(NOTE_B3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_B4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);          
      bass.play(NOTE_D4, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_G4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);       

      bass.play(NOTE_C4, t); switchBassLed();
      rythm.play(NOTE_C5, t24); switchRythmLed();
            solo.play(NOTE_FS4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_E5, t14); switchRythmLed();  
            wait(rythm);
      rythm.play(NOTE_G5, t14); switchRythmLed();   
            wait(rythm);       
      bass.play(NOTE_E4, t);  switchBassLed();
      rythm.play(NOTE_C5, t24); switchRythmLed();
            solo.play(NOTE_E4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_E5, t14); switchRythmLed();   
            wait(rythm);
      rythm.play(NOTE_G5, t14); switchRythmLed();   
            wait(rythm);          
      bass.play(NOTE_G4, t); switchBassLed();
      rythm.play(NOTE_C5, t24); switchRythmLed();
            solo.play(NOTE_C5, t34); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_E5, t14); switchRythmLed();
            wait(rythm); 
      rythm.play(NOTE_G5, t14); switchRythmLed();     
            solo.play(NOTE_C5, t14); switchSoloLed();
            wait(rythm);

      bass.play(NOTE_G3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_B4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);         
      bass.play(NOTE_D3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_G4, t); switchSoloLed();
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm); 
      bass.play(NOTE_FS3, t); switchBassLed();
      rythm.play(NOTE_D5, t24); switchRythmLed();
            solo.play(NOTE_A4, t); switchSoloLed();
            wait(rythm);
            wait(rythm);
      rythm.play(NOTE_FS5, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_A5, t14); switchRythmLed();
            wait(rythm);          

      bass.play(NOTE_G3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed();
            solo.play(NOTE_G4, tt); switchSoloLed();
            wait(rythm);        
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);
      bass.play(NOTE_B3, t); switchBassLed();
      rythm.play(NOTE_G4, t24); switchRythmLed(); 
            wait(rythm);
      rythm.play(NOTE_B4, t14); switchRythmLed();
            wait(rythm);
      rythm.play(NOTE_D5, t14); switchRythmLed();
            wait(rythm);      
            solo.play(NOTE_D4, t34); switchSoloLed();
            wait(solo);
            solo.play(NOTE_D4, t14); switchSoloLed();
            wait(solo);
}

void loop(void) {
    if (showSpecialMessage) {
        tampilkanOLED();
        return;
    }

    tampilkanOLED();
    mainMusicLoop();

    loopCount++;
    if (loopCount >= 2) {
        showSpecialMessage = true;
        messageStartTime = millis();
        loopCount = 0;
        tampilkanPesanKhusus();
    }
}