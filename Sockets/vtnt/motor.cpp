#include <stdio.h>
#include <wiringPi.h>

#define	I1	0	// 17
#define	I2	1	// 18

int main (void)
{
  int input;
  wiringPiSetup () ;
  pinMode (I1, OUTPUT) ;
  pinMode (I2, OUTPUT) ;
  digitalWrite (I1, LOW) ;	// Off
  digitalWrite (I2, LOW) ;	// Off
  delay (500) ;		// mS
  printf("\n Horario: 1; Antihorario: 2; Parar: 0\n");

  for (;;)
  {
  	scanf("%d", &input);

  	switch(input)
  	{
  	 case 0:
  	 	printf("\nParando o motor...");
  	 	digitalWrite (I1, LOW) ;	// Off
  		digitalWrite (I2, LOW) ;	// Off
  		delay (500) ;		// mS
  	 break;
  	 case 1:
  	 	printf("\nGirando o motor no sentido horario...");
  	 	digitalWrite (I1, LOW) ;	// Off
  		digitalWrite (I2, LOW) ;	// Off
  		delay (500) ;			// mS
  		digitalWrite (I1, HIGH) ;	// On
  	 break;
  	 case 2:
  	 	printf("\nGirando o motor no sentido antihorario...");
  	 	digitalWrite (I1, LOW) ;	// Off
  		digitalWrite (I2, LOW) ;	// Off
  		delay (500) ;			// mS
  		digitalWrite (I2, HIGH) ;	// On
  	 break;
  	 default:
  	 	printf("\nOpcao errada. Faca de novo!");
  	 
  	 
  	}

  }
  return 0 ;
}
