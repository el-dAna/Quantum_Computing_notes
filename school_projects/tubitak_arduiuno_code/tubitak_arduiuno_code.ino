#include "MCP_DAC.h" //reference the library files
#include <LiquidCrystal.h>
MCP4921 myDAC;       //create DAC object

int rs=12;
int en=9;
int d4=5;
int d5=4;
int d6=3;
int d7=2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);


void setup(){
myDAC.begin(10);     //initialize
lcd.begin(16,1);
}

void loop() {
  // 4095
  // 2048
myDAC.analogWrite(1390);  //output a voltage about 1/2 of Vref
lcd.setCursor(2,1);
lcd.autoscroll();
lcd.print(1);
delay(1000);
// lcd.print("Watch me count");
// for (int j=1;j<=10;j=j+1){
//   lcd.setCursor(0,1);
//   lcd.print(j);
//   delay(500); 
// }
 lcd.clear();
}

