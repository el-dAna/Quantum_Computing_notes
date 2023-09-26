#include <LiquidCrystal.h>
#include "MCP_DAC.h" //reference the library files
MCP4921 hdTDCs_DAC;       //create DAC object https://cyberblogspot.com/how-to-use-mcp4921-dac-with-arduino/

int numCols = 16;
int numRows = 2;
int scrollSpeed_beforeStimulation = 1000;
int scrollSpeed_forStimulation = 1000;
int rs=7;
int en=8;
int d4=9;
int d5=6;
int d6=5;
int d7=12;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
String Welcome = "tDCS stimulation starts in...";
String stimulationMessage = "Active hdTDCs....";
String afterStimulation = "Stimulation Done!";



void setup(){
  hdTDCs_DAC.begin(10);     //initialize
  lcd.begin(numCols, numRows);
  OnStart(Welcome, scrollSpeed_beforeStimulation, 0.1);
  lcd.clear();
  delay(2000);
}


void loop() {  
  
  hdTDCs_DAC.analogWrite(1460);
  OnStart(stimulationMessage, scrollSpeed_forStimulation, 0.2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(afterStimulation);
  delay(2000);
  exit(0);
}


void OnStart(String message, int scrollSpeed, float minutes) {
  int count = minutes*60;
  int mins = 0;
  float secs = 0;
  bool later_rounds = false;
  lcd.clear();

  while(count > 0) {
    for (int i = 0; i < message.length() - numCols + 1; i++) {
      //lcd.clear();
      if (count < 0){break;}
      lcd.setCursor(0, 0);
      lcd.print(message.substring(i, i + numCols));
      delay(scrollSpeed);

      if (later_rounds == true){
        mins = count/60;
        secs = count-(mins*60);
        lcd.setCursor(4, 1);
        lcd.print(mins);
        lcd.print(":");
        lcd.print(secs);
        count = count - 1;
      }
    }
    later_rounds = true;
    //delay(1000);
  }
}













// #include "MCP_DAC.h" //reference the library files
// #include <LiquidCrystal.h>
// MCP4921 myDAC;       //create DAC object

// int numCols = 16;
// int numRows = 2;
// int scrollSpeed = 500;
// int rs=7;
// int en=8;
// int d4=9;
// int d5=6;
// int d6=5;
// int d7=12;
// LiquidCrystal lcd(rs,en,d4,d5,d6,d7);


// void setup() {
//   lcd.begin(16, 2);
//   lcd.print("5-Min Countdown gtg bstt sthgs thtr tht ");
//   delay(2000); // Display the title for 2 seconds
//   lcd.clear();
//   countdown(2); // Start a 5-minute countdown
// }

// void loop() {
//   // Your main loop code here (if needed)
// }




// void countdown(int minutes) {
//   int count = minutes*60;
//   int mins = 0;
//   float secs = 0;

//   while ( count > 0) {
//       lcd.setCursor(0, 0);
//       lcd.print("Time Left: ");
//       count = count - 1;
//       mins = count/60;
//       secs = count-(mins*60);
//       lcd.setCursor(4, 1);
//       lcd.print(mins);
//       lcd.print(":");
//       lcd.print(secs);
//       delay(1000);
//     }
//   lcd.clear();
// }

// void ActiveStimulation(MCP4921 DAC, int stimulationTime) {
//   DAC.analogWrite(2048);
//   String activeStimulationMessage = "hdTDCS Stimulation";

//   countdown(activeStimulationMessage, stimulationTime);
// }




