/*
 
*/

#include <Arduino.h> //make sure VSCode understands that this is an arduino sketch
//#include <Joystick.h> //include the Joystick library

//Joystick_ joystick; //create a joystick instance called "joystick"... Pretty inventive, huh...

//define input pins for the pots
int pot_a_pin = A2;
int pot_b_pin = A3;

//define the pins for the buttons
int but1pin = 7;
int but2pin = 8;
int but3pin = 9;
int but4pin = 4;
int but5pin = 5;
int but6pin = 6;

//define variables to hold the state of buttons and value of pots
int pot_a_val_prev = 0;
int pot_a_val_new = 0;
int pot_a_pulse = 0;
int pot_a_pulse_prev = 0;
int pot_a_pulse_new = 0;
byte counter = 0;

byte but1state = 0;
byte but2state = 0;
byte but3state = 0;
byte but4state = 0;
byte but5state = 0;
byte but6state = 0;
byte softbut7state = 0; //"software" button, gets its state from potentiometer a movevement, plus increment
byte softbut8state = 0; //"software" button, gets its state from potentiometer b movevement, minus increment

//bytes to hold the button states to send to joystick library after debounce
byte but1laststate = 0;
byte but2laststate = 0;
byte but3laststate = 0;
byte but4laststate = 0;
byte but5laststate = 0;
byte but6laststate = 0;
byte softbut7laststate = 0; //"software" button, gets its state from potentiometer a movevement, plus increment
byte softbut8laststate = 0; //"software" button, gets its state from potentiometer b movevement, minus increment

//local pots
int pot_a_val = 0;
int pot_b_val= 0;




//if you don't know what "void setup()" does - you probably shouldn't be reading this
void setup() 
{
//joystick.begin();

//set pin modes for the local button pins
pinMode(but1pin, INPUT_PULLUP);
pinMode(but2pin, INPUT_PULLUP);
pinMode(but3pin, INPUT_PULLUP);
pinMode(but4pin, INPUT_PULLUP);
pinMode(but5pin, INPUT_PULLUP);
pinMode(but6pin, INPUT_PULLUP);

Serial.begin(115200); //initialize serial comms for debugging

}

//you should know what "void loop()" does
void loop() 
{

    
  //read pots
  pot_a_val = analogRead(pot_a_pin);
  pot_b_val = map(analogRead(pot_b_pin), 0, 1023, 1023, 0);

  //convert pot a reading into button presses
  pot_a_val_prev = pot_a_val;
  pot_a_pulse = pot_a_val_prev / 140;
  //pot_a_pulse_prev = pot_a_pulse;
  if (pot_a_pulse > pot_a_pulse_prev){softbut7state = 1, softbut8state = 0;}
  else if (pot_a_pulse < pot_a_pulse_prev){softbut8state = 1, softbut7state = 0;}
  
  //read buttons (use the ! to invert the logic because of using PULLUP)
  but1state = !digitalRead(but1pin);
  but2state = !digitalRead(but2pin);
  but3state = !digitalRead(but3pin);
  but4state = !digitalRead(but4pin);
  but5state = !digitalRead(but5pin);
  but6state = !digitalRead(but6pin);
  
  //tell the joystick library where to get the values for the axes
  //joystick.setXAxis(pot_a_val);
  //joystick.setYAxis(pot_b_val);
  
  //tell the joystick library state of buttons
	/*
  if (but1state != but1laststate)
	{
	joystick.setButton(0, but1state);
	but1laststate = but1state;
	}
  if (but2state != but2laststate)
	{
	joystick.setButton(1, but2state);
	but2laststate = but2state;
	}
  if (but3state != but3laststate)
	{
	joystick.setButton(2, but3state);
	but3laststate = but3state;
	}
  if (but4state != but4laststate)
	{
	joystick.setButton(3, but4state);
	but4laststate = but4state;
	}
  if (but5state != but5laststate)
	{
	joystick.setButton(4, but5state);
	but5laststate = but5state;
	}
  if (but6state != but6laststate)
	{
	joystick.setButton(5, but6state);
	but6laststate = but6state;
	}
 */   
delay(5);

//debugging - print remote pot values to screen...
  Serial.print("apot: "); Serial.print(pot_a_val); 
  Serial.print(" bpot: "); Serial.print(pot_b_val); 
//debugging - print button states to screen...
  Serial.print(" b1s: "); Serial.print(but1state);
  Serial.print(" b2s: "); Serial.print(but2state); 
  Serial.print(" b3s: "); Serial.print(but3state);
  Serial.print(" b4s: "); Serial.print(but4state);
  Serial.print(" b5s: "); Serial.print(but5state); 
  Serial.print(" b6s: "); Serial.print(but6state);
  Serial.print(" potapulse: "); Serial.print(pot_a_pulse);
  Serial.print(" softbut7state: "); Serial.print(softbut7state);
  Serial.print(" softbut8state: "); Serial.println(softbut8state);
}