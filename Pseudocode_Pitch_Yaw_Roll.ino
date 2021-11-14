//// speed
//int speedPin;
//int mSpeed;
//
//// directions need to be opposite of each other 
//int dir1;
//int dir2;
//int dir; //direction we want it to be run
//
//// inputs from encoder (When ENCA rises before ENCB => CCW)
//int ENCA;
//int ENCB;
//
//// gives the current position based on inputs from encoder
//int pos; 


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
//
//
//// takes encoder and writes into position to tell current position 
//void readEncoder(){ 
//  int b = digitalRead(ENCB);
//  if (b > 0){ // if CW
//    pos++;
//  }
//  else{ // if CCW
//    pos--;
//  }
//}



void setMotor(dir, speedPin, motorSpeed, dir1Pin, dir2Pin){
  // this is how you move a single motor with 'Speed' motorSpeed and in direction dir

  // gets input pins and will write to dir1Pin, dir2Pin, speedPin at the end to rotate the motor

}

// ideas for how to do pitch, yaw, roll:
// PITCH: tilt forward/backward legs
// YAW: Use motor that connects body to leg (that motor
// ROLL: tilt left 2/right 2 legs

void setPitch(angle, frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor){ // these motors are the knee motors
  // look at the angle: move frontLeft + frontRight motors in one direction and backLeft + backRight motors in the other using setMotor
  // there are limits to how much these motors can move and they determine the maximal pitch

  //setMotor used here
  
}

void setRoll(angle, frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor){ // these motors are the knee motors
  // look at the angle: move frontLeft + backRight motors in one direction and frontRight + backRight in the other using setMotor
  // limits here too 

  //setMotor used here
}

void setYaw(angle, frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor){ // the motors used here will be the torso to leg ones
  // look at the angle: all motors are moved but at various speeds depending on how far we want to go

  //setMotor used here
  
}


void lookHere(x, y, z){ //assuming robot is looking at (0, 0, 0) and looking in x direction before this is run

  // setPitch, setRoll, setYaw are used here
  // Question: pitch changes z, yaw changes y ? This is probably wrong but not sure how. Can just change x direction by moving the robot 

  // Call setPitch, setYaw, setRoll with corresponding angles

  // conversion between x, y, z and angles 
  //  => if it's only changing pitch, yaw then this is really easy.
  
}
