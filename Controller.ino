// Controller Code
// Using Bluetooth or Radio control send the commands to the main arduino on board

int VRx = A0;
int VRy = A1;
int SW = 2;
int function = 0;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;
int Button1 = 13;
int Button2 = 12;
int Button3 = 11;
int Button4 = 10;
void setup() {
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);
  pinMode(Button4, INPUT);
  Serial.begin(38400); // Default communication rate of the Bluetooth module

}

int runit = 0;

void loop() {
  // Digital Read from joysticks/buttons
  digi
  if (Serial.available()) {
    runit = Serial.read();
  }
  while (runit = 1) {
    xPosition = analogRead(VRx);
    yPosition = analogRead(VRy);
    SW_state = digitalRead(SW);
    mapX = map(xPosition, 0, 1023, -512, 512);
    mapY = map(yPosition, 0, 1023, -512, 512);
    //If y is -ve, dog moves backward
    //dog moves side to side with x
    //Map the xPosition distance to be moved for one step

    while (function == 0) { 
      if (digitalRead(button1)) { //Walk
        function = 1;
      }
      if (digitalRead(button2)) { //Roll
        function = 2;
      }
      if (digitalRead(button3)) { //Turn(Yaw)
        function = 3;
      }
      if (digitalRead(button4)) { //Pitch
        function = 4;
      }
    }
    
    Serial.write(String(function) + "," + String(mapX) + "," + String(mapY));
    // Output to Serial
    runit = 0;
    function = 0;
    delay(50);
  }
}
