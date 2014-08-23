//To program, remove jumper in WLAN_TX to D0


#define RESPONSE_SIZE 28
#define DELAY_OFFSET 1000

#define MANUAL_SW 2
#define ASSOC 3
#define POLLING_LED 11

int tmp;
int startBuffer;
char chartemp;
int i;
int fans;
long start;
int old_fans;
char buffer[RESPONSE_SIZE];
void setup() {
  stepperSetup();
  old_fans = -1;
    pinMode(POLLING_LED, OUTPUT);
  pinMode(ASSOC, OUTPUT);
  Serial.begin(9600);
 // delay(5000);
  Serial.write("$$$");
  delay(500);
  Serial.write("set uart mode 1\r");  //Disable Echo from Wifly
  delay(50);
  Serial.write("set wlan linkmon 0\r"); //Disable network timeout
  delay(50);
  Serial.write("set wlan phrase freecandy\r"); //Set pass prhase
  delay(1000);
  Serial.write("join eet_gumball\r");
  delay(5000);
  Serial.write("set ip proto 18\r");
  delay(50);
  Serial.write("set dns name graph.facebook.com\r");
  delay(100);
  Serial.write("set ip address 0\r");
  delay(50);
  Serial.write("set ip remote 80\r");
  delay(50);
  Serial.write("set com remote 0\r");
  delay(50);
  Serial.write("set com open 0\r");
  delay(50);
  Serial.write("set com close 0\r");
  delay(50);
  Serial.write("set sys iofunc 0x40\r"); //GPO5 shows TCP status
  delay(50);
  Serial.write("set wlan join 1\r"); //GPO5 shows TCP status
  delay(50);
  //Serial.write("exit\r");
  delay(200);
  Serial.write("open\r");
  delay(2000);
  Serial.write("GET /fql?q=SELECT%20fan_count%20FROM%20page%20WHERE%20username%20=%20%22eetunsw%22 HTTP/1.1\r\nHost: graph.facebook.com\r\nConnection: close\r\n\r\n");
  while(Serial.available()) { Serial.read(); }
  while(Serial.available() == 0) {};
  delay(600);
  
  
    i = 0;
}

  
void loop() {
  digitalWrite(POLLING_LED, HIGH);
  delay(50);
  Serial.write("$$$");
  while(Serial.available()) { Serial.read(); }
  while(Serial.available() == 0) {};
  delay(250);
  Serial.write("close\r");
  delay(100);
  //Send request to facebook receive response
  Serial.write("open\r");
  while(Serial.available()) { Serial.read(); }
  while(Serial.available() == 0) {};
  delay(1000);
  digitalWrite(POLLING_LED, LOW);
  Serial.write("GET /fql?q=SELECT%20fan_count%20FROM%20page%20WHERE%20username%20=%20%22eetunsw%22 HTTP/1.1\r\nHost: graph.facebook.com\r\nConnection: close\r\n\r\n");
  delay(600);
  startBuffer = 0;
  tmp = 0;
  i = 0;
  start = millis();
  digitalWrite(ASSOC, LOW);
  while(Serial.available()|| (millis() < (start + DELAY_OFFSET))) {
       if(Serial.available()){
      // start = millis(); 
      chartemp = Serial.read();
       if (chartemp == '\r' || chartemp == '\n') {
        tmp++;
       }
       else if (tmp == 4) {
         startBuffer = 1;
         tmp = 0;
       }
       else {
         tmp = 0;
     }
     if (startBuffer) {
        buffer[i] = chartemp;
        i++;
     }
     if (i > RESPONSE_SIZE) break;
       }
       
  }
  digitalWrite(ASSOC, HIGH);
  buffer[26] = '\n';
  fans = atoi(&buffer[22]);
  //Serial.print(fans, DEC);
   
  
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

/*
int get_fan_count(char *packet) {
  int fans_start = strpos(packet_buf, "fan_count", 0) + 11;
  int fans_stop = strpos(packet_buf, "}", fans_start);
  return atoi(substr(packet_buf,fans_start, fans_stop)); 
}*/
