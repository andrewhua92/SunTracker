int leftLight = A0; // pin for the first photodiode
int rightLight = A1; // pin for the second photodiode
// int light3 = 3;

int leftState = 0;  // current state of the pin for the first photodiode
int rightState = 0;
// int prevState1 = 0;
// int prevState2 = 0;

enum LocationStates{BOTH_ON, BOTH_OFF, LEFT_OFF, RIGHT_OFF};
LocationStates currState = BOTH_ON;
LocationStates prevState = currState;

void setup() {
  Serial.begin(9600);
  pinMode(leftLight, INPUT);
  pinMode(rightLight, INPUT);
  // pinMode(light3, INPUT);
}



void loop() {
  leftState = analogRead(leftLight);

  rightState = analogRead(rightLight);

  switch(currState){
    case BOTH_ON: {
      Serial.println("both on");
      Serial.println(leftState);
      Serial.println(rightState);
      Serial.println("");
      if(leftState < 10 && rightState > 10){
        currState = LEFT_OFF;
        prevState = BOTH_ON;
      }
      else if (leftState > 10 && rightState < 10){
        currState = RIGHT_OFF;
        prevState = BOTH_ON;
      }
      break;
    }
    case BOTH_OFF: {
      Serial.println("both off");
      Serial.println(leftState);
      Serial.println(rightState);      
      Serial.println("");
      if (leftState < 10 && rightState > 10){
        // code to move
        currState = LEFT_OFF;
        prevState = BOTH_OFF;
      }
      if (leftState > 10 && rightState < 10){
        // code to move
        currState = RIGHT_OFF;
        prevState = BOTH_OFF;
      }
      break;
    }
    case LEFT_OFF: {
      Serial.println("left off");
      Serial.println(leftState);
      Serial.println(rightState);
      Serial.println("");
       if (leftState  < 10&& rightState > 10){
        // code to move
       }
       else if (leftState > 10 && rightState > 10){
        currState = BOTH_ON;
        prevState = LEFT_OFF;
       }
       else if (leftState < 10 && rightState < 10){
        currState = BOTH_OFF;
        prevState = LEFT_OFF;
       }
       break;
    }
    case RIGHT_OFF: {
      Serial.println("right off");
      Serial.println(leftState);
      Serial.println(rightState);
      Serial.println("");
      if (leftState > 10 && rightState < 10){
          // code to move
      }
      else if (leftState > 10 && rightState > 10){
        currState = BOTH_ON;
        prevState = RIGHT_OFF;
      }
      else if (leftState < 10 && rightState < 10){
        currState = BOTH_OFF;
        prevState = RIGHT_OFF;
      }
      break;
    }
  }

  // prevState1 = leftState;
  // prevState2 = rightState; 

  delay(100);
}
