/*************************************************** 
  Receive a string of 1s and 0s over serial and 
  display on the screen, works well if connected to 
  an electric imp or similar
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // if the string is complete

void setup() {
 
  Serial.begin(57600);
  Serial.println("8x8 LED Matrix Test");
  
  matrix.begin(0x70);  // pass in the address
}

void loop() {
  
  //if we have serial data
  if (Serial.available()){
    
    //loop through all received serial characters
    while (Serial.available()) {
    
      // get the new byte:
      char inChar = (char)Serial.read(); 
      
      if (inChar == 'a'){
          //empty the string
          inputString = ""; 
      } else {
      
        // add it to the inputString:
        inputString += inChar;
      }
      
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '\n') {
        stringComplete = true;
      }
    }
    
    Serial.println(inputString);
  }
  
  if (inputString != ""){
    //set rotation
    matrix.setRotation(0);
  
    //clear the matrix
    matrix.clear();   
    
    //loop through the received data
    int pixelLoop = 0;
    for (int i = 0; i < 8; i++) { 
      for (int j = 0; j < 8; j++) { 
       //if there is a 1
       if (inputString.charAt(pixelLoop) == '1') {
         //draw a pixel
         matrix.drawPixel(j, i, LED_ON); 
        }
        //incrament the loop
        pixelLoop++;
      }
    }  
    
    //write to the display
    matrix.writeDisplay();
  }
 
  
}

