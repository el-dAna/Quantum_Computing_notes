// #include "MCP_DAC.h" //reference the library files
// MCP4921 myDAC;       //create DAC object

// void setup(){
// myDAC.begin(10);     //initialize
// }

// void loop(){
// myDAC.analogWrite(2048);  //output a voltage about 1/2 of Vref
// }


#include <LiquidCrystal.h>
int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
}

void loop() {
lcd.setCursor(0,0);
lcd.print("Watch me Count");
// for (int j=1;j<=10;j=j+1){
//   lcd.setCursor(0,1);
//   lcd.print(j);
//   delay(500);
 
// }
//  lcd.clear();
}