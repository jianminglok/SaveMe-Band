#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <displayMod.h>//big library

#define OLED_RESET 4
displayMod display(OLED_RESET);

//VCC to 5v
//GND to GND
//SCL to arduino pin A5
//SDA to arduino pin A4
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
  display.println("");
  display.display();//to show uploaded text

}

void loop(){


}
