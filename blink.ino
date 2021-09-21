/*    
 *     
 *     
Description:
            The program will begin by printing a prompt to the screen asking for user input. The program should do nothing before a user input is provided. 
            At first prompt, if the user provides a "g" the application will continuously blink two LEDs until the user enters an "s" at the prompt. 
            If the user provides an "s" at any time, the application will stop blinking both LEDs until new user input is provided. 
 *          
 *
 */

void setup() 
{
  Serial.setTimeout(50);
  Serial.begin(115200);                     // Sets Baud Rate to 11520
  delay(100);                               // Protects against garbage characters upon upload

  while (! Serial);                         // The progam will wait until the serial is ready

  // Once ready, prompt user with instructions:
  Serial.println("Enter a 'g' on the keyboard to blink the LEDs");
  Serial.println("Enter a 's' on the keyboard to turn off the blinking LEDs");
}

void loop() 
{
  
// These variables are used to read the user input, store the blink rate of the LEDs, and store the current state of the LEDs.

String userCharacter;                       // A string that handles the user input from the serial monitor
 
int offboardLED = 12;                       // Off-board LED pin setting.
int ledState1   = LOW;                      // The inital state of the off-board LED.

int onboardLED  = LED_BUILTIN;              // On-board LED pin setting.
int ledState2   = LOW;                      // The inital state of the on-board LED.
long onTime     = 2000;                     // The milliseconds of on-time for the on-board LED.
long offTime    = 1000;                     // The milliseconds of off-time for the on-board LED.

unsigned long previousTime = 0;             // This variable will store last time the state machine was updated

  pinMode(offboardLED, OUTPUT);             // Sets the offboard digital pin as an output
  pinMode(onboardLED,  OUTPUT);             // Sets the onboard digital pin as an output

  while (Serial.available() == 0)                    // Init Serial
  {
    userCharacter = Serial.readStringUntil('\n');   // Reads user input until newline (i.e. enter is pressed)

    if (userCharacter == "g")                       // When input is 'g' condition..
    {
      Serial.println("LED Cycle ON. Input 's' to stop the loop.");
      while(Serial.readStringUntil('\n') != "s")    // Condition to end loop is 's' is entered
      {
        unsigned long currentTime = millis();       // Storage of LED cycle time data
          
        /* On-board LED */
        if((ledState2 == HIGH) && (currentTime - previousTime >= onTime))
        {
          ledState1 = HIGH;                         // Turn on-board LED on
          ledState2 = LOW;                          // Turn off-board LED off
          previousTime = currentTime;               // Remember the time when the LEDs were turned on/off
          digitalWrite(offboardLED, ledState1);     // Update the off-board LED's state
          digitalWrite(onboardLED, ledState2);      // Update the on-board LED's state
        }
        else if ((ledState2 == LOW) && (currentTime - previousTime >= offTime))
        {
          ledState1 = LOW;                          // Turn on-board LED off
          ledState2 = HIGH;                         // Turn off-board LED on
          previousTime = currentTime;               // Remember the time when the LEDs were turned on/off
          digitalWrite(offboardLED, ledState1);     // Update the off-board LED's state
          digitalWrite(onboardLED, ledState2);      // Update the on-board LED's state
        }
      }
    }
    else if(userCharacter != "g" && userCharacter !="s" && userCharacter != "") { Serial.println("Invalid input. Please enter a valid input."); } // Error message
    else 
    { 
      ledState1 = LOW;
      ledState2 = LOW;
      digitalWrite(offboardLED, ledState1);         // Update the off-board LED's state
      digitalWrite(onboardLED, ledState2);          // Update the on-board LED's state
    }
  }
}
