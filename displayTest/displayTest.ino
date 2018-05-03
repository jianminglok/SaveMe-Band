#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <DisplayMod.h>//big library

#define OLED_RESET 4
DisplayMod display(OLED_RESET);

int hr = 4;
int min = 20;


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
  display.println();
  display.setCursor(0,0);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("SaveMe Band");
  display.println();
  display.println();
  display.display();//to show uploaded text
  delay(1000);
  display.clearDisplay();
}

void loop(){

  display.setTextSize(2);
  display.println(hr + ":" + min);
  display.setTextSize(1);
  display.println("Fri 20,7");
  display.println();
  display.display();
  ++ min;
  if(min == 60){
    min = 0;
    ++hr;
  }
  delay(1000);
  display.clearDisplay();
}
