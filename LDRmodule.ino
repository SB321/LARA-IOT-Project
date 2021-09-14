int sensorPin = A0;     //LDR ANALOG SENSOR VALUE FROM PIN NUMBER A0 
int sensorValue = 0;     // INITIALISING SENSOR VALUE AS 0 

 
void setup() {         
 
   Serial.begin(9600);        
   pinMode(13,OUTPUT);        
   pinMode(12,OUTPUT);       
   pinMode(11,OUTPUT);       
   pinMode(10,OUTPUT);        
   
  }

void loop() {
  
	sensorValue = analogRead(sensorPin);      //  ANALOG VALUE OF SENSOR ISTAKEN FROM sensorPin AND STORED IN VARIABLE sensorValue          
    
	Serial.println(sensorValue);           //   SERIAL VALUE IS PRINTED IN SERIAL MONITOR    
    
	if(sensorValue < 25){                    //  THRESHOLD VALUE IS SET FOR THE LED TO GLOW, IF CONDITION IS SATISFIED THEN THE LED WILL GLOW 
        
        	digitalWrite(13,HIGH);                                  
        	digitalWrite(12,HIGH);         
        	digitalWrite(11,HIGH);         
        	digitalWrite(10,HIGH);         
        
	}
	else{
	
        	digitalWrite(13,LOW);         
        	digitalWrite(12,LOW);          
        	digitalWrite(11,LOW);          
        	digitalWrite(10,LOW);           

   	}

	delay(1000);                          // DELAY OF 10 SEC

}
