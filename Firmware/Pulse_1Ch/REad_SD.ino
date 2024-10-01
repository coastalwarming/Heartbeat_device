void readFile(fs::FS & fs, const char * path) {
  File file = fs.open(path);
  if (!file) {
    No_settings_file = true;
    return;
  }
  No_settings_file = false;
  
  char buffer[50];
  memset(buffer, 0, sizeof(buffer));//Sem isto eu via muito lixo no buffer.
  uint8_t i = 0;
  int linhas = 0;
  byte len = 0;
  char  S1[13];
 
  while (file.available())    // note how this also prevents the buffer from overflowing (18 max to leave space for '\0'!)
  {
    buffer[i] = file.read();
    i++;
    if (file.peek() == '\n') {
      linhas++;
      if (linhas > 2)break;
      if (strstr(buffer, "=") > 0) {
         if (strstr(buffer, "Rate_Hz=") > 0) {
          p = strtok(buffer, "=");
          p = strtok(NULL, "=");
          if (p != NULL) {
            Rate_Hz = atoi(p);
            if (Rate_Hz < 5)Rate_Hz = 5; else if (Rate_Hz > 25)Rate_Hz = 25;
          } else {
            Rate_Hz = 10;
          }
        }
      }
      i = 0;
      memset(buffer, 0, sizeof buffer);
    }
  }
  file.close();
}
