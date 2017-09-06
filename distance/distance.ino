#include <GP2Y0A02YK0F.h>

GP2Y0A02YK0F irSensor;
int distance;

// variables for LEDs
int greenLED = 13;
int yellowLED = 12;
int redLED = 11;
int otherLED = 10;

// Number of modes to cycle through
int numModes = 6;

// Counter to see which mode we are on, initialized to 1 (the first mode
int counter = 1;

// Using this to keep track of time passed
unsigned long previousMillis = 0;        // will store last time LED was updated

// If the full interval has occured, return true
bool waitNoDelay(long millisToWait){
  unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= millisToWait) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        return true;
      }
      else{
        return false;
      }
  }

void setup()
{
  Serial.begin(9600);
  irSensor.begin(A0);  //  Assign A0 as sensor pin
  // LEDs are the output
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(otherLED, OUTPUT);
}

void loop()
{
  if(waitNoDelay(50)==true){
      distance = irSensor.getDistanceCentimeter();
      Serial.print("\nDistance in centimeters: ");
      Serial.print(distance);  
      if(distance>=20 && distance<=46){
        AllFlashing(200);
      }
      else if(distance>46 && distance<=72){
        AllFlashing(400);
      }
      else if(distance>72 && distance<=98){
        AllFlashing(600);
      }
      else if(distance>98 && distance<=124){
        AllFlashing(800);
      }
      else if(distance>124 && distance<=150){
        AllFlashing(1000);
      }
  }
}

void AllFlashing(long myInterval)
{
if(waitNoDelay(myInterval)==true){ 
              // If the LEDs have been OFF for the full interval, turn them ON
              if (digitalRead(greenLED) == LOW){  // Can just check one LED b/c they're all doing the same thing
                //Turn on all LEDS
                digitalWrite(greenLED, HIGH);
                digitalWrite(yellowLED, HIGH);
                digitalWrite(redLED, HIGH);
                digitalWrite(otherLED, HIGH); 
              }
              else{
                 // If the LEDs have been ON for the full interval, turn them OFF 
                digitalWrite(greenLED, LOW);
                digitalWrite(yellowLED, LOW);
                digitalWrite(redLED, LOW);
                digitalWrite(otherLED, LOW);
              }
            }
  }

