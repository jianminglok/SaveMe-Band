#define TINY_GSM_MODEM_SIM868
#define SMS_TARGET  "+60109829252" //target receiver

#include <TinyGsmClient.h>
#include <SoftwareSerial.h>
#include <TimeLib.h>

#define SerialMon Serial

SoftwareSerial SerialAT(2, 3); // RX, TX for sim868

#define DUMP_AT_COMMANDS
#define TINY_GSM_DEBUG SerialMon

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

int btn = 8;
int val = 0;

int buttonState;
int lastButtonState = HIGH;

String imei;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;

float gps_latitude;
float gps_longitude;
float gps_speed;
int gps_altitude;
int gps_view_satellites;
int gps_used_satellites;

void setup() {

  pinMode(btn, INPUT);

  SerialMon.begin(115200);

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
  DBG("Modem:", modemInfo);

  imei = modem.getIMEI();
  DBG("IMEI:", imei);

  modem.enableGPS();

}

void loop() {

  // This is only supported on SIMxxx series, used as an alternative for GPS
  String gsmLoc = modem.getGsmLocation();
  DBG("GSM location:", gsmLoc); 

  bool gps_fixstatus = modem.getGPS(&gps_latitude, &gps_longitude, &gps_speed, &gps_altitude, &gps_view_satellites, &gps_used_satellites);
  if ( gps_fixstatus ) {
    
    debugger.print(F("#GPS Location: LAT: "));
    debugger.println(gps_latitude);
    debugger.print(F(" LONG: "));
    debugger.println(gps_longitude);
    debugger.print(F(" SPEED: "));
    debugger.println(gps_speed);
    debugger.print(F(" ALTITUDE: "));
    debugger.println(gps_altitude);
    debugger.print(F(" USED SATELITES: "));
    debugger.println(gps_view_satellites);
    debugger.print(F(" VIEWED STELITES: "));
    debugger.println(gps_used_satellites);
  
    int gps_year, gps_month, gps_day, gps_hour, gps_minute, gps_second;
    if ( modem.getGPSTime(&gps_year, &gps_month, &gps_day, &gps_hour, &gps_minute, &gps_second) ) {
      //Sync time if it's diffrent.
      setTime(gps_hour, gps_minute, gps_second, gps_day, gps_month, gps_year);
      //set_time(gps_year, gps_month, gps_day, gps_hour, gps_minute, gps_second);
    }
    
  }

  // put your main code here, to run repeatedly:
  val = digitalRead(btn);  // read input value

  // If the switch changed, due to noise or pressing:
  if (val != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (val != buttonState) {
      buttonState = val;

    // if the button state has changed:
    // only toggle the LED if the new button state is HIGH
      if (val == HIGH) {
        debugger.println("Button is not pushed");  // turn LED OFF
      } else {
        // turn LED off:
        debugger.println("Button is pushed");
        sendSMS();  // turn LED ON
      }
    }
  }

  lastButtonState = val;
}

void sendSMS() {

  bool res;
  // put your setup code here, to run once:
  res = modem.sendSMS(SMS_TARGET, String("Hello from "));
  DBG("SMS:", res ? "OK" : "fail");

}

