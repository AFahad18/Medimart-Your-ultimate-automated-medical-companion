//Include libraries
#include <HTTPClient.h>               //Download: https://electronoobs.com/eng_arduino_httpclient.php
#include <WiFi.h>                     //Download: https://electronoobs.com/eng_arduino_wifi.php

// rfid part
#include <SPI.h>
#include <MFRC522.h>
#include <string>

#define RST_PIN        22          // Configurable, see typical pin layout above
#define SS_PIN         5         // Configurable, see typical pin layout above

byte readCard[4];
byte a = 0;
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance



//WIFI PART---Add WIFI data
const char* ssid = "Ashik";              //Add your WIFI network name 
const char* password =  "1234567.@";           //Add WIFI password


//Variables used in the code
String LED_id = "1";                  //Just in case control more than 1 LED
String data_to_send = "";             //Text data to send to the server  
bool toggle_pressed = false;          //Each time we press the push button   
unsigned int Actual_Millis, Previous_Millis;
int refresh_time = 200;

//Inputs/outputs
int button1 = 13;                     //push button
int LED = 2;                          //Connect LED on this pin (add 150ohm resistor)
String rfid_code = "";

//Button press interruption
void IRAM_ATTR isr() {
  toggle_pressed = true; 
}


void setup() {
  delay(10);
  Serial.begin(115200);                   //Start monitor
  pinMode(LED, OUTPUT);                   //Set pin 2 as OUTPUT
  pinMode(button1, INPUT_PULLDOWN);       //Set pin 13 as INPUT with pulldown
  //attachInterrupt(button1, isr, RISING);  //Create interruption on pin 13

  WiFi.begin(ssid, password);             //Start wifi connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected, my IP: ");
  Serial.println(WiFi.localIP());
  Actual_Millis = millis();               //Save time for refresh loop
  Previous_Millis = Actual_Millis; 

  //rfid part
  
}

void readRFID(){
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	//mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
  for(uint8_t i = 0; i<4; i++){
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
    rfid_code = rfid_code + readCard[i];
    Serial.print(" ");
    delay(500);
    a +=3;
  }
  Serial.println("");
  Serial.println(rfid_code);
    
    
  mfrc522.PICC_HaltA();
  // return 1;
}

void loop() {  
  Actual_Millis = millis();
  if(Actual_Millis - Previous_Millis > refresh_time){

    //rfid scan call
   // readRFID();

    Previous_Millis = Actual_Millis; 
    if(WiFi.status()== WL_CONNECTED){                   //Check WiFi connection status  
      HTTPClient http;                                  //Create new client
      if(rfid_code != ""){                               //If button was pressed we send text: "toggle_LED"
        data_to_send = "verify_rfid=" + rfid_code;  
      }
      else{
        data_to_send = "check_medicine_status";    //If button wasn't pressed we send text: "check_LED_status"
      }
      
      //Begin new connection to website       
      http.begin("https://medimartuiu.000webhostapp.com/esp32_update.php");   //Indicate the destination webpage 
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");         //Prepare the header
      
      int response_code = http.POST(data_to_send);                                //Send the POST. This will giveg us a response code
      
      //If the code is higher than 0, it means we received a response
      if(response_code > 0){
        Serial.println("HTTP code " + String(response_code));                     //Print return code
  
        if(response_code == 200){                                                 //If code is 200, we received a good response and we can read the echo data
          String response_body = http.getString();                                //Save the data comming from the website
          Serial.print("Server reply: ");                                         //Print data to the monitor for debug
          Serial.println(response_body);

          //If the received data is rfid_verified, we set LOW the LED pin
          if(response_body == "rfid_verified"){
            
              Serial.println("rfid_verified");
            
          }
          //If the received data is LED_is_on, we set HIGH the LED pin
          else if(response_body == "1"){
              Serial.println("medicine 1");
          }  
          else if(response_body == "2"){
              Serial.println("medicine 2");
          } 
          else {
              Serial.println("no response");
          } 
        }//End of response_code = 200
      }//END of response_code > 0
      
      else{
       Serial.print("Error sending POST, code: ");
       Serial.println(response_code);
      }
      http.end();                                                                 //End the connection
    }//END of WIFI connected
    else{
      Serial.println("WIFI connection error");
    }
  }
}
