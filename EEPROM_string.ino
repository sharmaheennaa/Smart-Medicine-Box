#include <EEPROM.h>
 
void writeString(char add,String data);
String read_String(char add);
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM.begin(512);
  String data = "0600";
 
  Serial.print("Writing Data:");
  Serial.println(data);
 
  writeString(10, data);  //Address 10 and String type data
  delay(10);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  String recivedData;
  recivedData = read_String(10);
  Serial.print("Read Data:");
  Serial.println(recivedData);
  delay(1000);
}
 
void writeString(char add,String data)
{
  int _size = data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
  EEPROM.commit();
}
 
 
String read_String(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<500)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }
  data[len]='\0';
  return String(data);
}
