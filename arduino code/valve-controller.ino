#include "Particle.h"
// First, we're going to make some variables.
// This is our "shorthand" that we'll use throughout the program:

int valve = D0; // Instead of writing D0 over and over again, we'll write led1
// You'll need to wire an LED to this one to see it blink.


// Having declared these variables, let's move on to the setup function.
// The setup function is a standard part of any microcontroller program.
// It runs only once when the device boots up or is reset.

void setup() {

  // We are going to tell our device that D0 and D7 (which we named led1 and led2 respectively) are going to be output
  // (That means that we will be sending voltage to them, rather than monitoring voltage that comes from them)

  // It's important you do this here, inside the setup() function rather than outside it or in the loop function.

  pinMode(valve, OUTPUT);


  Particle.subscribe("Water", tempHandler, MY_DEVICES);

  

}

// Next we have the loop function, the other essential part of a microcontroller program.
// This routine gets repeated over and over, as quickly as possible and as many times as possible, after the setup function is called.
// Note: Code that blocks for too long (like more than 5 seconds), can make weird things happen (like dropping the network connection).  The built-in delay function shown below safely interleaves required background activity, so arbitrarily long delays can safely be done if you need them.

void loop() {
   

}

void waterHandler(const char *event, const char *data)
{
    if(data == "off")
    {
        digitalWrite(led1, Low);
    }
    
    
    if(data == "on")
    {
    digitalWrite(led1, HIGH);
    }

}



