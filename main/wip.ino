#define TINY_GSM_MODEM_SIM808
#define SMS_TARGET  "+60132699212" //target receiver

#include <TinyGsmClient.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>
#include <SPI.h>
#include <Wire.h>
#include <DisplayMod.h>
#include <TinyGsmClientSIM800.h>
//initiallize software serial
#define SerialMon Serial
SoftwareSerial SerialAT(2, 3); // RX, TX for sim868

// Disable AT command log spam for now
// #define DUMP_AT_COMMANDS 
#define TINY_GSM_DEBUG SerialMon

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

//initiate oled display
#define OLED_RESET 4
DisplayMod display(OLED_RESET);

//below here is a bunce of variables
#define btn 8//variables for button
int val = 0;
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;

//gsm thingie
String imei;

void setup() {

  pinMode(btn, INPUT);//set pin 8 as INPUT

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C
  display.setCursor(0,0);//something like a boot up screen
  display.setTextSize(2);
  display.println("SaveMeBand");
  display.display();

  Serial.begin(9600);

  SerialMon.begin(9600);

  delay(10);

  // Set your reset, enable, power pins here
  delay(3000);

  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  DBG("Initializing modem...");
  modem.init();

  String modemInfo = modem.getModemInfo();
  //DBG("Modem:", modemInfo);

  imei = modem.getIMEI();
  //DBG("IMEI:", imei);

}


void loop() {

  DBG("Waiting for network...");
  if (!modem.waitForNetwork()) {
    delay(1000);
    return;
  }

  if (modem.isNetworkConnected()) {
    DBG("Network connected");
  }

  DBG("Connecting to", apn);
  if (!modem.gprsConnect(diginet, digi, digi)) {
    delay(1000);
    return;
  }

  bool res = modem.isGprsConnected();
  DBG("GPRS status:", res ? "connected" : "not connected");
  
}

void sendSMS() {

  bool res;
  // put your setup code here, to run once:
  res = modem.sendSMS(SMS_TARGET, String("Hello from "));
  DBG("SMS:", res ? "OK" : "fail");

}

