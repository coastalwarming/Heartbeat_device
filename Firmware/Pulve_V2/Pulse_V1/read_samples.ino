
void Read_and_store_samples() {
  adc_reading = analogRead(36);
  Update_Time();
  Create_or_Update_csv_file();
  if ((millis() - Last_measure) <= delay_)delay(delay_ - (millis() - Last_measure));
  Last_measure = millis();
}
