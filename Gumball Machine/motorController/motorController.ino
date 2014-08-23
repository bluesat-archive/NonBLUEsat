
/*

****BlueSat Motor Dispenser****

-ChrisJay, JackZeng and Alice

Motor driven through motor controlling circuit.
Arduino controls direction of current flow through pins 4-7.
Uses direct port writing to set the 4 states.



Wiring for gum dispensing:

  M1- = blue
  m1+ = red
  
  M2- = green
  M2+ = black
 
Pin Mapping:
  4 - M2 Direction
  5 - M1 on
  6 - M2 on
  7 - M2 Direction

 
*/

//set up wireless input pin
int wirelessIn = 3;

//setup wireless input and motor outputs
void setup(){

  // setup inputs and outputs
  // first 4 bits are motor control 
  // pin 3 is input (LOW = run)
  DDRD = B11110000;
  PORTD = B00000000;
  

}

void loop(){

  //loop waiting for input
  //looks for low as there is a pullup on the input
  while(1){
    if(!digitalRead(wirelessIn)){
      break;
    }
  }

  //Input recieved, turn motor
  turnMotor();
  
  delay(1000);
}



/*

This motor works in 4 sections for one step.
It is a stepper motor so you need to set bits
in particular order.

Each loop is one step and covers (360/50) degrees

*/

void turnMotor(){

  int i;
  int TIME = 20;
  
  //Takes 50 steps to cover a whole circle
  for(i=0;i<50;i++){
  
    //
    PORTD = B00110000;
    delay(TIME);
    
    //
    PORTD = B01000000;
    delay(TIME);
    
    //
    PORTD = B00100000;
    delay(TIME);
    
    //
    PORTD = B11000000;
    delay(TIME);
  
 
  //set everything low
  PORTD = B00001000;
  

  }
  
}
