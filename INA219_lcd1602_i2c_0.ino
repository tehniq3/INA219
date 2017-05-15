// base sketch from http://henrysbench.capnfatz.com/henrys-bench/arduino-current-measurements/ina219-arduino-current-sensor-voltmeter-tutorial-quick-start/
// adapted sketch by Nicu FLORICA (niq_ro) from http://www.tehnic.go.ro
// & http://www.arduinotehniq.com 

#include <Wire.h>
#include <Adafruit_INA219.h> // You will need to download this library

Adafruit_INA219 sensor219; // Declare and instance of INA219

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

 float busVoltage = 0;  // measure in volts
 float current = 0; // Measure in milli amps
 float current2 = 0; // for amps
 float power = 0;  // measure in watts

void setup(void) 
{
      
  Serial.begin(9600);    
  sensor219.begin();
  
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("INA219 Current &");
  lcd.setCursor(1,1);
  lcd.print("Voltage Sensor");
  delay(3000);
  lcd.clear();
}

void loop(void) 
{
 
  busVoltage = sensor219.getBusVoltage_V();
  current = sensor219.getCurrent_mA();
  power = busVoltage * (current/1000); // Calculate the Power
   
  Serial.print("Bus Voltage:   "); 
  Serial.print(busVoltage); 
  Serial.println(" V");  
  
  Serial.print("Current:       "); 
  Serial.print(current); 
  Serial.println(" mA");
  
  Serial.print("Power:         "); 
  Serial.print(power); 
  Serial.println(" W");  
  
  Serial.println("");  

lcd.setCursor(0,0);
lcd.print("U=");
if (busVoltage < 10.0) lcd.print(" ");
lcd.print(busVoltage);
lcd.print("V");


lcd.setCursor(0,1);
lcd.print("I=");
if (current < 1000.0) lcd.print(" ");
if (current < 100.0) lcd.print(" ");
if (current < 10.0) lcd.print(" ");
lcd.print(current,1);
lcd.print("mA");
delay(1000);
lcd.setCursor(0,1);
lcd.print("I= ");
int i1 = (current + 0.5)/1000;
int irest = current + 0.5 - 1000*i1;
int i2 = irest/100;
int irest2 = irest - 100*i2;
int i3 = irest2/10;
int i4 = irest2%10;

lcd.print(i1);
lcd.print(".");
lcd.print(i2);
lcd.print(i3);
lcd.print(i4);
lcd.print("A    ");

  delay(1000);
}
