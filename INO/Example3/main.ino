
void setup() {
  Serial.begin(115200);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);

}

void loop() {
  analogWrite(3,map(pulseIn(2,HIGH),1100,1900,0,255));
  Serial.println(map(pulseIn(2,HIGH),1100,1900,0,255));
  delay(20);

}
