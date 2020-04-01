#include <SPI.h> // Include SPI library - needed for speaking to the Ethernet shield
#include <Ethernet.h> // Include the Ethernet Library for controlling the Ethernet shield
#include <PubNub.h> // Include the PubNub library to publish data to our channel

byte mac[] = {0x00, 0x0E, 0xEF, 0x00, 0x00, 0x34}; 

int light = 0; // store the current light value
int light1 = 0;
int light2 = 0;

char pubkey[] = "pub-c-c4baa104-97d7-4d3c-a403-1f04295d861e";
char subkey[] = "sub-c-b4e92c8e-639d-11ea-b5f8-9a833ea0503a";
char channel[] = "ioechannel";

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600); //configure serial to talk to computer
    Serial.print("Serial set up");

    while(!Ethernet.begin(mac)) { // try starting our Ethernet connection using the MAC address
      Serial.println("Ethernet setup error!"); // if it returns false print the error statement
      delay(1000); // wait 1 second
    }
    Serial.println("Ethernet set up");
    PubNub.begin(pubkey,subkey); // start our PubNub set up
    Serial.println("Pubnub set up");
}

void loop() {
    // put your main code here, to run repeatedly:

    Ethernet.maintain(); // Manages DHCP leases on network
    EthernetClient *client; // Pointer to an EthernetClient

    light = analogRead(A0); // read and save value from PR
    light1 = analogRead(A1);
    light2 = analogRead(A2);
    
    Serial.println(light); // print current light value

    char msg[64] = "{\"eon\":{\"sensor\":"; // Formatting our message to be a JSON object

        sprintf(msg + strlen(msg), "%d", analogRead(light)); // Using sprintf to add our integer sensor reading

      strcat(msg, "}}"); // Concatenating the two curly braces on the end

    Serial.print("Publishing: ");
    Serial.println(msg);

    client = PubNub.publish(channel, msg); // try publishing our message
 
    if(light > 700) { // If it is bright...
        Serial.println("It is quite light!");
      
    }
    else if(light > 650 && light < 699) { // If it is average light...
        Serial.println("It is average light!");
  
    }
    else { // If it's dark...
        Serial.println("It is pretty dark!");
        
    }

   Serial.println(light1); // print current light value
 
    if(light > 700) { // If it is bright...
        Serial.println("It is quite light!");
      
    }
    else if(light > 650 && light < 699) { // If it is average light...
        Serial.println("It is average light!");
  
    }
    else { // If it's dark...
        Serial.println("It is pretty dark!");
        
    }
    Serial.println(light2); // print current light value
 
    if(light > 700) { // If it is bright...
        Serial.println("It is quite light!");
      
    }
    else if(light > 650 && light < 699) { // If it is average light...
        Serial.println("It is average light!");
  
    }
    else { // If it's dark...
        Serial.println("It is pretty dark!");
        
    }
    
    delay(1000); // don't spam the computer!
}
