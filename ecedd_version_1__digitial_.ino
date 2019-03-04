int light1 = A0; // pin for the first photodiode
int light2 = A1; // pin for the second photodiode
// int light3 = 3;

int lightState1 = 0;  // current state of the pin for the first photodiode
int lightState2 = 0;
// int prevState1 = 0;
// int prevState2 = 0;

enum LocationStates{BOTH_ON, BOTH_OFF, NORTH_OFF, SOUTH_OFF};
LocationStates currState = BOTH_ON;
LocationStates prevState = currState;

void setup() {
  Serial.begin(9600);
  pinMode(light1, INPUT);
  pinMode(light2, INPUT);
  // pinMode(light3, INPUT);
}



void loop() {
  lightState1 = analogRead(light1);

  lightState2 = analogRead(light2);

  switch(currState){
    case BOTH_ON: {
      Serial.println("both on");
      Serial.println(lightState1 + " and " + lightState2);
      Serial.println("");
      if(lightState1 < 10 && lightState2 > 10){
        currState = NORTH_OFF;
        prevState = BOTH_ON;
      }
      else if (lightState1 > 10 && lightState2 < 10){
        currState = SOUTH_OFF;
        prevState = BOTH_ON;
      }
      break;
    }
    case BOTH_OFF: {
      Serial.println("both off");
      Serial.println(lightState1 + " and " + lightState2);
      Serial.println("");
      if (lightState1 < 10 && lightState2 > 10){
        // code to move
        currState = NORTH_OFF;
        prevState = BOTH_OFF;
      }
      if (lightState1 > 10 && lightState2 < 10){
        // code to move
        currState = SOUTH_OFF;
        prevState = BOTH_OFF;
      }
      break;
    }
    case NORTH_OFF: {
      Serial.println("north off");
      Serial.println(lightState1 + " and " + lightState2);
      Serial.println("");
       if (lightState1  < 10&& lightState2 > 10){
        // code to move
       }
       else if (lightState1 > 10 && lightState2 > 10){
        currState = BOTH_ON;
        prevState = NORTH_OFF;
       }
       else if (lightState1 < 10 && lightState2 < 10){
        currState = BOTH_OFF;
        prevState = NORTH_OFF;
       }
       break;
    }
    case SOUTH_OFF: {
      Serial.println("south off");
      Serial.println(lightState1 + " and " + lightState2);
      Serial.println("");
      if (lightState1 > 10 && lightState2 < 10){
          // code to move
      }
      else if (lightState1 > 10 && lightState2 > 10){
        currState = BOTH_ON;
        prevState = SOUTH_OFF;
      }
      else if (lightState1 < 10 && lightState2 < 10){
        currState = BOTH_OFF;
        prevState = SOUTH_OFF;
      }
      break;
    }
  }

  // prevState1 = lightState1;
  // prevState2 = lightState2; 

  delay(1000);
}
