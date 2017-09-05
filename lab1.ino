/* Lab 1: 
 *   Pressing a button will switch the system of lights between several modes. 
 *   Minimum of 5 modes and at least 3 LEDs
 */

                         /********** INITIALIZING VARIABLES **********/
// variable for pin connected to the button
int button = 8;

// variables for LEDs
int greenLED = 13;
int yellowLED = 12;
int redLED = 11;
int otherLED = 10;

// Number of modes to cycle through
int numModes = 6;

// Counter to see which mode we are on, initialized to 1 (the first mode
int counter = 1;


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
}

// Main code here, to run repeatedly:
void loop() {
  // Check if button was pressed, update the mode counter
  if (digitalRead(button) == LOW) {
      // If button was pushed, reset all LEDs (turned off between modes)
      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(otherLED, LOW);  
      delay(500);

      // Check if the last mode has been reached
      if (counter >= numModes){
        counter = 1;
      }
      // Increment the counter to move to the next mode
      else {
        counter++;
      }
  }
      
  // Check which mode we are in
    switch(counter){
      case 1: // ALL ON
              digitalWrite(greenLED, HIGH);
              digitalWrite(yellowLED, HIGH);
              digitalWrite(redLED, HIGH);
              digitalWrite(otherLED, HIGH);  
              break;
       case 2: // ALL OFF
              digitalWrite(greenLED, LOW);
              digitalWrite(yellowLED, LOW);
              digitalWrite(redLED, LOW);
              digitalWrite(otherLED, LOW);  
              break;
       case 3: // ALL FLASHING
              // Turn on
              digitalWrite(greenLED, HIGH);
              digitalWrite(yellowLED, HIGH);
              digitalWrite(redLED, HIGH);
              digitalWrite(otherLED, HIGH); 
              delay(1000);                       // wait for a second 
              // Turn off
              digitalWrite(greenLED, LOW);
              digitalWrite(yellowLED, LOW);
              digitalWrite(redLED, LOW);
              digitalWrite(otherLED, LOW);  
              break;
       case 4: // ALL BOUNCING
              digitalWrite(greenLED, HIGH);      // Green on  
              delay(1000);                           // Wait for a second
              digitalWrite(greenLED, LOW);       // Green off             
              digitalWrite(yellowLED, HIGH);     // Yellow on
              delay(1000);                           // Wait for a second
              digitalWrite(yellowLED, LOW);      // Yellow off
              digitalWrite(redLED, HIGH);        // Red on
              delay(1000);                           // Wait for a second  
              digitalWrite(redLED, LOW);         // Red off       
              digitalWrite(otherLED, HIGH);      // Other LED on
              delay(1000);                           // Wait for a second 
              digitalWrite(otherLED, LOW);       // Other LED off           
              break;
       case 5: // TWO ON, TWO OFF (SWITCHING)
              digitalWrite(greenLED, HIGH);      // Green on  
              digitalWrite(redLED, HIGH);        // Red on
              delay(1000);                           // Wait for a second  
              digitalWrite(greenLED, LOW);       // Green off     
              digitalWrite(redLED, LOW);         // Red off  
                   
              digitalWrite(yellowLED, HIGH);     // Yellow on  
              digitalWrite(otherLED, HIGH);      // Other LED on
              delay(1000);                           // Wait for a second  
              digitalWrite(yellowLED, LOW);      // Yellow off     
              digitalWrite(otherLED, LOW);       // OtherLED off     
              break;
        case 6: // RANDOMLY TURN ON ONE LIGHT
              digitalWrite(random(10, 14), HIGH);   // Provide power to a random pin (with an LED)
              delay(1000);                          // Wait for a second     
              break;
  }
  
}
