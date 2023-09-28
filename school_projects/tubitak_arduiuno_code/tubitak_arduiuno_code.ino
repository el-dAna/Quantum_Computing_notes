#include <LiquidCrystal.h>
#include "MCP_DAC.h" //reference the library files
MCP4921 hdTDCs_DAC(5, 2); //third and second yellow wires from the red 5V input to DAC from Arduiuno     //create DAC object https://cyberblogspot.com/how-to-use-mcp4921-dac-with-arduino/
int DAC_output_pin = 3; //yellow wire close to red 5V input to DAC from Arduiuno 

int numCols = 16;
int numRows = 2;
int scrollSpeed_beforeStimulation = 1000;
int scrollSpeed_forStimulation = 1000;

const int electrode = A0; //9V red cable voltage from regulator t arduiuno
const int five_volt_probe = A2; //5V orange cable from arduiuno to DAC Vin
const int DAC_output_voltage_probe = A1; // blue cable to measure output voltage of DAC
float Set_DAC_Vout;

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

  Set_DAC_Vout = 1460; // Tune DAC Vout here

  Serial.begin(9600);
  hdTDCs_DAC.begin(DAC_output_pin);     //initialize
  lcd.begin(numCols, numRows);
  OnStart(Welcome, scrollSpeed_beforeStimulation, 0.1);
  lcd.clear();
  delay(2000);

  run_checks_again: // a checkpoint to return to if any of the checks fail. if any check fail then 10mA current will not be output!
  all_passed = Run_Checks(set_DAC_Vout);
  if (!all_passed){
    number_of_warns++;
    goto run_checks_again;
  }
  

}


void loop() {  

  // hdTDCs_DAC.analogWrite(1660);
  Stimulation(true, Set_DAC_Vout);
  OnStart(stimulationMessage, scrollSpeed_forStimulation, 0.2);
  lcd.clear();
  lcd.setCursor(0, 0);
  // hdTDCs_DAC.analogWrite(0);
  Stimulation(false);
  lcd.print(afterStimulation);
  delay(2000);
  exit(0);
}




void Stimulation(bool active, float set_DAC_Vout){
  if (active){
    hdTDCs_DAC.analogWrite(set_DAC_Vout);
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
    lcd.setCursor(9, 0);
    lcd.print(measured_voltage);
    lcd.setCursor(13, 0);
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


bool Run_Checks(float DAC_Vout){
  int checks_list[3];

  //Checks 9V from voltage regulator to arduiuno
  float voltage_at_electrodes = get_voltage(electrode, false);
  bool condition_A0 = voltage_at_electrodes >= 9; //this is fixed, Vout of 9V regulator
  bool condition_A0_result = assertWithErrorMessage(condition_A0, "Wrong eltrd. V!", voltage_at_electrodes);
  
  //Checks 5V from arduiuno to DAC
  float 5V_to_DAC_voltage = get_voltage(five_volt_probe, false);
  bool condition_A2 = 5V_to_DAC_voltage >= 4.7; // this is fixed, close to 5V from arduiuno
  bool condition_A2_result = assertWithErrorMessage(condition_A2, "Wrong DAC V_in!", 5V_to_DAC_voltage);

  //checks the Vout of DAC to electrodes
  float DAC_Vout = get_voltage(DAC_output_voltage_probe, false);
  bool condition_A1 = DAC_Vout >= DAC_Vout; //tune DAC to output 10mA and set that voltage
  bool condition_A1_result = assertWithErrorMessage(condition_A1, "Wrong DAC V_out!", DAC_Vout);

  checks_list[0] = condition_A0_result;
  checks_list[1] = condition_A1_result;
  checks_list[2] = condition_A2_result;
  bool all_checks_passed = checks_list[0] & checks_list[1] & checks_list[2];

  return all_checks_passed;
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




