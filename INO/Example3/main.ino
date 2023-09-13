#define RC_NUM_CHANNELS 4
#define SERIAL_PORT_SPEED 115200
#define RC_CH1  0
#define RC_CH1_INPUT  18 // receiver pin 1
uint16_t RC_VALUES[RC_NUM_CHANNELS];
uint32_t RC_START[RC_NUM_CHANNELS];
volatile uint16_t RC_SHARED[RC_NUM_CHANNELS];
void setup() {
  Serial.begin(SERIAL_PORT_SPEED);
  pinMode(RC_CH1_INPUT, INPUT);
  attachInterrupt(digitalPinToInterrupt(RC_CH1_INPUT), READ_RC1, CHANGE);
}

// Thee functions are called by the interrupts. We send them all to the same place to measure the pulse width
void READ_RC1() { 
   Read_Input(RC_CH1, RC_CH1_INPUT); 
}
void READ_RC2() { 
   Read_Input(RC_CH2, RC_CH2_INPUT);
}
void READ_RC3() { 
   Read_Input(RC_CH3, RC_CH3_INPUT); 
}
void READ_RC4() { 
   Read_Input(RC_CH4, RC_CH4_INPUT); 
}
// This function reads the pulse starts and uses the time between rise and fall to set the value for pulse width
void Read_Input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    RC_START[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - RC_START[channel]);
    RC_SHARED[channel] = rc_compare;
  }
}

void loop() {
  
  // read the values from our RC Receiver
  rc_read_values();
Serial.print("CH1=");
Serial.print(RC_VALUES[RC_CH1]); Serial.print(",CH2=");
Serial.print(RC_VALUES[RC_CH2]); Serial.print(",CH3=");
Serial.print(RC_VALUES[RC_CH3]); Serial.print(",CH4=");
Serial.print(RC_VALUES[RC_CH4]);Serial.print("\n");
}

// this function pulls the current values from our pulse arrays for us to use. 
void rc_read_values() {
  noInterrupts();
  memcpy(RC_VALUES, (const void *)RC_SHARED, sizeof(RC_SHARED));
  interrupts();
}
