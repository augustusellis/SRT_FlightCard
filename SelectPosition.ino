/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/
//Servo deafult 93
// Servo Min 20
//Servo Max 160
//intial closed 140
//final open 30
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int cpos = 0;     //curretn psotion of servo
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600); //bgins serial
}

void loop() {
  
  if(Serial.available())
  {
    pos=Serial.parseInt();
    sopl("Reading in the postion:"+String(pos));  
  }
  cpos=myservo.read();
  if(pos>=20&&pos<=160&&cpos!=pos)
  {
    sopl("My current position is "+String(cpos));
    moveToPos(cpos,pos);
    sopl("I just moved to "+ String(pos));
  }

}

void  sopl(String s)
{
  Serial.println(s);
}

void moveToPos(int b, int e)
{
    for (int i = b; i >= e; i -= 1) { // goes from b degrees to e degrees
      // in steps of 1 degree
      myservo.write(i);              // tell servo to go to position in variable 'i'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (int i = b; i <= e; i += 1) { // goes from b degrees to e degrees
      // in steps of 1 degree
      myservo.write(i);              // tell servo to go to position in variable 'i'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  //sopl(String(myservo.read()));
}

