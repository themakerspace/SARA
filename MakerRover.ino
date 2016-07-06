

//   this sketch moves a robot vehicle forward,
//   using a 9110 motor driver chip and
//    sweeping a servo (connected to pin 9) back and forth
//    when the sensor detects an obstacle, the robot turns away and continues to move forward
//========================================


// ----------LIBRARIES--------------


#include <NewPing.h>

// --------CONSTANTS (won't change)---------------

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const long interval = 100;           // interval at which to blink (milliseconds)

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



const int AIA = 3;                    // (pwm) pin 9 connected to pin A-IA   (left motor fwrd)
const int AIB = 5;                    // (pwm) pin 5 connected to pin A-IB   (left motor bkwd)
const int BIA = 6;                   // (pwm) pin 10 connected to pin B-IA  (right motor fwrd)
const int BIB = 9;                    // (pwm) pin 6 connected to pin B-IB   (right motor bkwd)
const int ledPin = 13;

byte speed = 255;                    // change this (0-255) to control the speed of the motors 

 

//------------ VARIABLES (will change)---------------------


// Variables will change :
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated




int Distance = 0;
int cm2crash; //integer which measures the distance away from an object
 
unsigned long currentMillis = 0;              // stores the value of millis() in each iteration of loop()



//========================================



void setup() {

Serial.begin(115200);
 Serial.println("Scan");  // so we know what sketch is running

  pinMode(TRIGGER_PIN, OUTPUT);   //  set up sensor pins
  pinMode(ECHO_PIN, INPUT);  
  
  pinMode(AIA, OUTPUT); // set motor pins to output
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(3, HIGH);                              //start both motors forward
  digitalWrite(4, HIGH); 

}

//========================================
void loop() {                                          //Notice that none of the action happens in loop() apart from reading millis()
                                                      //   it just calls the functions that have the action code

  currentMillis = millis();                           // capture the latest value of millis()
  
  
  blinky();
  Scan();

}

//============Subroutines   ========================================




void forward()
{
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, LOW);
  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, LOW);
}

void backward()
{
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);
  digitalWrite(BIA, LOW);
  digitalWrite(BIB, HIGH);
}

void rightSpin()
{
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, LOW);
  digitalWrite(BIA, LOW);
  digitalWrite(BIB, HIGH);
}

void leftSpin()
{
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);
  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, LOW);
}

void rightSlide()
{
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, LOW);
  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);
}

void leftSlide()
{
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);
  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, LOW);
}

void fullStop()
{
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);
  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);
}
void blinky()
{
   // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}

void Scan() {
 Serial.print("object within  ");                         //output to monitor for debugging
    Serial.print (Distance);                                  
    Serial.println (" cm ");  

    Distance = sonar.ping_cm();                                //  ping
    if (1 < Distance && Distance <=15) //if the sensor senses something between 1cm and 15cm ... very close to object - reverse 
    {
                          
      fullStop();
      delay(50);
      backward();
      delay(500);
      rightSpin();
      delay(1000);
                              

   }    
    else if (15 < Distance && Distance <30) //moderately close to object - tight turn left
{
    
      fullStop();
      delay(50);
      leftSpin();
      delay(500);
}
else if (Distance >= 30 && Distance < 50) //far from object - slow turn left
  
  {
      
      rightSpin();
      delay(1000);
  }

else // cruise
  {
   
      forward();
    
    
  }
  
  }
   
    
 
    
//========================================END
