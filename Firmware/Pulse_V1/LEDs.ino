void Blink_Red_LED() {
  while (1) {
    unsigned long currentMillis_1 = millis();
    static int RedledState = LOW;             // ledState used to set the LED

    if (currentMillis_1 - previousMillis_1 >= 1000) {
      previousMillis_1 = currentMillis_1;

      // if the LED is off turn it on and vice-versa:
      if (RedledState == LOW) {
        RedledState = HIGH;
      } else {
        RedledState = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(Red_LED_PIN, RedledState);
    }
  }
}

void Blink_Green_LED() {
  unsigned long currentMillis_2 = millis();
  static int GreenledState = LOW;             // ledState used to set the LED

  if (currentMillis_2 - previousMillis_2 >= 1000) {
    previousMillis_2 = currentMillis_2;

    // if the LED is off turn it on and vice-versa:
    if (GreenledState == LOW) {
      GreenledState = HIGH;
    } else {
      GreenledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(Green_LED_PIN, GreenledState);
  }
}
