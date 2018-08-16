volatile int value = 0;
volatile uint8_t prev = 0;

void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);

  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);

  Serial.begin(9600);
}

void updateEncoder() {
  uint8_t a = digitalRead(2);
  uint8_t b = digitalRead(3);

  uint8_t ab = (a << 1) | b;
  uint8_t encoded = ( prev <<2 ) | ab;

  if(encoded == 0b1101 || encoded == 0b0100 || encoded == 0b0010 || encoded == 0b1011){
    value ++;
  } else if(encoded == 0b1110 || encoded == 0b0111 || encoded == 0b0001 || encoded == 0b1000) {
    value --;
  }

  prev = ab;
}

void loop()
{
   Serial.println(value);
}


