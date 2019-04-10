/* 
* Taster.cpp
*
* Created: 09.04.2019 11:33:54
* Author: Bastian Reul
Version
*/


#include "Taster.h"
#include <avr/interrupt.h>

/*Um einen Taster im Quellcode verwenden zu können, muss er:
- in der main.cpp global definiert sein (nicht in der main(){ ---} Routine
- Vorher muss ebenfalls global ein Pin deklariert worden sein, welcher dann dem Taster bei seiner Deklaration übergeben wird.
- Da ein Interruptvektor (bspw. PCINT0_vect) immer für einen gesammten Port zuständig ist, muss jede Änderung abgespeichert werden, damit über einen Vergleich erkannt werden 
	kann, welcher Pin (bspw. B0-B6) sich geändert hat. Hierfür muss es eine globale Variable für jeden verwendeten Schalterport geben:
	volatile uint8_t portBhistory = 0xFF;
	volatile uint8_t portChistory = 0xFF;
	volatile uint8_t portDhistory = 0xFF;
	
Dann kann unter der main(){----} Routine der Taster mit Interrupt Routinen verwendet werden. Wenn zum Beispiel garkeine Taster an Port C und D verwendet werden, reicht es
	natürlich, nur die  ISR (PCINT0_vect) { ---------} zu verwenden.
ISR (PCINT0_vect)  // PCINT0_vect ist zuständig für Interrupts an den Pins B0-B7
{
	uint8_t changedbits;
	changedbits = PINB ^ portBhistory;
	portBhistory = PINB;
	
	if (changedbits & (1 << PINB0))
	{	//Interrupt an Pin B0 erkannt
		
	}
	if (changedbits & (1 << PINB1))
	{	//Interrupt an Pin B1 erkannt
		
	}
	if (changedbits & (1 << PINB2))
	{	//Interrupt an Pin B2 erkannt
		
	}
	if (changedbits & (1 << PINB3))
	{	//Interrupt an Pin B3 erkannt
		
	}
	if (changedbits & (1 << PINB4))
	{	//Interrupt an Pin B4 erkannt
		
	}
	if (changedbits & (1 << PINB5))
	{	//Interrupt an Pin B6 erkannt
		
	}
	if (changedbits & (1 << PINB6))
	{	//Interrupt an Pin B6 erkannt
		
	}
	if (changedbits & (1 << PINB7))
	{	//Interrupt an Pin B7 erkannt
		
	}
}

ISR (PCINT1_vect)  // PCINT1_vect ist zuständig für Interrupts an den Pins C0-C7
{
	uint8_t changedbits;
	changedbits = PINC ^ portChistory;
	portChistory = PINC;
	
	if (changedbits & (1 << PINC0))
	{	//Interrupt an Pin C0 erkannt
		
	}
	if (changedbits & (1 << PINC1))
	{	//Interrupt an Pin C1 erkannt
		
	}
	if (changedbits & (1 << PINC2))
	{	//Interrupt an Pin C2 erkannt
		
	}
	if (changedbits & (1 << PINC3))
	{	//Interrupt an Pin C3 erkannt
		
	}
	if (changedbits & (1 << PINC4))
	{	//Interrupt an Pin C4 erkannt
		
	}
	if (changedbits & (1 << PINC5))
	{	//Interrupt an Pin C6 erkannt
		
	}
	if (changedbits & (1 << PINC6))
	{	//Interrupt an Pin C6 erkannt
		
	}
}

ISR (PCINT2_vect)  // PCINT0_vect ist zuständig für Interrupts an den Pins D0-D7
{
	uint8_t changedbits;
	changedbits = PIND ^ portDhistory;
	portDhistory = PIND;
	
	if (changedbits & (1 << PIND0))
	{	//Interrupt an Pin D0 erkannt
		
	}
	if (changedbits & (1 << PIND1))
	{	//Interrupt an Pin D1 erkannt
		
	}
	if (changedbits & (1 << PIND2))
	{	//Interrupt an Pin D2 erkannt
		
	}
	if (changedbits & (1 << PIND3))
	{	//Interrupt an Pin D3 erkannt
		
	}
	if (changedbits & (1 << PIND4))
	{	//Interrupt an Pin D4 erkannt
		
	}
	if (changedbits & (1 << PIND5))
	{	//Interrupt an Pin D6 erkannt
		
	}
	if (changedbits & (1 << PIND6))
	{	//Interrupt an Pin D6 erkannt
		
	}
	if (changedbits & (1 << PIND7))
	{	//Interrupt an Pin D7 erkannt
		
	}
}

Benutzen von Tastern:
main.cpp:
...
#define TasterEntprellenMS 300

Pin LED_Rot('D', 5, false);
Pin LED_Gruen('D', 6, false);
Pin LED_Blau('D', 7, false);

Pin PinFuerTaster_1('B', 0, true);
Taster Taster_1(PinFuerTaster_1, true);
Pin PinFuerTaster_2('B', 1, true);
Taster Taster_2(PinFuerTaster_2, true);

volatile uint8_t portBhistory = 0xFF;
volatile uint8_t portChistory = 0xFF;
volatile uint8_t portDhistory = 0xFF;
...

main()
{
	...
		LED_Rot.setze_Status(false);
		LED_Gruen.setze_Status(false);
		LED_Blau.setze_Status(false);
	...
	while(true)
	{
		if (Taster_1.StatusAenderung)
		{
			LED_Rot.toggle_Pin();
			Taster_1.StatusAenderung = false;
		}
		if (Taster_2.StatusAenderung)
		{
			LED_Gruen.toggle_Pin();
			Taster_2.StatusAenderung = false;
		}	
	}
	...
} // ende main()

ISR (PCINT0_vect)  // PCINT0_vect ist zuständig für Interrupts an den Pins B0-B7
{
	cli();
	uint8_t changedbits;
	changedbits = PINB ^ portBhistory;
	portBhistory = PINB;
	
	if (changedbits & (1 << PINB0))
	{	//Interrupt an Pin B0 erkannt
		Taster_1.StatusAenderung = true;
	}
	if (changedbits & (1 << PINB1))
	{	//Interrupt an Pin B1 erkannt
		Taster_2.StatusAenderung = true;
	}
	if (changedbits & (1 << PINB2))
	{	//Interrupt an Pin B2 erkannt
		
	}
	if (changedbits & (1 << PINB3))
	{	//Interrupt an Pin B3 erkannt
		
	}
	if (changedbits & (1 << PINB4))
	{	//Interrupt an Pin B4 erkannt
		
	}
	if (changedbits & (1 << PINB5))
	{	//Interrupt an Pin B6 erkannt
		
	}
	if (changedbits & (1 << PINB6))
	{	//Interrupt an Pin B6 erkannt
		
	}
	if (changedbits & (1 << PINB7))
	{	//Interrupt an Pin B7 erkannt
		
	}
	//delay(TasterEntprellenMS);
	_delay_ms(TasterEntprellenMS);
	sei();
}

*/


// default constructor
Taster::Taster()
{
} //Taster

Taster::Taster(Pin TasterPin, bool PullUp)
{
	TasterPin.PullUpSchalten(PullUp);
	switch(TasterPin.lese_Port()) //Im Pin Change Interrupt Controll Register (PCICR) muss die dem Port entsprechende Maske freigeschaltet werden
	{
		case 'B':								//			|	7 Bit	|	6 Bit	|	5 Bit	|	4 Bit	|	3 Bit	|	2 Bit	|	1 Bit	|	0 Bit	| 
			PCICR |= (1 << PCIE0);				//	PCICR	|	------	|	------	|	------	|	------	|	------	|	PCIE2	|	PCIE1	|	PCIE0	|
			switch(TasterPin.lese_PinNummer())	//ATMEGA328p	Maske für Port:												  D		|	  C		|	  B
			{
				case 0:	PCMSK0 |= (1 << PCINT0);
					break;
				case 1: PCMSK0 |= (1 << PCINT1);	//In dem jeweiligen Masken werden dann die Pins ausgesucht, die für den Interrupt verwendet werden sollen
					break;							//			|	7 Bit	|	6 Bit	|	5 Bit	|	4 Bit	|	3 Bit	|	2 Bit	|	1 Bit	|	0 Bit	|
				case 2:	PCMSK0 |= (1 << PCINT2);	//	PCMSK0	|	PCINT7	|	PCINT6	|	PCINT5	|	PCINT4	|	PCINT3	|	PCINT2	|	PCINT1	|	PCINT0	|
					break;							//ATMEGA328p|   Pin B7	|   Pin B6	|   Pin B5	|   Pin B5	|   Pin B3	|   Pin B2	|   Pin B1	|   Pin B0	|
				case 3: PCMSK0 |= (1 << PCINT3);
					break;
				case 4:	PCMSK0 |= (1 << PCINT4);
					break;
				case 5: PCMSK0 |= (1 << PCINT5);
					break;
				case 6:	PCMSK0 |= (1 << PCINT6);
					break;
				case 7: PCMSK0 |= (1 << PCINT7);
					break;
				default:
					break;
			}
			break;
		case 'C':								//			|	7 Bit	|	6 Bit	|	5 Bit	|	4 Bit	|	3 Bit	|	2 Bit	|	1 Bit	|	0 Bit	|
			PCICR |= (1 << PCIE1);				//	PCICR	|	------	|	------	|	------	|	------	|	------	|	PCIE2	|	PCIE1	|	PCIE0	|
			switch(TasterPin.lese_PinNummer())	
			{
				case 0:	PCMSK1 |= (1 << PCINT8);
					break;
				case 1: PCMSK1 |= (1 << PCINT9);	//In dem jeweiligen Masken werden dann die Pins ausgesucht, die für den Interrupt verwendet werden sollen
					break;							//			|	7 Bit	|	6 Bit	|	5 Bit	|	4 Bit	|	3 Bit	|	2 Bit	|	1 Bit	|	0 Bit	|
				case 2:	PCMSK1 |= (1 << PCINT10);	//	PCMSK1	|	------	|	PCINT14	|	PCINT13	|	PCINT12	|	PCINT11	|	PCINT10	|	PCINT9	|	PCINT8	|
					break;							//ATMEGA328p|   ------	|   Pin C6	|   Pin C5	|   Pin C5	|   Pin C3	|   Pin C2	|   Pin C1	|   Pin C0	|
				case 3: PCMSK1 |= (1 << PCINT11);
					break;
				case 4:	PCMSK1 |= (1 << PCINT12);
					break;
				case 5: PCMSK1 |= (1 << PCINT13);
					break;
				case 6:	PCMSK1 |= (1 << PCINT14);
					break;
					// Pin C7 gibt es beim ATMEGA328 nicht
				default:
				break;
			}	
			break;	
		case 'D':								//			|	7 Bit	|	6 Bit	|	5 Bit	|	4 Bit	|	3 Bit	|	2 Bit	|	1 Bit	|	0 Bit	|
			PCICR |= (1 << PCIE2);				//	PCICR	|	------	|	------	|	------	|	------	|	------	|	PCIE2	|	PCIE1	|	PCIE0	|
			switch(TasterPin.lese_PinNummer())
			{
				case 0:	PCMSK2 |= (1 << PCINT16);
					break;
				case 1: PCMSK2 |= (1 << PCINT17);	//In dem jeweiligen Masken werden dann die Pins ausgesucht, die für den Interrupt verwendet werden sollen
					break;							//			|	7 Bit	|	6 Bit	|	5 Bit	|	4 Bit	|	3 Bit	|	2 Bit	|	1 Bit	|	0 Bit	|
				case 2:	PCMSK2 |= (1 << PCINT18);	//	PCMSK2	|	PCINT23	|	PCINT22	|	PCINT21	|	PCINT20	|	PCINT19	|	PCINT18	|	PCINT17	|	PCINT16	|
					break;							//ATMEGA328p|   Pin D7	|   Pin D6	|   Pin D5	|   Pin D5	|   Pin D3	|   Pin D2	|   Pin D1	|   Pin D0	|
				case 3: PCMSK2 |= (1 << PCINT19);
					break;
				case 4:	PCMSK2 |= (1 << PCINT20);
					break;
				case 5: PCMSK2 |= (1 << PCINT21);
					break;
				case 6:	PCMSK2 |= (1 << PCINT22);
					break;
				case 7: PCMSK2 |= (1 << PCINT23);
					break;
				default:
					break;
			}
		break;
		default:
			break;
	}
	sei();
	
}

// default destructor
Taster::~Taster()
{
} //~Taster
