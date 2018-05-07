#include <SPI.h>
#include <Wire.h>
#include <DisplayMod.h>//big library

#define OLED_RESET 4
DisplayMod display(OLED_RESET);

int count = 0;


//VCC to 5v
//GND to GND
//SCL to arduino pin A5
//SDA to arduino pin A4
void setup(){


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("SaveMeBand");
  display.println();
  display.println();
  display.display();//to show uploaded text
  delay(3000);

}

void loop(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(count);
  display.print(":");
  display.println(count);
  display.display();
  ++count;
  delay(1000);
}
