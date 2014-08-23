

#include "Wifly.h"
#include <SoftwareSerial.h>

#define BUFFERSIZE 100
#define SSSID "AndroidAP"
#define PASSWORD "freecandy"

WiflyClass Wifly(2,3);
int i = 0;
char buff[BUFFERSIZE];
char temp;


void setup()
{
  Serial.begin(9600);
  Wifly.init();
     
 // Wifly.setConfig(SSSID,PASSWORD);
  Wifly.join(SSSID);
  Wifly.checkAssociated();
 // Wifly.sendCommand("set uart mode 0\r", "AOK");
  delay(100);
  Wifly.sendCommand("set ip proto 18\r", "AOK");  //Enable shield to act as html client
  delay(100);
  Wifly.sendCommand("set dns name graph.facebook.com\r", "AOK"); //Set destination server to send requests to (Not a dns server)
  delay(100);
  Wifly.sendCommand("set ip address 0\r", "AOK"); //Apparently forces shield to use DNS address instead of IP
  delay(100);
  Wifly.sendCommand("set ip remote 80\r", "AOK");//Set webserver port to 80
  delay(100);
  Wifly.sendCommand("set com remote 0\r", "AOK"); //I am 60-70% sure that this prevents the shield from inserting sensor data into GET requests
  delay(100);
  Wifly.sendCommand("set com open 0\r", "AOK");
  delay(100);
  
  Wifly.sendCommand("set com clost 0\r", "AOK");
  delay(100);
  //Wifly.sendCommand("set com size 1420\r", "AOK");
  Serial.print("Ready to go\n");
   
   // Wifly.join("bluesat");
    Wifly.sendCommand("open\r", "AOK");
  Wifly.sendCommand("GET /fql?q=SELECT%20fan_count%20FROM%20page%20WHERE%20username%20=%20%22eetunsw%22 HTTP/1.1\r\nHost: graph.facebook.com\r\nConnection: close\r\n\r\n", "AOK");
  i = 0;
  Wifly.sendCommand("close\r", "AOK");
  Wifly.sendCommand("EXIT\r","exit");
  Serial.print("Trying to read\n");
/*  while(Wifly.canReadFromSocket()&& i < BUFFERSIZE)
   {
    temp = Wifly.readFromSocket();	
    buff[i] = temp;
    i++;
  }  
  Serial.print("Printing Buffer:");
  Serial.print(buff);
   */
  
   // Wifly.sendCommand("open graph.facebook.com 80", "");
 // Â
  /*
  Wifly.sendCommand("set dns name www.google.com\r", "AOK");
  Wifly.sendCommand("set ip host graph.facebook.com\r", "AOK");
  Wifly.sendCommand("set sys autoconn 1\r", "AOK");
  Wifly.sendCommand("set com idle 200 1\r", "AOK");
  Wifly.sendCommand("set sys sleep 2 1\r", "AOK");
  Wifly.sendCommand("set sys wake 20\r", "AOK");
  Wifly.sendCommand("set uart mode 2\r", "AOK");
  */
  
  
//  while(!Wifly.connect("192.168.1.164","90"));
//  Wifly.writeToSocket("Connected!");
}
void loop()
{
  delay(1000);
  Serial.print("Entered Loop\n");
 // Wifly.SoftwareSerial::print("$$$");
 // Wifly.SoftwareSerial::print("open\r");
 // Wifly.SoftwareSerial::print("GET /fql?q=SELECT%20fan_count%20FROM%20page%20WHERE%20username%20=%20%22eetunsw%22 HTTP/1.1\r\nHost: graph.facebook.com\r\nConnection: close\r\n\r\n");
 //  Wifly.SoftwareSerial::print("exit\r");
  Wifly.sendCommand("$$$", "CMD");
  Wifly.sendCommand("open\r", "AOK");
  Wifly.sendCommand("GET /fql?q=SELECT%20fan_count%20FROM%20page%20WHERE%20username%20=%20%22eetunsw%22 HTTP/1.1\r\nHost: graph.facebook.com\r\nConnection: close\r\n\r\n", "AOK");
  //Wifly.sendCommand("close\r", "AOK");
 // Wifly.sendCommand("EXIT\r","exit");
 /* i = 0;
  while(Wifly.canReadFromSocket()&& i < BUFFERSIZE)
   {
    temp = Wifly.readFromSocket();	
    buff[i] = temp;
    i++;
  }
  Serial.print(buff);
  if(Serial.available())
  {
    
    Wifly.print((char)Serial.read());
    
  }*/
}


