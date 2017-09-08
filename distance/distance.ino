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
      distance = irSensor.getDistanceCentimeter();
      Serial.print("\nDistance in centimeters: ");
      Serial.print(distance);  
      if(distance<=30){
        Serial.print("in small distance");
        AllFlashing(50);
      }
      else if(distance>30 && distance<=40){
        AllFlashing(1000);
      }
      else if(distance>40 && distance<=50){
        AllFlashing(2000);
      }
      else if(distance>50 && distance<=60){
        AllFlashing(3000);
      }
      else if(distance>60){
        AllFlashing(4000);
      }
}

void AllFlashing(long myInterval)
{
        if(waitNoDelay(myInterval)==true){ 
              // If the LEDs have been OFF for the full interval, turn them ON
              if (digitalRead(greenLED) == LOW){  // Can just check one LED b/c they're all doing the same thing
                Serial.print("hiya");
                //Turn on all LEDS
                digitalWrite(greenLED, HIGH);
                digitalWrite(yellowLED, HIGH);
                digitalWrite(redLED, HIGH);
                digitalWrite(otherLED, HIGH); 
              }
              else{
                Serial.print("why why why");
                 // If the LEDs have been ON for the full interval, turn them OFF 
                digitalWrite(greenLED, LOW);
                digitalWrite(yellowLED, LOW);
                digitalWrite(redLED, LOW);
                digitalWrite(otherLED, LOW);
              }
            }
  }

