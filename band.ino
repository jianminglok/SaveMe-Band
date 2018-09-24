#include<SoftwareSerial.h>

SoftwareSerial bt(2,3);

const int  buttonPin = 5;    // the pin that the pushbutton is attached to

// Variables will change:

int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
  bt.begin(9600);
}


void loop() {

  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      Serial.println("1");
      bt.println("1");
      //bt.write("1");
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("Distress Signal sent");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

while(Serial.available()){
  Serial.write(bt.read());
  }

  while(bt.available()){
    bt.write(Serial.read());
    }
  

}
