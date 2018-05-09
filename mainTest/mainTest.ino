#include <SPI.h>
#include <Wire.h>
#include <DisplayMod.h>//big library

#define OLED_RESET 4
DisplayMod display(OLED_RESET);


//VCC to 5v
//GND to GND
//SCL to arduino pin A5
//SDA to arduino pin A4
void setup(){

  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.setCursor(0,0);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("SaveMe Band");
  display.display();//to show uploaded text
  delay(1000);

}

void week(int x){
  //to get what week is it
  String week;
  switch (x) {
    case(1):
      week = "Sun";
      break;
    case(2):
      week = "Mon";
      break;
    case(3):
      week = "Tue";
      break;
    case(4):
      week = "Wed";
      break;
    case(5):
      week = "Thu";
      break;
    case(6):
      week = "Fri";
      break;
    case(7):
      week = "Sat";
      break;
  }
  return x;
}

void loop(){

  display.clearDisplay();
  display.setTextSize(2);
  display.println(hour() + ":" + minute());
  display.setTextSize(1);
  display.println(week(weekday()) + "," + day() + "," + month());

}
