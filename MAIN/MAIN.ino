//For engine shutdown, can have multiple pins to check inputs, or just use an
//interrupt on pins 2 & 3, or use combination. Right now based on 2/3 pin high confirmation
//Need to add servo/stepper motor code
//Countdown not real time (runs slow) if it matters

//Commands
//r - readys launch
//f - final launch ready
//l - LAUNCH
//a - abort
//s - returns state of variables

//Commands Meant for DAQ
//i - initialization: initializes SD card
//t - sensor test: sends sensor values ten times over 5 seconds
//c - collect data: collects data continuously. outputs over serial and saves. Also checks temp
//to make sure it's not too hot. Command to make pins go high to signal heat event are commented out
//e - exit data collect

#include <SoftwareSerial.h> //Communication with DAQ Arduino
#include <Servo.h>          //Valve Control

//Servo Valve Variables
Servo valveServo;
int motorControllerPowerPin = 7;
int valveSignalPWMPin = 5;
bool firstTime = true;

//DAQ Serial Connection Settings
int baud = 9600;
int DAQrxPin = 2;
int DAQtxPin = 3;
SoftwareSerial DAQSerial(DAQrxPin, DAQtxPin);

//Hardware Serial and Launch Status Variables
char inputCMD;
String data;
String msg;
boolean launchReady = 0;
boolean finalLaunchReady = 0;
boolean launchTime = 0;
boolean dontAbort = 1;
String abortLaunch;


void setup() {
  // Initiate Serial Connections to Launchbox (Hardware Serial) and DAQ (Software Serial)
  DAQSerial.begin(baud);
  Serial.begin(baud);
  //Initiate
  valveServo.attach(valveSignalPWMPin);// attaches the valve servo object to the PWM output pin

}

void loop() {
  //Set valve servo to close on the first loop
  if (firstTime == 1)
  {
    valveClose(valveServo);
    firstTime = 0;
  }

  //Read in commands from Launch Box and Respond Accordingly
  inputCMD = Serial.read();
  //Output data from DAQSerial back onto hardware serial (this sends the data back to the launchbox)
  if (DAQSerial.available())
  {
    data = DAQSerial.readStringUntil('\n');
    Serial.println(data);
  }
  switch (inputCMD) {
    case 'a': //abort sequence -- negates all launch-ready statuses
      launchTime = 0;
      launchReady = 0;
      finalLaunchReady = 0;
      Serial.println("xCMabo");
      break;
    case 'i': //initialize DAQ Arduino
      DAQSerial.println('i');
      Serial.println("CM: i passed");
      break;
    case 't':
      DAQSerial.println('t');
      Serial.println("CM: t passed");
      break;
    case 'c':
      DAQSerial.println('c');
      Serial.println("CM: c passed");
      break;
    case 'e':
      DAQSerial.println('e');
      Serial.println("CM: e passed");
      break;
    case 'r':
      launchReady = 1;
      //    Serial.println("First Launch Ready is " + launchReady);
      Serial.println("xCMrl11");
      break;
    case 'f':
      finalLaunchReady = 1;
      //    Serial.println("Second Launch Ready is " + finalLaunchReady);
      Serial.println("xCMrl21");
      break;
    case 'u':
      launchReady = 0;
      //    Serial.println("First Launch Ready is " + launchReady);
      Serial.println("xCMrl10");
      break;
    case 'j':
      finalLaunchReady = 0;
      //    Serial.println("Second Launch Ready is " + finalLaunchReady);
      Serial.println("xCMrl20");
      break;
    case 'l':
      if (launchReady && finalLaunchReady)
      {
        //      countdown();
        Serial.println("xCMlau");
        launchTime = 1;
      }
      else
      {
        Serial.println("CM: LR1 and LR2 not ready");
      }
      break;
    case '_':
      //turn on servo power
      setServoPower(1, motorControllerPowerPin);
      break;
    case '/':
      //turn off servo power
      setServoPower(0, motorControllerPowerPin);
      break;
    case '!':
      //open servo
      valveOpen(valveServo);
      break;
    case '#':
      //close servo
      valveClose(valveServo);
      break;
    case '~':
      //get servo status
      Serial.println("~" + String(valveServo.read()) + " ::  " + String(valveStatus(valveServo)));
      break;
    default:
      break;
  }

  // If all launch ready signals have been set, then initiate launch procedures
  if (launchReady && finalLaunchReady && launchTime)
  {
    launch();
  }

}

void launch()
{
  //turn Servo -- we dont do this since the main arduino is not in charge of the launch
}



// Servo and Motor Controller Functions
void setServoPower(int servoPowerOption, int powerPin)
{
  if (servoPowerOption == 1)
  {
    digitalWrite(powerPin, HIGH);
  }
  if (servoPowerOption == 0)
  {
    digitalWrite(powerPin, LOW);
  }
}
void setValvePosition(Servo &valveServo, int newValvePosition)
// valveServo       --> reference to the servo to turn
// newValvePosition --> new angular position for the servo to turn to
{
  // int cpos = valveServo.read();
  //for (int i = cpos; i >= newValvePosition; i -= 1) { // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
  valveServo.write(newValvePosition);              // tell servo to go to position in variable 'pos'
  //  delay(3);                       // waits 15ms for the servo to reach the position
  // }
}
void valveOpen(Servo &valveServo)
{
  int pOpen = 30; //Adjustable Open Position
  setValvePosition(valveServo, pOpen);
}
void valveClose(Servo &valveServo)
{
  int pClose = 140; //Adjustable Closed Postion
  setValvePosition(valveServo, pClose);
}
int valveStatus(Servo &valveServo)
{
  int position = valveServo.read();
  int status = 0;
  if (position > 100)
  {
    status = 1;
  }
  else
  {
    status = 0;
  }
  return status;
}

