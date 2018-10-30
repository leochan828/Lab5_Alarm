#include <stdio.h>
#include <wiringPi.h>
#include "ifttt.h"

void  ALARM_OFF(void);
void  ALARM_ARMING(void);
void  ALARM_ARMED(void);
void  ALARM_TRIGGERED(void);
void ALARM_SOUNDING(void);

int main(int argc, char *argv[])
{
	wiringPiSetup();
	pullUpDnControl(3, PUD_UP) ;
	ALARM_OFF();
	return 0;	
}

void  ALARM_OFF(){
	printf("Alarm Off\n");
	pinMode(1, OUTPUT);
	pinMode(2,OUTPUT);
	pinMode(3, INPUT);
	digitalWrite(1, HIGH); delay(500);
	digitalWrite(2, LOW);
	for(;;){
		if(digitalRead(3) == 0)
		{
			ALARM_ARMING();
			break;
		}
	}

}

void  ALARM_ARMING(){
	int i;
	printf("ALARM ARMING");
	for(i = 0 ; i < 10 ; i++){
		digitalWrite(1, HIGH); delay(500);
		digitalWrite(1, LOW); delay(500);
	}
	digitalWrite(2, HIGH);
	ALARM_ARMED();	
}

void ALARM_ARMED(){
	for(;;)
	{
		if(digitalRead(3) == 0)
		{
			ALARM_OFF();
			break;
		}
		
		if(digitalRead(0) == 0)
		{
			ALARM_TRIGGERED();
			break;
		}
	}
}

void ALARM_TRIGGERED()
{
	int i;
	for(i = 0 ; i < 10 ; i++){
		digitalWrite(1, HIGH); digitalWrite(2, HIGH);
		delay(500);
		digitalWrite(1, LOW); digitalWrite(2, LOW);
		delay(1000);
		if(digitalRead(3) == 0){
			ALARM_OFF();
			break;
		}
	}
	ALARM_SOUNDING();
}

void ALARM_SOUNDING(){
	ifttt("https://maker.ifttt.com/trigger/ALARM_TRIGGERED/with/key/cz4tWjECPNr27EBeIQALXx","my1", "my2", "my3");
	for(;;){	
		digitalWrite(1, HIGH); digitalWrite(2, HIGH); digitalWrite(4, HIGH);
		delay(1000);
		digitalWrite(1, LOW); digitalWrite(2, LOW); digitalWrite(4, LOW);
		delay(1000);
		if(digitalRead(3) == 0){

			break;
		}
	}	
	ALARM_OFF();

}
