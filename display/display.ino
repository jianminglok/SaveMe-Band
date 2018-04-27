#include <SPI.h>
#include <Wire.h>
#include <min.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);



void setup(){

  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (
    display.display();
    delay(3000);
    display.clearDisplay();

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("SaveMe Band");
  display.display();//to show uploaded text

}

void loop(){


}
