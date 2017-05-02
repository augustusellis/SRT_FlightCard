/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int powerPin=13; // That will be set to high and low

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  pinMode(powerPin,OUTPUT);
}

void loop() {

  if(Serial.available())
  {
    Serial.print(Serial.available());
    char com=Serial.read();
    if(com=='H')
    {
      Serial.println("Supplying 5V");
      digitalWrite(powerPin,HIGH);
    }
    if(com=='L')
    {
      Serial.println("Supplying 0V");
      digitalWrite(powerPin,LOW);
    }
    
  }
  if(digitalRead(powerPin)==HIGH)
  {
    servoStuff();
  }

}


void servoStuff()
{
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  Serial.println("Inside Servo Stuff");
}

