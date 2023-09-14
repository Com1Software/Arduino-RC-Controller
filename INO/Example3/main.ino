
void setup() {
  Serial.begin(115200);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,INPUT);
  pinMode(7,OUTPUT);

}

void loop() {
  analogWrite(3,map(pulseIn(2,HIGH),1100,1900,0,255));
  Serial.print("CH1=");
  Serial.print(map(pulseIn(2,HIGH),1100,1900,0,255));
  analogWrite(5,map(pulseIn(4,HIGH),1100,1900,0,255));
  Serial.print(",CH2=");
  Serial.print(map(pulseIn(4,HIGH),1100,1900,0,255));
  analogWrite(7,map(pulseIn(6,HIGH),1100,1900,0,255));
  Serial.print(",CH3=");
  Serial.print(map(pulseIn(6,HIGH),1100,1900,0,255));
  Serial.print(",CH4=");
  ;Serial.print("\n");
  delay(20);

}
