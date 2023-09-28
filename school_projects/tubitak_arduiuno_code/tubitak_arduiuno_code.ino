#include <LiquidCrystal.h>
#include "MCP_DAC.h" //reference the library files
MCP4921 hdTDCs_DAC(5, 2);       //create DAC object https://cyberblogspot.com/how-to-use-mcp4921-dac-with-arduino/

int numCols = 16;
int numRows = 2;
int scrollSpeed_beforeStimulation = 1000;
int scrollSpeed_forStimulation = 1000;

const int electrode = A0;
int rs=7;
int en=8;
int d4=9;
int d5=6;
int d6=11; // 11, 5
int d7=12;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);


bool all_passed;
int number_of_warns = 1;

String Welcome = "tDCS stimulation starts in...";
String stimulationMessage = "Active hdTDCs....";
String afterStimulation = "Stimulation Done!";



void setup(){
  Serial.begin(9600);
  hdTDCs_DAC.begin(3);     //initialize
  lcd.begin(numCols, numRows);
  OnStart(Welcome, scrollSpeed_beforeStimulation, 0.1);
  lcd.clear();
  delay(2000);

  running_checks:
  all_passed = Run_Checks();
  if (!all_passed){
    number_of_warns++;
    goto running_checks;
  }
  

}


void loop() {  
  // float electrode_voltage = get_voltage(electrode, true);
  // lcd.setCursor(0, 0);
  // lcd.print("E_voltage");
  // lcd.setCursor(0, 1);
  // lcd.print(electrode_voltage);
  // delay(2000);
  // lcd.clear();


  // hdTDCs_DAC.analogWrite(1660);
  Stimulation(true);
  OnStart(stimulationMessage, scrollSpeed_forStimulation, 0.2);
  lcd.clear();
  lcd.setCursor(0, 0);
  // hdTDCs_DAC.analogWrite(0);
  Stimulation(false);
  lcd.print(afterStimulation);
  delay(2000);
  exit(0);
}


void Stimulation(bool active){
  if (active){
    hdTDCs_DAC.analogWrite(1660);
  }else{
    hdTDCs_DAC.analogWrite(0);
  }
}


bool assertWithErrorMessage(bool condition, String possible_error, float measured_voltage) {
  bool passed_check;
  if (!condition) {
    //If monitor available
    Serial.print("WARNING ");
    Serial.println(number_of_warns);
    Serial.print(measured_voltage);
    Serial.println("Volts");
    Serial.println(possible_error);
    delay(3000);
    
    //If only LCD available
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WARN");
    lcd.setCursor(5, 0);
    lcd.print(number_of_warns);
    lcd.setCursor(8, 0);
    lcd.print(measured_voltage);
    lcd.setCursor(12, 0);
    lcd.print("V");
    lcd.setCursor(0, 1);
    lcd.print(possible_error);
    


    passed_check = false;
    //exit(0);
  }
  return passed_check;
}

float get_voltage(int AnaloguePin, bool SerialMonitor) {
  int analogValue = analogRead(AnaloguePin);
  // Convert the analog value to a voltage
  float voltage = analogValue * (5.0 / 1023.0);

  if (SerialMonitor) {
    // Print the voltage to the serial port
    Serial.print("Voltage: ");
    Serial.println(voltage);
    // Wait for 1 second
    delay(1000);
  }
  return voltage;
}


bool Run_Checks(){
  float voltage_at_electrodes = get_voltage(electrode, false);
  bool condition_1 = voltage_at_electrodes > 100;
  bool condition_1_result = assertWithErrorMessage(condition_1, "Wrong eltrd. V!", voltage_at_electrodes);

  return condition_1_result;
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




