/*
 * Author: Alessandro Taufer
 * Github: alessandro.taufer@gmail.com
 * Release Date: None
 */


// WANTED PUZZLE SECTION - Public variables
bool wantedSolutionStatus; // Has the wanted section been correctly solved
int wantedLeds[3] = {10,11,12}; // List of pins binded to leds
int wantedBtns[3] = {7,8, 9}; // List of pins binded to buttons. The first btn will be the one binded to the right solution
bool wantedBtnsStatus[sizeof(wantedLeds)/sizeof(int)]; // Vector of btn status (pressed or not)


void setup() {

  // Debug
  Serial.begin(9600);

  // WANTED PUZZLE SECTION - pin configuration and variables initialization
  for (int i = 0; i < sizeof(wantedLeds)/sizeof(int); i++){
    pinMode(wantedLeds[i], OUTPUT);
    pinMode(wantedBtns[i], INPUT);
    wantedBtnsStatus[i] = false;
  }
  wantedSolutionStatus = false;

}

void loop() {
  // WANTED PUZZLE SECTION - functional code
  bool changed = false;
  for(int i=0; i < sizeof(wantedLeds)/sizeof(int); i++){
    if (digitalRead(wantedBtns[i])){
      wantedBtnsStatus[i] = !wantedBtnsStatus[i];    
      changed = true;
    }
  }

  wantedSolutionStatus = true;
  for(int i = 0; i < sizeof(wantedLeds)/sizeof(int) && wantedSolutionStatus; i++){ // Check if the solution is correct
    if (i == 0){
      wantedSolutionStatus = wantedBtnsStatus[i];
    }else if(wantedBtnsStatus[i]){
      wantedSolutionStatus = !wantedBtnsStatus[i];
    }
  }

  if (wantedSolutionStatus){ // Debug
    Serial.println(" Selected the correct solution for wanted! ");
  }
  
  for(int i = 0; i < sizeof(wantedLeds)/sizeof(int); i++ ){
    digitalWrite(wantedLeds[i], wantedBtnsStatus[i]);
  }

  if (changed){ // Avoid miss clics
    delay(300);
  }
}
