/* ValveControl
 by Angel Castrellon
 This code is meant to control the NO2 Valve, by send sending commands via serial communications. 
 modified 22 October 2016
 by Angel Castrellon
*/

/*
 *  Valid Commands: type $val followed by
    -o =Open;
    -c =Close
    -s =Status
*/
#include <Servo.h> //includes the Servo library 


const int baud=9600;// Sets buad rate, this will nit be changed


Servo Valve;  // create servo object called Valve
int pOpen=30; //Adjustable Open Position
int pClose=140; //Adjustable Closed Postion
char myName[]= {'v','a','l'};//
char c;
int stat=0;//status value; '0' is closed '1' is open 

void setup() {
  
  Valve.attach(9);// attaches the valve servo on pin 9 to the servo object
  delay(500);
  Serial.begin(baud);// Initializes Serial object; Serial will automatically 
                    // transmit and revcive from the RX and TX pins 
  delay(100);
  //Valve.write(pClose);<---- Don't uncommment this
  delay(2000);
  menu();
}

void loop() {
  c='0';//Initializez c
 if (Serial.available())//Check is Serial is abavalible, if so read into the serial port
  {
    c=Serial.read();
  }
  if(c=='$')// The '$' character denotes the beginning of a command
  {
   //Serial.println("triggered");<---- Debuggin code
   int cnt=0;//Counter to check the length of a input
   while(Serial.available()<5 || cnt<10)
   { 
    cnt++;
     delay(100);
   }
   char charlie[3];//charlie is a character array handel
   //Serial.println("name check");<---- Debugging code
   boolean passed=true;//boolean determines whether or not a valid command 
   for (int i=0;i<3;i++)//This loop check charlie against myName
   {
     charlie[i]=Serial.read();
     if(charlie[i]!=myName[i])
     {
      passed=false;//sets passed to false
      break;//if the name is not the same break out of the for loop
     }
   }
   if(passed)
   {
    //Serial.println("Getting command");<-----Debugging Code
    Serial.read();
    char com=Serial.read();
    dotexe(com);
   }
  }
  else if(c!='0')
  {
    menu();
  }
}


void dotexe(char q)
{//executes commands
  int cpos=Valve.read();
  switch(q)
  {
    case 'o':
    //Valve.write(pOpen);
    //delay(15);
    moveToPos(cpos,pOpen);
    Serial.println("Valve has been Opened");
    Serial.println(Valve.read());
    stat=1;
    break;
    
    case 'c':
    //Serial.println(Valve.read());
    //Valve.write(pClose);
    //delay(15)
    moveToPos(cpos,pClose);
    Serial.println("Valve has been Closed");
    Serial.println(Valve.read());
    stat=0;
    break;
    
    case 's':
    if(stat==0)
    {
      Serial.println("Status: Closed");
    }
    else if(stat==1)
    {
      Serial.println("Status: Open");
    }
    break;
    
    default :
    Serial.println("Invalid Command");
    menu();
    break;
    
  }  
}

void menu()
{
    //displays valid command list  
    Serial.println("Valid Commands: type $val followed by");
    Serial.println("-o =Open");
    Serial.println("-c =Close");
    Serial.println("-s =Status");
}

void moveToPos(int b, int e)
{
  for (int i = b; i >= e; i -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Valve.write(i);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15ms for the servo to reach the position
  }
  for (int i = b; i <= e; i += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Valve.write(i);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15ms for the servo to reach the position
  }
  //sopl(String(myservo.read()));
}



