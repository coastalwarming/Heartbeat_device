/*Libraries*/
//SD
#include <Wire.h>//IIC access to rtc.
#include <SPI.h>//SPI access to SD card.
#include <SD.h>//Communication to SD card.
#include <FS.h>//Filesystem access to SD card.
File file;

//TIMER + RTC
#include <SparkFun_RV3032.h>
#include <ESP32Time.h>
/**/

/**Global variables:*/
//SD:
char *p;
char File_name[35];
bool No_SD = true, No_settings_file = true;
//Timing:
int Rate_Hz = 20;
int delay_ = 50;
unsigned long Last_measure = 0;
volatile int ms_Int_cnt;
int year_ = 0, month_ = 0, day_ = 0, hour_ = 0, minute_ = 0, second_ = 0;
volatile int millisecond = 0;
volatile int adc_reading = 0;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

//TIMER + RTC
//#define rtc_adjust//Uncomment to adjust time!!!
ESP32Time Inrtc;
RV3032 Outrtc;
volatile bool Outrtc_working = false;
unsigned long current_epoch = 0;
hw_timer_t * timer = NULL;
void IRAM_ATTR RTC_1Hz();
void IRAM_ATTR msTimer();

//
void setup() {

  //Adjust RTC:
#ifdef rtc_adjust
  Adjust_rtc_to_compile_time();
#endif
  //

  //MicroSD:
  start_sd();
  //

  if (!No_SD) {
    readFile(SD, "/Pulse_settings.txt");
    delay_ = 1000 / Rate_Hz;
  } else delay_ = 50;

  if (!No_settings_file)delay_ = 50;

  //RTC 1Hz interrupt:
  pinMode(14, INPUT);
  attachInterrupt(14, RTC_1Hz, FALLING);//RISING, FALLING,CHANGE, LOW .
  config_Timer();

  //RTC
  Wire.begin();
  start_rtc();
  //

  Update_Time();

}

void loop() {
  Read_and_store_samples();
}
