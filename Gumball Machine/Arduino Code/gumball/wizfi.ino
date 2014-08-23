#define OKAY_1 "[OK]\r\n\n\r\n"
#define OKAY_2 "[OK]\r\n"
#define OKAY_3 "0"

boolean wifi_conn = false;
char tcp_conn = false;
char cid = -1;

boolean wizfi_conn() {
  return wifi_conn;  
}

boolean wizfi_cmd(char* cmd, char* expected_res) {
  Serial.println(cmd);
  //delay(10);
  //return false;
  return Serial.find(expected_res);
}

void wizfi_connect(char *ssid, char *pass) {
  char cmd1[100], cmd2[100];
  String cmd1_s = "AT+WWPA=" + String(pass);
  String cmd2_s = "AT+WA=" + String(ssid);
  cmd1_s.toCharArray(cmd1, 100);
  cmd2_s.toCharArray(cmd2, 100);
  
  wifi_conn = false;
  while (!wifi_conn) { 
    wizfi_cmd("AT&F", OKAY_1); //Factory reset
    wizfi_cmd("ATC0", OKAY_1); //Disable auto connect
    wizfi_cmd("ATE0", OKAY_2); //Disable echo
    wizfi_cmd("ATV0", "0"); //Binary Return Values
    wizfi_cmd("AT+XEHT=1,1,0,1", "0"); //Setup GPIO10
    wizfi_cmd("AT+WD", "0"); //Disassociate
    wizfi_cmd("AT+WAUTH=0", "0"); //No WEP
    wizfi_cmd(cmd1, "0"); //WPA Password
    wizfi_cmd("AT+NDHCP=1", "0"); //DHCP on
    wizfi_cmd("AT+XDUM=0", "0"); //Don't disable UART
    
    //Connect to network
    Serial.setTimeout(20000);
    wifi_conn = wizfi_cmd(cmd2, "IP");
    Serial.setTimeout(1000);
  }  
}

void wizfi_tcp_connect(char *ip) {
  char cmd[100];
  String cmd_s = "AT+NCTCP=" + String(ip);
  cmd_s.toCharArray(cmd, 100);
  
  //Close existing connections
  wizfi_cmd("AT+NCLOSEALL", "0");
  
  //Let things settle..
  delay(100);
  
  Serial.setTimeout(20000);
  cid = -1;
  while (cid == -1) {
    //digitalWrite(13, LOW);
    if ( wizfi_cmd(cmd, "7") ) {
      //digitalWrite(13,HIGH);
      //cid = Serial.parseInt();  //doesnt work!
      cid = 0; // @TODO
      tcp_conn = true;
    }
  }
  Serial.setTimeout(1000); 
}

char* wizfi_sendtcp(char cid, char *packet, char *result, int result_len) {
  char start_cmd[4] = {(char)27, 'S', cid, '\0'};
  char end_cmd[3] = {(char)27, 'E', '\0'};
  char expected[3] = {(char)27, 'O', '\0'};
  
  //Write request
  delay(10); // just for a small delay
  wizfi_cmd(start_cmd, expected);
  Serial.println(packet);
  wizfi_cmd(end_cmd, expected);
  
  //Read response
  Serial.setTimeout(20000);
  Serial.find(start_cmd);
  Serial.readBytesUntil(((char)27), result, result_len);
  
  delay(10);
    
  Serial.flush();
}
