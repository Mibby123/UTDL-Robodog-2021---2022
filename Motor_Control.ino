// Code for Motor Control with a specific encoder type
// For Arduino Mega, Mega2560, MegaADK only the following pins can be used for interrupts 2, 3, 18, 19
#define Encoder_measurements 360
#define Encoderchangepin 2
#define Encoderdirectionpin 4

/*
  //These are for all the Encoders that would be needed to be measured
  #define Encoder[] = {<PIN NUMBERS FOR ENCODER TRANSISTORS>};
*/
int Encoder_num = 999;

/*
  int pos[x] //<- x is the number of encoders
  for (int i = 0; i < x; i++) {
    pos[i] = 0;  // set all initial encoder values to 0;
  }
*/

void setup() {
  //Use and Interupt to change the value of pos, whenever there is a change in the motor position
  attachInterrupt(digitalPinToInterrupt(Encoderchangepin), changeEncoder, FALLING); // Interrupt only when the pin is going from HIGH to LOW
}

void setMotor(Motor, Angle, Speed, Encoder_num) {
  while (1) {
    if (Angle > round(determineAngle(pos))) { // pos is assumed to be directly downward when = 0, and ccw motion is positive and cw motion is negative
      digitalWrite(Motor_Direction, HIGH); //Change Direction to Clockwise on a hardware level
      digitalWrite(Encoder[Encoder_num], HIGH); // Choose Encoder to Measure (a series of transistors to determine output) <-- This will allow for only one interrupt to be needed
      analogWrite(Motor, Speed);
    }
    if (Angle < round(determineAngle(pos))) {
      digitalWrite(Motor_Direction, LOW); //Change Direction to Counter-Clockwise on a hardware level
      digitalWrite(Encoder[Encoder_num], HIGH); // Choose Encoder to Measure (a series of transistors to determine output) <-- This will allow for only one interrupt to be needed
      analogWrite(Motor, Speed);
    }
    if (Angle ==  round(determineAngle(pos))) {
      digitalWrite(Encoder[Encoder_num], LOW);
      analogWrite(Motor, 0);
      break;
    }
    delay(10); //Change this value depending on functionality of motor given
    analogWrite(Motor, 0);
  }
}

void changeEncoder() {
  boolean b = digitalRead(Encoderdirectionpin); //Logic needs to be changed depending on the encoder
  if (b == HIGH) {
    pos[Encoder_num]++;
  }
  if (b == LOW) {
    pos[Encoder_num]--;
  }
}

float determineAngle(int pos) {
  if (pos > 0) {
    Angle = pos / Encoder_measurements * 360;
  }
  if (pos < 0) {
    Angle = 360 + pos / Encoder_measurements * 360; // 360 + negative angle
  }
}
