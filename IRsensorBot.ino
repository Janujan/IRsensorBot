/* Infrared Sensing Bot 
   Author: Janujan Selvaratnam
   
   This robot uses the parallax boe-bot shield and parts along with the 
   arduino to create a mobile robot that avoids collisions based on infrared
   sensors data.
   
   Credits: Parallax Boe-bot Shield Tutorials
*/

#include <Servo.h>

Servo servoRight;
Servo servoLeft;
int left = 13;
int right = 12;

void setup( )
{

	tone(4, 3000, 1000); //beginning the sketch

	//Inputs 
	pinMode(10, INPUT);		//Left IR Reciever
	pinMode(3, INPUT);	    //Right IR Reciever

	//Outputs
	pinMode(9, OUTPUT);	 	//Left IR Transmitter
	pinMode(2, OUTPUT); 	//Right IR Transmitter
	pinMode(11, OUTPUT); 	//Left LED For Response
	pinMode(right, OUTPUT);	//Left Servo
	pinMode(left, OUTPUT);	//Right Servo

	Serial.begin(9600);
	servoRight.attach(right);
	servoLeft.attach(left);
  
}



void loop( )
{
	//start flashing the IRLED
	int irLeft = irDetect(9, 10, 38000);	
	int irRight = irDetect(2, 3, 38000);


	Serial.print(irLeft);
    Serial.print(" ");
    Serial.println(irRight);
	

	/*Flash LED if object is detected
	Note: There seems to be a fair amount of static as LED
	toggles on and off frequently with no object in sight
	*/

	if(irLeft == 0 && irRight == 0)
	{
		backUpLeft( );

	}


	else if(irLeft == 0)
	{
		//digitalWrite(11, HIGH);
		backUpRight( );

	}

	else if( irRight == 0)
	{
		backUpLeft( );
	}

	else{ 

		//digitalWrite(11, LOW); 
		Move(500, 1);
	}
	delay(10);
	


  
}


/*Purpose:
	Flash the specified LED and detect whether this any disturbance in front
	of the device
	LEDpin: the led transmitting the signal
	RECpin: the Reciever pin 
	frequency: rate to flash the LED (usually 38000 Hz)
*/
int irDetect( int LEDpin, int RECpin, long frequency )
{
	tone(LEDpin, frequency, 8);		//Roughly flashes for about a millisecond
	delay(1);						//Wait for the millisecond

	int irVal = digitalRead(RECpin);	//Store the value of the reciever
	delay(1);							//wait again for downtime
	return irVal;

}

void Move(int time, int movement)
{
	switch(movement)
	{
		case 1:										//forward
			servoRight.writeMicroseconds(1400);
			servoLeft.writeMicroseconds(1600);
			delay(time);
			break;

		case 2:										//backward
			servoRight.writeMicroseconds(1600);
			servoLeft.writeMicroseconds(1400);
			delay(time);
			break;

		case 3:										//right
			servoRight.writeMicroseconds(1300);
			servoLeft.writeMicroseconds(1500);
			delay(time);
			break;

		case 4:										//left
			servoRight.writeMicroseconds(1500);
			servoLeft.writeMicroseconds(1700);
			delay(time);
			break;
		case 5:										//stop
			servoRight.writeMicroseconds(1500);
			servoLeft.writeMicroseconds(1500);
			delay(time);			

	}


}

void backUpRight( )
{
	Move(250, 5);
	Move(1000, 2);
	Move(1000, 3);
	Move(1000, 1);
}

void backUpLeft( )
{
	Move(250, 5);
	Move(1000, 2);
	Move(1000, 4);
	Move(1000, 1);	
}

