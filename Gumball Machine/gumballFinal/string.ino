

int strpos(char *str, char *target, int length) {
  for (int i=length; str[i]!='\0'; i++) {
    if (my_strcmp(str+i, target))
      return i;  
  }
  return -1;
}
int my_strcmp(char *stra, char *strb) {
  for (int i=0; stra[i] != '\0' && strb[i] != '\0'; i++) {
    if (stra[i] != strb[i])
      return false;
  }  
  return true;
}
char* substr(char* str, int start, int stop) { //destories input
  str[stop] = '\0';
  return str+start;
}

