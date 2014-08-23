#include <Configuration.h>
#include <Debug.h>
#include <ParsedStream.h>
#include <SpiUart.h>
#include <WiFly.h>
#include <WiFlyClient.h>
#include <WiFlyDevice.h>
#include <WiFlyServer.h>
// (Based on Ethernet's WebClient Example)
#include <SPI.h>


byte server[] = { 66, 249, 89, 104 }; // Google

//Client client(server, 80);

WiFlyClient client;

void setup() {
  
  Serial.begin(9600);

  Serial.println("Here we go");
  
  WiFly.begin();
  
  Serial.println("Here we go");
  
  if (!WiFly.join("gumball", "freecandy")) {
    Serial.println("Association failed.");
    while (1) {
      // Hang on failure.
    }
  }  

  Serial.println("connecting...");

  if (client.connect("google.com", 80)) {
    Serial.println("connected");
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } else {
    Serial.println("connection failed");
  }
  
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}


