void start_sd() {
  if (InitSDCard()) {
    createDir(SD, "/Data");
  } else No_SD = false;
}

bool InitSDCard() {
  if (!SD.begin()) {
    for (int i = 0; i < 5; i++) {
      if (SD.begin())return 1;
    }
    return 0;
  } else return 1;
  return 0;
}


void Create_or_Update_csv_file() {
  if (!No_SD) {
    snprintf_P(File_name, sizeof(File_name), PSTR("/Data/%i%02i%02i_%02i%02i%02i.CSV"),
               year_, month_, day_,  hour_, minute_, second_);
    File file = SD.open(File_name);
    if (!file) {
      writeFile(SD, File_name, "");
    } else {
      char Log_data_S[75] = {};
      snprintf_P(Log_data_S, sizeof(Log_data_S), PSTR("%i-%02i-%02i %02i:%02i:%02i.%03i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i"), year_, month_, day_, hour_, minute_, second_, millisecond, adc_reading);
      appendFile(SD, File_name, Log_data_S);
    }
  }
}


void appendFile(fs::FS & fs, const char * path, char message[]) {
  file.println(message);
  file.close();
}

void writeFile(fs::FS & fs,  char * path, const char * message) { //const char * path
  File file = fs.open(path, FILE_WRITE);
  file = fs.open(path, FILE_WRITE);
  char log_[30] = {};
  char log_2[30] = {};
  memset(log_, 0, sizeof(log_));
  file.println("------------------------------,--------------------");
  file.printf("Pulse");
  file.printf("Rate_Hz,%d\n", Rate_Hz);
  file.println("------------------------------,--------------------");
  file.print("Time,");
  file.close();
}

void createDir(fs::FS & fs, const char * path) {
  if (!fs.mkdir(path))No_SD = true;
}
