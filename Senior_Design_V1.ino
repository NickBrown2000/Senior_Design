// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define enablePin 4
#define stepsPerRevolution 200

int LOT;
int revs;
int pause;
int mspeed;
int oldRev;
 
// Rotary Encoder Module connections
const int PinSW1 = 10;  // Rotary Encoder Switch
const int PinDT1 = 9;   // DATA signal
const int PinCLK1 = 8;  // CLOCK signal
 
const int PinSW2 = 13;   // Rotary Encoder Switch
const int PinDT2 = 12;   // DATA signal
const int PinCLK2 = 11;  // CLOCK signal
 
// Store previous Pins state
int PreviousCLK1;
int PreviousDATA1;
 
int PreviousCLK2;
int PreviousDATA2;
 
void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  //Set default values
  LOT=4; //Default LOT of Cycle in Seconds
  pause = 2000;//Milliseconds
  mspeed = 1000;//Microseconds
  revs = 2.5;//Revolutions per cycle
  
  //Set up pause encoder
  PreviousCLK1 = digitalRead(PinCLK1);
  PreviousDATA1 = digitalRead(PinDT1);
  pinMode(PinSW1, INPUT_PULLUP);
 
  //Set up flow encoder
  PreviousCLK2 = digitalRead(PinCLK2);
  PreviousDATA2 = digitalRead(PinDT2);
  pinMode(PinSW2, INPUT_PULLUP);

  //Turn off motor
  digitalWrite(enablePin, HIGH);
}
 
void loop() {

  //Check for changes then turn on motor
  checkEncoders();
  digitalWrite(enablePin, LOW);
 
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor CW:
  for (int i = 0; i < revs * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(mspeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(mspeed);
  }

  //Pause at top of sinusoid
  delayMicroseconds(500);
  
  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);
  //Spin the stepper motor CCW:
  for (int i = 0; i < revs * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(mspeed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(mspeed);
  }

  //Turn off the motor and wait
  digitalWrite(enablePin, HIGH);
  delay(pause);
}
 
void checkEncoders() { 
    check_rotary1();
 
    PreviousCLK1 = digitalRead(PinCLK1);
    PreviousDATA1 = digitalRead(PinDT1);
 
    check_rotary2();
 
    PreviousCLK2 = digitalRead(PinCLK2);
    PreviousDATA2 = digitalRead(PinDT2);
 
}
 
void check_rotary1() {
 
  if ((PreviousCLK1 == 0) && (PreviousDATA1 == 1)) {
    if ((digitalRead(PinCLK1) == 1) && (digitalRead(PinDT1) == 0)) {
      increasePause();
    }
    if ((digitalRead(PinCLK1) == 1) && (digitalRead(PinDT1) == 1)) {
      decreasePause();
    }
  }
 
  if ((PreviousCLK1 == 1) && (PreviousDATA1 == 0)) {
    if ((digitalRead(PinCLK1) == 0) && (digitalRead(PinDT1) == 1)) {
     increasePause();
    }
    if ((digitalRead(PinCLK1) == 0) && (digitalRead(PinDT1) == 0)) {
      decreasePause();
    }
  }
 
  if ((PreviousCLK1 == 1) && (PreviousDATA1 == 1)) {
    if ((digitalRead(PinCLK1) == 0) && (digitalRead(PinDT1) == 1)) {
      increasePause();
    }
    if ((digitalRead(PinCLK1) == 0) && (digitalRead(PinDT1) == 0)) {
      decreasePause();
    }
  }
 
  if ((PreviousCLK1 == 0) && (PreviousDATA1 == 0)) {
    if ((digitalRead(PinCLK1) == 1) && (digitalRead(PinDT1) == 0)) {
      increasePause();
    }
    if ((digitalRead(PinCLK1) == 1) && (digitalRead(PinDT1) == 1)) {
      decreasePause();
    }
  }
}
 
 
void check_rotary2() {
 
  oldRev = revs;
 
  if ((PreviousCLK2 == 0) && (PreviousDATA2 == 1)) {
    if ((digitalRead(PinCLK2) == 1) && (digitalRead(PinDT2) == 0)) {
      increaseRevs();
    }
    if ((digitalRead(PinCLK2) == 1) && (digitalRead(PinDT2) == 1)) {
      decreaseRevs();
    }
  }
 
  if ((PreviousCLK2 == 1) && (PreviousDATA2 == 0)) {
    if ((digitalRead(PinCLK2) == 0) && (digitalRead(PinDT2) == 1)) {
      increaseRevs();
    }
    if ((digitalRead(PinCLK2) == 0) && (digitalRead(PinDT2) == 0)) {
      decreaseRevs();
    }
  }
 
  if ((PreviousCLK2 == 1) && (PreviousDATA2 == 1)) {
    if ((digitalRead(PinCLK2) == 0) && (digitalRead(PinDT2) == 1)) {
      increaseRevs();
    }
    if ((digitalRead(PinCLK2) == 0) && (digitalRead(PinDT2) == 0)) {
      decreaseRevs();
    }
  }
 
  if ((PreviousCLK2 == 0) && (PreviousDATA2 == 0)) {
    if ((digitalRead(PinCLK2) == 1) && (digitalRead(PinDT2) == 0)) {
      increaseRevs();
    }
    if ((digitalRead(PinCLK2) == 1) && (digitalRead(PinDT2) == 1)) {
      decreaseRevs();
    }
  }
}

void increasePause(){
  int oldPause = pause;
  if(pause<=4000 && mspeed>1000){
    pause = pause + 500;
    mspeed = mspeed*(pause/oldPause);
}
}
void decreasePause(){
  int oldPause = pause;
  if(pause>1000 && mspeed>1000){
    pause = pause - 500 ;
    mspeed = mspeed*(pause/oldPause);
    }
}

void increaseRevs(){
  int oldRev = revs;
    if(revs<=10 && mspeed>1000){
      revs++;
      mspeed = mspeed*(revs/oldRev);
    }
 }
void decreaseRevs(){
  int oldRev = revs;
    if(revs>=2 && mspeed>1000){
    revs--;
    mspeed = mspeed*(revs/oldRev);
}
}
