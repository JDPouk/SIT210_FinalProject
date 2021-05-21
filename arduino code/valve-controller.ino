// This #include statement was automatically added by the Particle IDE.

#include "Particle.h"
#include <JsonParserGeneratorRK.h>
// First, we're going to make some variables.
// This is our "shorthand" that we'll use throughout the program:

int valve = D3; // Instead of writing D3 over and over again, we'll write valve

int sensor1= A1;

int waterState = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
long OnTime = 60000;           // milliseconds of on-time
long OffTime = 60000; 
unsigned long currentMillis;
int Moisture;
String Current = "12:10";
String setTime = "0";
// Having declared these variables, let's move on to the setup function.
// The setup function is a standard part of any microcontroller program.
// It runs only once when the device boots up or is reset.

void setup() {



  pinMode(valve, OUTPUT);
  pinMode(sensor1, INPUT);


  Particle.subscribe("Water", waterHandler, MY_DEVICES);
  Particle.subscribe("set time", timeHandler, MY_DEVICES);
  Particle.subscribe("Current Time", currentHandler, MY_DEVICES);
  

}



void loop() {
    currentMillis = millis();
      Moisture =  analogRead(sensor1);
      createEventPayload(Moisture);
      
    if(setTime == Current)
  {
     createEventPayload(Moisture);
    waterState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(valve, waterState);
  }
      
    
    if((waterState == HIGH) && (currentMillis - previousMillis >= OnTime))
  {
      createEventPayload(Moisture);
    waterState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(valve, waterState);  // Update the actual LED
  }
  else if ((waterState == LOW) && (currentMillis - previousMillis >= OffTime))
  {
      createEventPayload(Moisture);
    waterState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(valve, waterState);	  // Update the actual LED
  }
}



void createEventPayload(int humid)
{
    JsonWriterStatic<256> jw;
    {
        JsonWriterAutoObject obj(&jw);
        jw.insertKeyValue("Moisture",Moisture);
    }
    Particle.publish("Moisture_Vals", jw.getBuffer(), PRIVATE);

}



void waterHandler(const char *event, const char *data)
{
     Moisture =  analogRead(sensor1);
    String val = String(data);
    if(val== "off")
    {
      createEventPayload(Moisture);
    waterState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(valve, waterState); 
    }
    
    
    if(val == "on")
    {
     createEventPayload(Moisture);
    waterState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(valve, waterState);
    }

}



void timeHandler(const char *event, const char *data)
{
   setTime = String(data);

}

void currentHandler(const char *event, const char *data)
{
   Current = String(data);

}
