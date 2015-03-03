/*HI JEN! I've commented the hell out of this so it should be easy to understand.
I wanted to not only explain what our code is doing, but also why I use certain
programming conventions. By the way, this is a multiline comment.*/

//and this is a single-line comment.

/*It is good form to open a piece of code with a multiline description of what it's for.
It is also good to do this for each section. Especially if you plan on collaborating.
Commenting also helps you remember what the fuck you were doing when you come back to it
months later. Very good practice. So we will comment heavily as a routine. */

//Always start by defining the terms you'll use throughout.

/*****GLOBAL CONSTANTS*****/
//these are user-defined constants.
//these are good for readability, as well as for
//making it easier to change parameters from a single location.
//for instance, if we need to use a different sensor pin,
//we can now just change it here instead of hunting down all
//the places in the code where it says "14"
const boolean CLOSED = 0;      //The closed and open states are the inverse
const boolean OPEN   = 1;      //of what you might expect because of the pullup resistor.
const int SENSOR_PIN = 14;     //The teensy DIGITAL pin into which the speed sensor is inserted.

/*****GLOBAL VARIABLES*****/
elapsedMillis sinceSend;  //automatically counts milliseconds
boolean sensorState;      //store state of sensor. OPEN or CLOSED.

//Initialization -- this is run once at the beginning
void setup() {
  Serial.begin(38400); //38400 is the "baud rate" or transfer rate.
                       //this number does not matter when in USB mode.
  pinMode(SENSOR_PIN, INPUT_PULLUP); //use the built-in pullup resistor 
                                     //on the digital pin we designated 
                                     //in the global constants section.
  sensorState = digitalRead(SENSOR_PIN); //get the initial sensor state
  sinceSend   = 0;  //begin the millisecond counter
}//end setup()

//loop() is run once every "tick" of the processor
void loop(){
 //read sensor input, and eliminate error deriving from a magnet
 //that stays on the sensor for two reads in a row, which would
 //erroneously double the perceived speed
 if(digitalRead(SENSOR_PIN) == 0){
  if(sensorState != CLOSED){   //only do this if it was not already closed
    sensorState = CLOSED;
    if(sinceSend <= 1023)      //Joystick values go from 0 to 1023.
      Joystick.X(sinceSend);   //therefor we have to make the sensor sort of timeout
    else Joystick.X(1023);     //anything longer than 1023ms and we just call it 1023.
                               //this will have to count as a speed of 0 in the game
                               //and a reading of 0 will be our speed cap which is actually
                               //impossible to hit, creating a sort of max speed asymptote
    
    //note: Serial.print prints to the serial monitor without linebreaks.
    //Serial.println (pronounced "print line") prints to the monitor and then
    //puts a linebreak at the end.
    Serial.print(sinceSend); //for debugging purposes, output to serial monitor
    Serial.println(" milliseconds since the last rotation");
    
    sinceSend = 0; //reset count
  }//end inner if; do nothing otherwise
 }//end closed sensor activities
 
 else //if the SENSOR_PIN reads as open,
   sensorState = OPEN; //call the sensor open, but do nothing else

 //USE THIS TO GET ANALOG VALUES FOR SENSOR DEBUGGING
 /*
 Serial.println(analogRead(0));
 delay(100);
 */
 
}//end loop()


