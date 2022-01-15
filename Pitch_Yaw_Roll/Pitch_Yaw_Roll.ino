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



//void setMotor(dir, speedPin, motorSpeed, dir1Pin, dir2Pin){
//  // this is how you move a single motor with 'Speed' motorSpeed and in direction dir
//
//  // gets input pins and will write to dir1Pin, dir2Pin, speedPin at the end to rotate the motor
//
//}
//
//
//void setPitch(angle, frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor){ // these motors are the knee motors
//  // look at the angle: move frontLeft + frontRight motors in one direction and backLeft + backRight motors in the other using setMotor
//  // there are limits to how much these motors can move and they determine the maximal pitch
//
//  //setMotor used here
//  
//}
//
//void setRoll(angle, frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor){ // these motors are the knee motors
//  // look at the angle: move frontLeft + backRight motors in one direction and frontRight + backRight in the other using setMotor
//  // limits here too 
//
//  //setMotor used here
//}
//
//void setYaw(angle, frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor){ // the motors used here will be the torso to leg ones
//  // look at the angle: all motors are moved but at various speeds depending on how far we want to go
//
//  //setMotor used here
//  
//}
//
//
//void lookHere(x, y, z){ //assuming robot is looking at (0, 0, 0) and looking in x direction before this is run
//
//  // setPitch, setRoll, setYaw are used here
//  // Question: pitch changes z, yaw changes y ? This is probably wrong but not sure how. Can just change x direction by moving the robot 
//
//  // Call setPitch, setYaw, setRoll with corresponding angles
//
//  // conversion between x, y, z and angles 
//  //  => if it's only changing pitch, yaw then this is really easy.
//  
//}




// Actual code starts here


void kinematics (int leg, float x, float y, float z, float roll, float pitch, float yaw) {

    // leg 1  : front left
    // leg 2  : front right
    // leg 3  : back left
    // leg 4  : back right
    
    // moving the foot sideways on the end plane
    float lengthY;
    float hipAngle1a;
    float hipAngle1b;
    float hipAngle1;
    float hipAngle1Degrees;
    float hipHyp;

    // moving the foot forwards or backwardes in the side plane
    float shoulderAngle2;
    float shoulderAngle2Degrees;
    float z2;

    // side plane of individual leg only
    #define shinLength 200     
    #define thighLength 200
    float z3;
    float shoulderAngle1;
    float shoulderAngle1Degrees;
    float shoulderAngle1a;   
    float kneeAngle;  
    float kneeAngleDegrees; 

    // *** ROTATION AXIS

    // roll axis
    #define bodyWidth PLACEHOLDER      // half the distance from the middle of the body to the hip pivot  
    float legDiffRoll;            // difference in height for each leg
    float bodyDiffRoll;           // how much shorter the 'virtual body' gets
    float footDisplacementRoll;   // where the foot actually is
    float footDisplacementAngleRoll; // smaller angle
    float footWholeAngleRoll;     // whole leg angle
    float hipRollAngle;       // angle for hip when roll axis is in use
    float rollAngle;          // angle in RADIANS that the body rolls
    float zz1a;               // hypotenuse of final triangle
    float zz1;                // new height for leg to pass onto the next bit of code
    float yy1;                // new position for leg to move sideways

    // pitch axis

    #define bodyLength PLACEHOLDER      // distance from centre of body to shoulder pivot
    float legDiffPitch;            // differnece in height for each leg
    float bodyDiffPitch;           // how much shorter the 'virtual body' gets
    float footDisplacementPitch;   // where the foot actually is
    float footDisplacementAnglePitch; // smaller angle
    float footWholeAnglePitch;     // whole leg angle
    float shoulderPitchAngle;      // angle for hip when roll axis is in use
    float pitchAngle;              // angle in RADIANS that the body rolls
    float zz2a;                    // hypotenuse of final triangle
    float zz2;                     // new height for the leg to pass onto the next bit of code
    float xx1;                     // new position to move the leg fowwards/backwards
    
    // yaw axis 

    float yawAngle;                 // angle in RADIANs for rotation in yaw
    float existingAngle;            // existing angle of leg from centre
    float radius;                   // radius of leg from centre of robot based on x and y from sticks
    float demandYaw;                // demand yaw postion - existing yaw plus the stick yaw 
    float xx3;                      // new X coordinate based on demand angle 
    float yy3;                      // new Y coordinate based on demand angle

    // ** YAW AXIS **

    // convert degrees to radians for the calcs
    yawAngle = (PI/180) * yaw;

    // put in offsets from robot's parameters so we can work out the radius of the foot from the robot's centre

    // I changed this but I'm not sure I'm right here. I think i am?

    
    if (leg == 1) {         // front left leg
       y = y - bodyWidth; 
       x = x + bodyLength;      
    }
    else if (leg == 2) {    // front right leg
       y = y + bodyWidth;
       x = x + bodyLength; 
    }
    else if (leg == 3) {    // back left leg
       y = y - bodyWidth; 
       x = x - bodyLength;
    }
    else if (leg == 4) {    // back right leg
       y = y + bodyWidth;; 
       x = x - bodyLength;
    }

    //calc existing angle of leg from centre
    existingAngle = atan(y/x);   

    // calc radius from centre
    radius = y/sin(existingAngle);

    //calc demand yaw angle
    demandYaw = existingAngle + yawAngle;

    // calc new X and Y based on demand yaw angle
    xx3 = radius * cos(demandYaw);           // calc new X and Y based on new yaw angle
    yy3 = radius * sin(demandYaw);


    // this just reflects changes from above

    // remove the offsets so we pivot around 0/0 x/y
    if (leg == 1) {         // front left leg
       yy3 = yy3 + bodyWidth; 
       xx3 = xx3 - bodyLength;      
    }
    else if (leg == 2) {    // front right leg
       yy3 = yy3 - bodyWidth;
       xx3 = xx3 - bodyLength; 
    }
    else if (leg == 3) {    // back left leg
       yy3 = yy3 + bodyWidth; 
       xx3 = xx3 + bodyLength;
    }
    else if (leg == 4) {    // back right leg
       yy3 = yy3 - bodyWidth; 
       xx3 = xx3 + bodyLength;
    }

    // ** PITCH AXIS ***   

    if (leg == 1 || leg == 2) {
      pitch = pitch *-1;
      xx3 = xx3*-1;
    }

    // convert pitch to degrees
    pitchAngle = (PI/180) * pitch;

    //calc top triangle sides
    legDiffPitch = sin(pitchAngle) * bodyLength;
    bodyDiffPitch = cos(pitchAngle) * bodyLength;

    // calc actual height from the ground for each side
    legDiffPitch = z - legDiffPitch;

    // calc foot displacement
    footDisplacementPitch = ((bodyDiffPitch - bodyLength)*-1)+xx3;

    //calc smaller displacement angle
    footDisplacementAnglePitch = atan(footDisplacementPitch/legDiffPitch);

    //calc distance from the ground at the displacement angle (the hypotenuse of the final triangle)
    zz2a = legDiffPitch/cos(footDisplacementAnglePitch);

    // calc the whole angle for the leg
    footWholeAnglePitch = footDisplacementAnglePitch + pitchAngle;

    //calc actual leg length - the new Z to pass on
    zz2 = cos(footWholeAnglePitch) * zz2a;

    //calc new Z to pass on
    xx1 = sin(footWholeAnglePitch) * zz2a;  

    if (leg == 1 || leg == 2) {
      xx1 = xx1*-1;
    }

    // *** ROLL AXIS ***

    // convert roll angle to radians
    rollAngle = (PI/180) * roll;    //covert degrees from the stick to radians

    if (leg == 2 || leg == 3) {    // reverse the calcs for each side of the robot
      rollAngle = rollAngle *-1;
       yy3 = yy3*-1;
    }

    // calc the top triangle sides
    legDiffRoll = sin(rollAngle) * bodyWidth;
    bodyDiffRoll = cos(rollAngle) * bodyWidth;
    
    // calc actual height from the ground for each side
    legDiffRoll = zz2 - legDiffRoll;              

    // calc foot displacement
    footDisplacementRoll = ((bodyDiffRoll - bodyWidth)*-1)-yy3;

    //calc smaller displacement angle
    footDisplacementAngleRoll = atan(footDisplacementRoll/legDiffRoll);  

    //calc distance from the ground at the displacement angle (the hypotenuse of the final triangle)
    zz1a = legDiffRoll/cos(footDisplacementAngleRoll);

    // calc the whole angle for the leg
    footWholeAngleRoll = footDisplacementAngleRoll + rollAngle;

    //calc actual leg length - the new Z to pass on
    zz1 = cos(footWholeAngleRoll) * zz1a;

    //calc new Y to pass on
    yy1 = sin(footWholeAngleRoll) * zz1a;

    if (leg == 2 || leg == 3) {   // reverse the calcs for each side of the robot
      yy1 = yy1*-1;
    }


    // *** TRANSLATION AXIS ***

    // calculate the hip joint and new leg length based on how far the robot moves sideways
    hipAngle1 = atan(yy1/zz1);    
    hipAngle1Degrees = ((hipAngle1 * (180/PI)));   // convert to degrees
    z2 = zz1/cos(hipAngle1); // new leg length for next part

    // ****************

    // calculate the shoulder joint offset and new leg length based on how far the foot moves forward/backwards
    shoulderAngle2 = atan(xx1/z2);     // calc how much extra to add to the shoulder joint
    shoulderAngle2Degrees = shoulderAngle2 * (180/PI);
    z3 = z2/cos(shoulderAngle2);     // calc new leg length to feed to the next bit of code below

    // ****************

    // calculate leg length based on shin/thigh length and knee and shoulder angle
    shoulderAngle1 = acos( (sq(thighLength) + sq(z3) - sq(shinLength))/(2*thighLength*z3) ) ; //Law of cosines
    kneeAngle = PI - (shoulderAngle1 *2);       // radians
    // NOTE NEED TO UNDERSTAND KNEE ANGLE I DON'T GET IT RIGHT NOW
    // NOTE NEED TO UNDERSTAND KNEE ANGLE I DON'T GET IT RIGHT NOW
    // NOTE NEED TO UNDERSTAND KNEE ANGLE I DON'T GET IT RIGHT NOW

    

    //calc degrees from angles
    shoulderAngle1Degrees = shoulderAngle1 * (180/PI);    // degrees
    kneeAngleDegrees = kneeAngle * (180/PI);              // degrees  

    



     // write to joints 

     // careful of the data that you pass into the motors (whether its positive or negative)

     // convert data from angles to encoder counts; not entirely sure how this would work because not sure how motors work but assuming its same as previous, would be something like:
     // HERE, come back here for encoderValue and to make sure everything makes sense

     int encoderValue = 2000;
     int angleToEncoder = encoderValue/360;
     

    if (leg == 1) {     // front right
        int shoulderAngle1Counts = (shoulderAngle1Degrees-45) * angleToEncoder; // convert to encoder counts
        int shoulderAngle2Counts = shoulderAngle2Degrees * angleToEncoder; // convert to encoder counts
        int shoulderAngleCounts = shoulderAngle1Counts + shoulderAngle2Counts;
        int kneeAngleCounts = (kneeAngleDegrees-90) * angleToEncoder; // convert to encoder counts 
        int hipAngleCounts = hipAngle1Degrees * angleToEncoder;    // convert to encoder counts       
        driveJoints (60, shoulderAngleCounts);    // front right shoulder
        driveJoints (61, kneeAngleCounts);    // front right knee  
        driveJoints (41, hipAngleCounts);     // front right hip
    }

    else if (leg == 2) {     // front left
        int shoulderAngle1Counts = (shoulderAngle1Degrees-45) * angleToEncoder; // convert to encoder counts
        int shoulderAngle2Counts = shoulderAngle2Degrees * angleToEncoder; // convert to encoder counts
        int shoulderAngleCounts = shoulderAngle1Counts + shoulderAngle2Counts;
        int kneeAngleCounts = (kneeAngleDegrees-90) * angleToEncoder; // convert to encoder counts 
        int hipAngleCounts = hipAngle1Degrees * angleToEncoder;    // convert to encoder counts        
        driveJoints (50, shoulderAngleCounts);    // front left shoulder
        driveJoints (51, kneeAngleCounts);    // front left knee
        driveJoints (40, hipAngleCounts);     // front left hip
    }

    else if (leg == 3) {     // back left
        int shoulderAngle1Counts = (shoulderAngle1Degrees-45) * angleToEncoder; // convert to encoder counts
        int shoulderAngle2Counts = shoulderAngle2Degrees * angleToEncoder; // convert to encoder counts
        int shoulderAngleCounts = shoulderAngle1Counts - shoulderAngle2Counts;
        int kneeAngleCounts = (kneeAngleDegrees-90) * angleToEncoder; // convert to encoder counts 
        int hipAngleCounts = hipAngle1Degrees * angleToEncoder;    // convert to encoder counts        
        driveJoints (30, shoulderAngleCounts);    // back left shoulder
        driveJoints (31, kneeAngleCounts);    // back left knee
        driveJoints (10, hipAngleCounts);     // back left hip
        
    }

    else if (leg == 4) {     // back right
        int shoulderAngle1Counts = (shoulderAngle1Degrees-45) * angleToEncoder; // convert to encoder counts
        int shoulderAngle2Counts = shoulderAngle2Degrees * angleToEncoder; // convert to encoder counts
        int shoulderAngleCounts = shoulderAngle1Counts - shoulderAngle2Counts;
        int kneeAngleCounts = (kneeAngleDegrees-90) * angleToEncoder; // convert to encoder counts 
        int hipAngleCounts = hipAngle1Degrees * angleToEncoder;    // convert to encoder counts        
        driveJoints (20, shoulderAngleCounts);    // back right shoulder
        driveJoints (21, kneeAngleCounts);    // back right knee
        driveJoints (11, hipAngleCounts);     // back right hip
    }





    
}
