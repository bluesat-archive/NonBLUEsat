#include <Debug.h>
#include <WiFly_communicator.h>

#define WIFI_SSID "eet_gumball"
#define WIFI_PASS "freecandy"

#define FB_IP "69.171.224.54,80"
#define FB_PACKET "GET /fql?q=SELECT%20fan_count%20FROM%20page%20WHERE%20username%20=%20%22eetunsw%22 HTTP/1.1\r\nHost: graph.facebook.com\r\n"

#define BUFFER_LEN 1000

#define MANUAL_SW 2
#define ASSOC 3
#define POLLING_LED 11

char packet_buf[BUFFER_LEN];
int fans;
int old_fans = -1;

void setup() {
  Serial.begin(115200);
  pinMode(POLLING_LED, OUTPUT);
  pinMode(ASSOC, OUTPUT);
  stepperSetup();
  
  //5s Startup delay
  delay(5000);
  
  //Connect to WIFI
  wizfi_connect(WIFI_SSID, WIFI_PASS);
  
  //Success! Wifi connected
  
  //Flush WIFI buffer
  delay(1000);
  Serial.flush();
}

void loop() {
  while ( digitalRead(ASSOC) )
    wizfi_connect(WIFI_SSID, WIFI_PASS); 
 
  digitalWrite(POLLING_LED, HIGH);
  wizfi_tcp_connect(FB_IP);
 
  digitalWrite(POLLING_LED, LOW);
  wizfi_sendtcp('0', FB_PACKET, packet_buf, BUFFER_LEN);
  fans = get_fan_count(packet_buf);
  
  if ( old_fans == -1 )
    old_fans = fans;
  if ( fans < old_fans ) //an unlike!! :(
    old_fans = fans;
  if ( fans > old_fans ) {
    old_fans = fans;
    stepperRevolution(); 
  }
  
  while (digitalRead(MANUAL_SW)) {
    stepperSpin();  
  }
}

int get_fan_count(char *packet) {
  int fans_start = strpos(packet_buf, "fan_count", 0) + 11;
  int fans_stop = strpos(packet_buf, "}", fans_start);
  return atoi(substr(packet_buf,fans_start, fans_stop)); 
}
