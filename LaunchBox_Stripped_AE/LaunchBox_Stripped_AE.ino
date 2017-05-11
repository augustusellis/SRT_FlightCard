//All commands need to be accounted for in switch statement
//Should probably be "launching" state where launch box just
//reads data and passes it along (Comm Master checks for abort).

//Commands
//r - readys launch 1 on
//f - final launch 2 on
//u - readys launch 1 off
//j - final launch 2 off
//l - LAUNCH
//a - abort
//s - returns state of variables

//Commands Meant for DAQ
//i - initialization: initializes SD card
//t - sensor test: sends sensor values ten times over 5 seconds
//c - collect data: collects data continuously. outputs over serial and saves. Also checks temp
//to make sure it's not too hot. Command to make pins go high to signal heat event are commented out
//e - exit data collect

//Commands Meant for Launch Box
//p - system arm
//o - igniter arm
//k - igniter continuity test
//b - buzzer
//1 - N2O fill open
//2 - N2O fill close
//3 - N2O vent open
//4 - N2O vent close
//5 - Oxygen fill open
//6 - Oxygen fill close
//7 - QD air open
//8 - QD air close
//9 - aux
//0 - chA
//q - chB

#include "LiquidCrystal.h"

int countTest;
int count2;

char missionCMD;
String data;
LiquidCrystal lcd = LiquidCrystal(39, 41, 45, 47, 49, 51);
const int delayTime = 1000;
const int lowBuzzLevel = 2;  //buzzer pwm value for "quiet" mode
const int willBuzz = HIGH; //decides if buzzer sounds at full volume when igniter is armed

int systemArmState = LOW;
int igniterArmState = LOW;
int igniterContTestState = HIGH;
int igniterState = LOW;
int buzzerState = LOW;

int igMon = LOW;
int sysMon = LOW;
boolean solsClosed = 0;
int sysMonPrev = 0;
int igMonPrev = 0;
int readyLaunch1 = 0;
int readyLaunch2 = 0;

int systemArm = 25;
int igniterArm = 23;
int igniterContTest = 40;
int buzzer = 6;
int n2OFillOpen = 38;
int n2OFillClose = 36;
int n2OVentOpen = 34;
int n2OVentClose = 32;
int oxyFillOpen = 30;
int oxyFillClose = 28;
int qdAirOpen = 26;
int qdAirClose = 24;
int aux = 22;
int chA = 31;
int chB = 29;
int igniter = 44;

int timerTrigger = 7;
int timerCheck = 8;
int prevTimerState = 0;
int timerState = 0;

int prevSolenoid;
int prev2;
int prev3;
int prev4;
double solDelay;

int prev12V = LOW;
int prev24V = LOW;

int igniterTest = 42;
int preArmMonitor = 35;
int igniterDisable = 37;

int loadCell1 = A10;
int loadCell2 = A11;
int loadCell3 = A12;
int loadCellPin1;
int loadCellPin2;
int loadCellPin3;
String lc;
boolean checkLC = 1;

int battery9 = A7;
int battery12 = A8;
int battery24 = A9;
String batts;
boolean checkBatts = 1;

void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  delay(100);
 // Serial.print("\n\n");
  Serial.print("+++");
  //  delay(100);
  //  Serial.println("ATBD 7");
  delay(100);
  Serial.println("bb");
  //Serial.println("b");
  delay(100);
  Serial.flush();
  delay(2);
  Serial.end();
  Serial.begin(9600);
}

void loop()
{
  //Serial.println("Working");
  if (Serial.available() > 0) {
    missionCMD = Serial.read();
  
  Serial3.println(missionCMD);
  Serial.println("Sent "+ missionCMD);
  }
  if (Serial3.available() > 0)
  {
    data = Serial3.readStringUntil('\n');
    Serial.println(data);
    Serial.println("Main Serial Returns Values.");
  }
}
