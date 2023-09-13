#define RC_NUM_CHANNELS 1
#define SERIAL_PORT_SPEED 9600
#define RC_CH1  0
#define RC_CH1_INPUT  2
uint16_t RC_VALUES[RC_NUM_CHANNELS];
uint32_t RC_START[RC_NUM_CHANNELS];
volatile uint16_t RC_SHARED[RC_NUM_CHANNELS];
void setup() {
  Serial.begin(SERIAL_PORT_SPEED);
  pinMode(RC_CH1_INPUT, INPUT);
  attachInterrupt(digitalPinToInterrupt(RC_CH1_INPUT), READ_RC1, CHANGE);
}
void READ_RC1() { 
   Read_Input(RC_CH1, RC_CH1_INPUT); 
}
void Read_Input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    RC_START[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - RC_START[channel]);
    RC_SHARED[channel] = rc_compare;
  }
}

void loop() {
  rc_read_values();
Serial.print("CH1=");
Serial.print(RC_VALUES[RC_CH1]); 
Serial.print("\n");
}
void rc_read_values() {
  noInterrupts();
  memcpy(RC_VALUES, (const void *)RC_SHARED, sizeof(RC_SHARED));
  interrupts();
}
