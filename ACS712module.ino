#include <Ethernet.h>      
// HEADER FILE TO USE NODEMCU TO SEND DATA TO CLOUD                     
#include <ESP8266WiFi.h>;                        
#include <WiFiClient.h>;
 // HEADER FILE OF THINKSPEAK (I.E CLOUD TO STORE DATA REAL TIME AND IS FETCHED BY APP)
#include <ThingSpeak.h>;                       


int mVperAmp = 185;                              // Sensitivity of 5 amp ACS712
int RawValue= 0;                                 // VARIABLE TO STORE ANALOG VALUE OF SENSOR AND IS INITIALISED TO 0
int ACSoffset = 2500;                            // OFFSET VALUE IS SET TO  2500 B, BECAUSE TO GET ACCURATE READING
double Voltage = 0;                              

//Network SSID
const char* ssid = "123456789"; 
//Network Password                
const char* password = "123456789";  
//LDR Pin Connected at A0 Pin           
int LDRpin = A0;                                

WiFiClient client;
 
unsigned long myChannelNumber = 818583;             //Channel Number 
const char * myWriteAPIKey = "80YWPYX6GJM8F525";    


void setup() {
  
 
  Serial.begin(9600);                                //baud rate at which arduino communicates with Laptop/PC
  
  WiFi.begin(ssid, password);                        // BEGING WIFI CONNECTION 
  ThingSpeak.begin(client);

  Serial.print("DC Current Sensor");                 // PRINT THE MESSAGE IN SERIAL MONITOR
  Serial.print("ACS 712");
}

void loop()                                                    
{
  printData();   
}

void printData(){

   int sumVoltage=0,sumCurrent=0;
   
   for(int lc=1;lc<=4;lc++){
                                
     RawValue = analogRead(analogIn);                             // analog value of sensor is stored in variable RawValue
     Voltage = (RawValue / 1023.0) * 5;                           // Gets you mV
     Amps = ((  2400-Voltage) / mVperAmp);                        // Formula for calculation of current
     
     Serial.print("\nRaw Value = " );                             
     Serial.print(RawValue);                                     
    
     Serial.print("\nVOLTAGE = " );                              
     Serial.print((Voltage*10)+180);                             
     
     Serial.print("\n CURRENT VALUE = " );                       
     Serial.print(Amps);                                        
  
      sumVoltage=sumVoltage+Voltage;                            // this statement is exectuted to take average of 4 value of voltage and then print to get accurate value 
      sumCurrent=sumCurrent+Amps;                               // this statement is exectuted to take average of 4 value of current and then print to get accurate value 
        delay(5000);                                            // delay is provided for 5 sec
   }
   

   int voltAvg=sumVoltage/4;                                   // average of voltage is calulated and saved in voltAvg
   int curAvg=sumCurrent/4;                                    
   sendDataThingspeak(voltAvg,curAvg);                         
                     
}

void sendDataThingspeak(int avgVoltage,int avgCurrent){        
  
 

  ThingSpeak.setField(1,(float)avgVoltage);                     
  ThingSpeak.setField(2,(float)avgCurrent);                    
  ThingSpeak.writeFields(myChannelNumber,  myWriteAPIKey);     
 
}
