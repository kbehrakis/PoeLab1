/* Lab 1: 
 *   Pressing a button will switch the system of lights between several modes. 
 *   Minimum of 5 modes and at least 3 LEDs
 */

                         /********** INITIALIZING VARIABLES **********/
// variable for pin connected to the button
int button = 8;
int buttonState = LOW;  // Begins not being pressed
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


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

const long interval = 1000;           // interval at which to blink (milliseconds)

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


                         /********** ACTUAL CODE **********/
// Setup code here, to run once:
void setup() {
  // Button is the input
  pinMode(button, INPUT);

  // LEDs are the output
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(otherLED, OUTPUT);
  Serial.begin(9600);
}

// Main code here, to run repeatedly:
void loop() {
  Debounce();
  Serial.println(counter);
      
  // Check which mode we are in
    switch(counter){
      
      case 1: // ALL ON
              AllOn();
              break;
              
       case 2: // ALL OFF  
              AllOff();
              break;
              
       case 3: // ALL FLASHING
            // If the interval has been completed
              AllFlashing();
              break;
              
       case 4: // ALL BOUNCING
              // If one of the LEDs has been on for the full interval
              AllBouncing();
              break;
              
       case 5: // TWO ON, TWO OFF (SWITCHING)
              TwoOnTwoOff();
              break;
              
        case 6: // RANDOMLY TURN ON ALL THE LEDs (RANDOM SEQUENCE)
              // If at least one LED has been on for the full interval, switch to a different LED
              RandomOn();
              break;
    }
}

void AllOn()
{
   digitalWrite(greenLED, HIGH);
   digitalWrite(yellowLED, HIGH);
   digitalWrite(redLED, HIGH);
   digitalWrite(otherLED, HIGH);  
}


void AllOff()
{
   digitalWrite(greenLED, LOW);
   digitalWrite(yellowLED, LOW);
   digitalWrite(redLED, LOW);
   digitalWrite(otherLED, LOW);
}


void AllFlashing()
{
if(waitNoDelay(interval)==true){ 
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

 void AllBouncing()
 {
      if(waitNoDelay(interval)==true){
                // Green LED was on for full interval
                if(digitalRead(greenLED) == HIGH){
                  digitalWrite(greenLED, LOW);       // Green off             
                  digitalWrite(yellowLED, HIGH);     // Yellow on
                }
                // Yellow LED was on for full interval
                else if(digitalRead(yellowLED) == HIGH) {
                  digitalWrite(yellowLED, LOW);      // Yellow off
                  digitalWrite(redLED, HIGH);        // Red on
                }
                // Red LED was on for full interval
                else if(digitalRead(redLED) == HIGH) {
                  digitalWrite(redLED, LOW);      // Yellow off
                  digitalWrite(otherLED, HIGH);   // Red on
                }
                // OtherLED was on or sequence hasn't started yet (either way, green LED should light up)
                else {
                  digitalWrite(otherLED, LOW);      // Yellow off
                  digitalWrite(greenLED, HIGH);   // Red on
                }
              }
 }

 void TwoOnTwoOff()
 {
   if(waitNoDelay(interval)==true){ 
              // If the LEDs have been OFF for the full interval, turn them ON
                if (digitalRead(greenLED) == LOW){  // Can just check one LED b/c they're all doing the same thing
                  //Turn on all LEDS
                  digitalWrite(greenLED, HIGH);
                  digitalWrite(yellowLED, LOW);
                  digitalWrite(redLED, HIGH);
                  digitalWrite(otherLED, LOW); 
                }
                else{
                   // If the LEDs have been ON for the full interval, turn them OFF 
                  digitalWrite(greenLED, LOW);
                  digitalWrite(yellowLED, HIGH);
                  digitalWrite(redLED, LOW);
                  digitalWrite(otherLED, HIGH);
                }
            }
 }

 void RandomOn()
 {
  if(waitNoDelay(interval)==true){
                // If all the LEDs are on already, then reset
                if((digitalRead(greenLED) == HIGH)&&(digitalRead(yellowLED) == HIGH)&&(digitalRead(redLED) == HIGH)&&(digitalRead(otherLED) == HIGH)){
                  digitalWrite(greenLED, LOW);
                  digitalWrite(yellowLED, LOW);
                  digitalWrite(redLED, LOW);
                  digitalWrite(otherLED, LOW); 
                }
                 else{
                  digitalWrite(random(10, 14), HIGH);   // Provide power to a random pin (with an LED)
                  }   
              }
 }

 void Debounce(){
    // read the state of the switch into a local variable:
    int reading = digitalRead(button);
  
    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:
  
    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
      // reset the debouncing timer
      lastDebounceTime = millis();
    }
  
    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:
  
      // if the button state has changed:
      if (reading != buttonState) {
        buttonState = reading;
  
        // only toggle the LED if the new button state is HIGH
        if (buttonState == HIGH) {
          digitalWrite(greenLED, LOW);
          digitalWrite(yellowLED, LOW);
          digitalWrite(redLED, LOW);
          digitalWrite(otherLED, LOW);
         // Check if the last mode has been reached
        if (counter >= numModes){
          counter = 1;
        }
        // Increment the counter to move to the next mode
        else {
          counter++;
        }
         }
      }
    }
  
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
 }

