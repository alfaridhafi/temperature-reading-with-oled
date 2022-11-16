#include <EEPROM.h>
#include <max6675.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <max6675.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED diplay width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
int address = 0;
byte value;
int addr = 0;
int l1;
int buz = 2;
int temp;
int temp1;
int ktcSO = 4;
int ktcCS = 6;
int ktcCLK = 5;
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
int Switch1 = A4;
int Switch2 = A5;

void setup() {
  Serial.begin(9600);
  // give the MAX a little time to settle
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  //  display.print("Test");
  display.display();
  delay(500);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  pinMode(Switch1, INPUT_PULLUP);
  pinMode(Switch2, INPUT_PULLUP);
  pinMode(buz, OUTPUT);
}

void loop() {
  // basic readout test
  int SW1 = digitalRead(Switch1);
  int SW2 = digitalRead(Switch2);
 
//   display.setCursor(1,24); display.print("EPROM="); display.print(address);
  if (SW1 == LOW) {
     temp = (ktc.readCelsius() * 2.008678) - 2057.47 + 1;
      temp= constrain(temp,0,500);
     int val1 = temp / 4;
      EEPROM.write(addr, val1);
      address = addr;
      l1 = EEPROM.read(address);
      address = address + 1;
      if (address == 350)
      address = 0;
      addr = addr + 1;
      if (addr == 350)
        addr = 0;
      if (address >= 300) {
     digitalWrite(buz,HIGH);
      } else {
       digitalWrite(buz,LOW);
      }
    
      display.clearDisplay();
      display.setCursor(1, 0); display.print("sensor1: "); display.print(" "); display.print(temp);
      display.setCursor(1, 10); display.print("EPPROM= "); display.print(address);
      display.display();
   
  }
  if (SW2 == LOW) {
   temp = (ktc.readCelsius() * 2.008678) - 2057.47 + 1;
     int val1 = temp / 4;
      EEPROM.write(addr, val1);
      address = addr;
      l1 = EEPROM.read(address);
      address = address + 1;
      if (address == 350)
      address = 0;
      addr = addr + 1;
      if (addr == 350)
        addr = 0;
      if (address >= 300) {
     digitalWrite(buz,HIGH);
      } else {
       digitalWrite(buz,LOW);
      }
      display.clearDisplay();
      display.setCursor(1, 0); display.print("sensor1: "); display.print(" "); display.print(temp);
      display.setCursor(1, 10); display.print("EPPROM= "); display.print(address);
      display.display();
  }
}
