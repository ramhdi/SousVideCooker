int out_a = 2;
int out_b = 3;
int sw = 10;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;

int mode;
const int mode_1 = 0;
const int mode_2 = 1;
const int mode_3 = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(out_a, INPUT_PULLUP);
  pinMode(out_b, INPUT_PULLUP);
  pinMode(sw, INPUT_PULLUP);

  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);

  mode = 0;
}

void loop() {
  switch (mode) {
    case mode_1:
      Serial.println(mode);
      if (!digitalRead(sw)) {
        mode = mode_2;
      }
      break;

    case mode_2:
      Serial.println(mode);
      if (!digitalRead(sw)) {
        mode = mode_3;
      }
      break;

    case mode_3:
      Serial.println(mode);
      if (!digitalRead(sw)) {
        mode = mode_1;
      }
      break;
  }

  Serial.println(encoderValue);
  delay(100);
}

void updateEncoder() {
  int MSB = digitalRead(out_a); //MSB = most significant bit
  int LSB = digitalRead(out_b); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101) encoderValue++;
  if (sum == 0b1110) encoderValue--;

  lastEncoded = encoded; //store this value for next time
}
