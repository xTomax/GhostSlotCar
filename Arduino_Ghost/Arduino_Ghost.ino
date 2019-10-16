//On Uno, one shall have like 1Kb of available EEPROM

 Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.

#include <EEPROM.h>

void printTemp();
void clearEEPROM();
void writeTemp();

/** PWM pins duty **/
/** 3,9,10,11 - 490hz = 2.04 ms   | This ones will do perfectly, should use less proc **/
/** 5,6 - 980hz = 1.02 ms   **/
pwmPinTrack1 = 3;
pwmPinTrack1 = 9;
pwmPinTrack1 = 10;
pwmPinTrack1 = 11;

int address = 0; //Retains the Max EEPROM address in use.
unsigned long timer = 0;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
     
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  //Can be removed when lots of work.
  delay(1);
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  
void printData()
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    byte value = EEPROM.read(i);                //read EEPROM data at address i
    if(value != 0)                              //skip "empty" addresses
    {
      float temp = value*conv_coeff;            //convert ADC values to temperature
      temp = (temp - 0.5)*100;                  //take care of the offset
 
      Serial.println(temp);
    }
  }
}

byte readLastData()
{
    return EEPROM.read(address);                //read EEPROM data at address "address"
}

 
void clearEEPROM()
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    if(EEPROM.read(i) != 0)                     //skip already "empty" addresses
    {
      EEPROM.write(i, 0);                       //write 0 to address i
    }
  }
  Serial.println("EEPROM erased");
  address = 0;                                  //reset address counter
}

/* Receive the actual value and compare to the last write, if the diference is "Justifiable" write it next*/
void writeData(byte val)
{
  if (address == 0){
    EEPROM.write(address, val);
    address++;
    return
  }
  if(address == EEPROM.length())  //check if address counter has reached the end of EEPROM
  {
    Serial.print("Reach the maximum Address. Cant store anymore info. Last address: ");
    Serial.println(address);
    return;
  }
  byte last = readLastData();
  if (last - 2 > val || last + 2 < val){
    EEPROM.write(address, value);         //write value to current address counter address
    Serial.print("Sensor value stored at address ");
    Serial.println(address);
    address++;                      //increment address counter
  }

}
  
}
