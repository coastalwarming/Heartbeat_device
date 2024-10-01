void start_rtc() {
  if (!Outrtc.begin()) {
    Outrtc_working = false;
    return;
  } else {
    Set_registers_OUTRTC();
    Outrtc.disableAllInterrupts();
    Outrtc.clearAllInterruptFlags();
    Outrtc.setPeriodicTimeUpdateFrequency(TIME_UPDATE_1_SECOND); 
    Outrtc.enableHardwareInterrupt(CONTROL2_UIE); 
    Inrtc.setTime(Outrtc.getEpoch() );
  }
}

void Set_registers_OUTRTC() {
  Outrtc.writeBit_(0x10, 2, 1);
  Outrtc.writeRegister_(0xC0, 0b00100000);
  Outrtc.set24Hour();
  Outrtc.writeRegister_(0x3F, 0b00010001);
  Outrtc.writeBit_(0x10, 2, 0);
  Outrtc.writeRegister_(0xC0, 0b00100000);
  Outrtc.set24Hour();
}


void Update_Time() {
  static int Prev_second_ = 0;
  if (Outrtc.updateTime()) {
    millisecond = ms_Int_cnt;
    second_ = Outrtc.getSeconds();
    minute_ = Outrtc.getMinutes();
    hour_ = Outrtc.getHours();
    day_ = Outrtc.getDate();
    month_ = Outrtc.getMonth();
    year_ = Outrtc.getYear();
    current_epoch = Outrtc.getEpoch();
  }
}

void IRAM_ATTR RTC_1Hz() {
  portENTER_CRITICAL_ISR(&timerMux);
  ms_Int_cnt = 0;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void config_Timer() {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &msTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);
}

void IRAM_ATTR msTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  ms_Int_cnt++;
  if (ms_Int_cnt >= 1000)ms_Int_cnt = 999;
  portEXIT_CRITICAL_ISR(&timerMux);
}
