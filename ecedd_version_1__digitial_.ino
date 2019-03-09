#include <Servo.h>

int leftLight = A1;         // pin for the first photodiode
int rightLight = A0;        // pin for the second photodiode

int leftState = 0;          // current state of the pin for the first photodiode
int rightState = 0;         // currrent state of the pin for the second photodiode

Servo myServo;               // initializing the Servo object

enum LocationStates{BOTH_ON, BOTH_OFF, LEFT_OFF, RIGHT_OFF};    // enumerated states for the state machine algorithm
LocationStates currState = BOTH_ON;                             // initialize current state to be 'BOTH_ON'

void setup() {
  Serial.begin(9600);           // sets the serial data rate
  myServo.attach(9);            // assigns the pin for the Servo connection
  pinMode(leftLight, INPUT);    // assigns the pins for the photodiodes to be inputs
  pinMode(rightLight, INPUT);
  myServo.write(0);             // initializes the position of the servo to be at the horizontal (as the sun will be interpreted to start at dawn)
  // pinMode(light3, INPUT);
}

int pos = 0;                    // initializes the position variable to be 0, which will be modified to be increased or decreased based on light detection


void loop() {
  leftState = analogRead(leftLight);     // assigns the pins for the pins to be read in as analog values
  rightState = analogRead(rightLight);

  switch(currState){                    // case structure for the current state, which houses the State Machine
    case BOTH_ON: {                     // If the current state is BOTH_ON...
      
      Serial.println("both on");        // Serial Monitor print statements
      Serial.println(leftState);
      Serial.println(rightState);
      Serial.println(pos);
      Serial.println("");
      
      if(leftState < 10 && rightState > 10){            // If the amount of light read by the right diode is exceeding the ambient threshold, switch the state to having the left off
        currState = LEFT_OFF;
      }
      else if (leftState > 10 && rightState < 10){      // If the amount of light read by the left diode is exceeding the ambient threshold, switch the state to having the right off
        currState = RIGHT_OFF;
      }
      break;
    }
    
    case BOTH_OFF: {                  // If the current state is BOTH_OFF...
      
      Serial.println("both off");     // If the current state is BOTH_ON...
      Serial.println(leftState);
      Serial.println(rightState); 
      Serial.println(pos);     
      Serial.println("");
      
      if (leftState > 10 && rightState > 10){             // If both diodes are experiencing an amount of light exceeding the ambient threshold, switch the state to being both on
        currState = BOTH_ON;
      }
      else if (leftState < 10 && rightState > 10){      // If the amount of light read by the right diode is exceeding the ambient threshold, switch the state to left off
        if (pos < 180){                                 // as well, if the current angle is less than the horizontal (left) range of 180 degrees, increase the angle of the arm by 3 degrees
          pos = pos + 3;
        }
        myServo.write(pos);                             // Tells servo to move to this angle
        currState = LEFT_OFF;                           
      }
      else if (leftState > 10 && rightState < 10){      // If the amount of light read by the left diode is exceeding the ambient threshold, switch the state to right off
        if (pos > 0){                                   // as well, if the current angle is greater than the horizontal (right) range of 180 degrees, decrease the angle of the arm by 3 degrees
          pos = pos - 3;
        }
        myServo.write(pos);                             // Tells servo to move to this angle
        currState = RIGHT_OFF;
      }
      break;
    }
    
    case LEFT_OFF: {                  // If the current state is LEFT_OFF...
      
      Serial.println("left off");                     // Serial monitor print statements
      Serial.println(leftState);
      Serial.println(rightState);
      Serial.println(pos);
      Serial.println("");
      
       if (leftState  < 10 && rightState > 10){      // If the amount of light read by the right diode is exceeding the ambient threshold, continue to move until they're both on
        if (pos < 180){                              // as well, if the current angle is less than the horizontal (left) range of 180 degrees, increase the angle of the arm by 3 degrees
          pos = pos + 3;
        }
        myServo.write(pos);                          // Tells servo to move to this angle
       }
       else if (leftState > 10 && rightState > 10){ // If the amount of light read by both diodes exceeds the ambient threshold, change state to being both on
        currState = BOTH_ON;
       }
       else if (leftState < 10 && rightState < 10){ // If the amount of light read by both diodes do not exceed the ambient threshold, change state to being both off
        currState = BOTH_OFF;
       } 
       break;
    }
    
    case RIGHT_OFF: {                     // If the current state is RIGHT_OFF...
      
      Serial.println("right off");                  // Serial monitor print statements
      Serial.println(leftState);
      Serial.println(rightState);
      Serial.println(pos);
      Serial.println("");
      
      if (leftState > 10 && rightState < 10){       // If the amount of light ready by the left diode is exceeding the ambient threshold, continue to move until they're both on
          if (pos > 0){                             // as well, if the current angle is greater than the horizontal (right) range of 180 degrees, decrease the angle of the arm by 3 dgegrees
            pos = pos - 3;
          }
          myServo.write(pos);                       // Tells servo to move to this angle
      }
      else if (leftState > 10 && rightState > 10){  // If the amount of light read by both diodes exceeds the ambient threshold, change state to being both on
        currState = BOTH_ON;
      }
      else if (leftState < 10 && rightState < 10){  // If the amount of light read by both diodes does not exceed the ambient threshold, change state to being both off
        currState = BOTH_OFF;
      }
      break;
    }
  }

  delay(5);     // Input delay to the Arduino in milliseconds
}
