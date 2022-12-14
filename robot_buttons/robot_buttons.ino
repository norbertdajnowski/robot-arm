#include <Braccio.h>
#include <Servo.h>
#include <ezButton.h>

const int BUTTON_NUM = 3;

const int BUTTON_1_PIN = 2;
const int BUTTON_2_PIN = 3;
const int BUTTON_3_PIN = 4;

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

ezButton buttonArray[] = {
	ezButton(BUTTON_1_PIN), 
	ezButton(BUTTON_2_PIN), 
	ezButton(BUTTON_3_PIN)
};

void simple(){
  //(step delay, M1, M2, M3, M4, M5, M6);
  Serial.print("test 1");
  Braccio.ServoMovement(20, 0,  15, 180, 170, 0,  73);  

  //Wait 1 second
  delay(1000);

  Braccio.ServoMovement(20, 180,  165, 0, 0, 180,  10);  

  //Wait 1 second
  delay(1000);
}

void right_angle(){
  Serial.print("test 2");
  Braccio.ServoMovement(20, 90, 90, 90, 90, 90,  73); 
}

void sponge (){
  Serial.print("test 3");
  //(step delay  M1 , M2 , M3 , M4 , M5 , M6);
  Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);
  
  //Wait 1 second
  delay(1000);

  //The braccio moves to the sponge. Only the M2 servo will moves
  Braccio.ServoMovement(20,           0,  90, 180, 180,  90,   10);

  //Close the gripper to take the sponge. Only the M6 servo will moves
  Braccio.ServoMovement(10,           0,  90, 180, 180,  90,  60 );

  //Brings the sponge upwards.
  Braccio.ServoMovement(20,         0,   45, 180,  45,  0, 60);

  //Show the sponge. Only the M1 servo will moves
  Braccio.ServoMovement(20,         180,  45, 180,   45,   0,  60);

  //Return to the start position.
  Braccio.ServoMovement(20,         0,   90, 180,  180,  90, 60);

  //Open the gripper
  Braccio.ServoMovement(20,         0,   90, 180,  180,  90, 10 );
}

void setup() {
	Serial.begin(9600);
  Braccio.begin();

	for(byte i = 0; i < BUTTON_NUM; i++){
		buttonArray[i].setDebounceTime(50); // set debounce time to 50 milliseconds
	}
}

void loop() {
	for(byte i = 0; i < BUTTON_NUM; i++)
		buttonArray[i].loop(); // MUST call the loop() function first
    
	for(byte i = 0; i < BUTTON_NUM; i++) {
		if(buttonArray[i].isPressed()) {
			if (i == 0) {
        simple();
      }
      else if (i == 1) {
        right_angle();
      }
      else if (i == 2) {
        sponge();
      }
		}
	}
}