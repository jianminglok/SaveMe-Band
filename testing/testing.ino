#define TINY_GSM_MODEM_SIM868;
#define SMS_TARGET  "+60132699212" //target receiver

#include <TinyGsmClient.h>;
#include <SoftwareSerial.h>;

SoftwareSerial SerialAT(2, 3); // RX, TX for sim868

//#define DUMP_AT_COMMANDS
#define TINY_GSM_DEBUG SerialMon

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

int btn = 4;
int ledPin = 13;
int ledState = LOW;
int val = 0;

int buttonState;
int lastButtonState = HIGH;

String imei;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;

void setup() {

  pinMode(btn, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

  Serial.begin(115200);

  delay(10);

  // Set your reset, enable, power pins here

  delay(3000);

  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  Serial.println(F("Initializing modem..."));
  modem.init();

  String modemInfo = modem.getModemInfo();
  Serial.print(F("Modem: "));
  Serial.println(modemInfo);

  imei = modem.getIMEI();
  Serial.print("IMEI:" + imei);

}

void loop() {

  modem.enableGPS();
  String gps_latitude;
  String gps_longitude;
  String gps_speed;
  String gps_altitude;
  String gps_view_satellites;
  String gps_used_satellites;
  String gps_fixstatus = modem.getGPS(&gps_latitude, &gps_longitude, &gps_speed, &gps_altitude, &gps_view_satellites, &gps_used_satellites);
  if ( gps_fixstatus ) {

    Serial.print(F("#GPS Location: LAT: "));
    Serial.println(gps_latitude);
    Serial.print(F(" LONG: "));
    Serial.println(gps_longitude);
    Serial.print(F(" SPEED: "));
    Serial.println(gps_speed);
    Serial.print(F(" ALTITUDE: "));
    Serial.println(gps_altitude);
    Serial.print(F(" USED SATELITES: "));
    Serial.println(gps_view_satellites);
    Serial.print(F(" VIEWED STELITES: "));
    Serial.println(gps_used_satellites);

    int year, month, day, hour, minute, second;
    if ( modem.getGPSTime(&gps_year, &gps_month, &gps_day, &gps_hour, &gps_minute, &gps_second) ) {
      //Sync time if it's diffrent.
      set_time(gps_year, gps_month, gps_day, gps_hour, gps_minute, gps_second);
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
        // turn LED on:
        Serial.println("Button is not pushed");  // turn LED OFF
        ledState = !ledState;
      } else {
        // turn LED off:
        Serial.println("Button is pushed");
        ledState = !ledState;
        sendSMS();  // turn LED ON
      }
    }
  }

  digitalWrite(ledPin, ledState);
  lastButtonState = val;
}

void sendSMS() {

  bool res;
  // put your setup code here, to run once:
  res = modem.sendSMS(SMS_TARGET, String("Hello from "));
  DBG("SMS:", res ? "OK" : "fail");

}
