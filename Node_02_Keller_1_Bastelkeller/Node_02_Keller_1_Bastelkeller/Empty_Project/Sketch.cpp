/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio


#include <stdint.h>
#include <avr/eeprom.h>
#include "Hausbus.h"
#include "CAN.h"
#include "Pin_ATMEGA328.h"
#include "Taster.h"

uint32_t EEPROM_UID_NODE EEMEM = UID_NODE;
uint32_t EEPROM_UID_KELLER_HUB EEMEM = UID_KELLER_HUB;

uint32_t CAN_Buffer[20];
uint32_t CAN_UID_List[20] = {
			/*	0	*/					ID_02_Keller_1_Bastelkeller_Lichtschalter_ROT,
			/*	1	*/					ID_02_Keller_1_Bastelkeller_Lichtschalter_Gruen,
			/*	2	*/					ID_02_Keller_1_Bastelkeller_Lichtschalter_BLAU,
			/*	3	*/					UID_MASK_ZERO,
			/*	4	*/					UID_MASK_ZERO,
			/*	5	*/					UID_MASK_ZERO,
			/*	6	*/					UID_MASK_ZERO,
			/*	7	*/					UID_MASK_ZERO,
			/*	8	*/					UID_MASK_ZERO,
			/*  9	*/					UID_MASK_ZERO,
			/* 10	*/					UID_MASK_ZERO,
			/* 11	*/					UID_MASK_ZERO,
			/* 12	*/					UID_MASK_ZERO,
			/* 13	*/					UID_MASK_ZERO,
			/* 14	*/					UID_MASK_ZERO,
			/* 15	*/					UID_MASK_ZERO,
			/* 16	*/					UID_MASK_ZERO,
			/* 17	*/					UID_MASK_ZERO,
			/* 18	*/					UID_MASK_ZERO,
			/* 19	*/					UID_MASK_ZERO

};

#define TasterEntprellenMS 300

Pin PinFuerTaster_1('B', 0, true);
Taster Taster_1(PinFuerTaster_1, true);
Pin PinFuerTaster_2('B', 1, true);
Taster Taster_2(PinFuerTaster_2, true);

volatile uint8_t portBhistory = 0xFF;
volatile uint8_t portChistory = 0xFF;
volatile uint8_t portDhistory = 0xFF;

bool CAN_UID_LIST_Complete = false;

bool CAN_Message_detected = false;

void setup() {
    // put your setup code here, to run once:
  int packetSize = 0;
	  Serial.begin(9600);
	  while (!Serial);

	  Serial.println("CAN Node");

	  // start the CAN bus at 500 kbps
	  if (!CAN.begin(500E3)) {
		  Serial.println("Starting CAN failed!");
		  while (1);
	  }
	 
	CAN.filterExtended(CAN_UID_List[0], UID_MASK_ONE);
	Serial.println("Can Filtermaske wurde angewandt");

}

void loop() {
	
			if (Taster_1.StatusAenderung)
			{
				CAN.beginExtendedPacket(ID_01_Keller_1_Bastelkeller_Licht);
				CAN.write(Kommando_Licht_toggle);
				CAN.endPacket();
				Taster_1.StatusAenderung = false;
			}
			if (Taster_2.StatusAenderung)
			{
				CAN.beginExtendedPacket(ID_01_Keller_1_Bastelkeller_Licht);
				CAN.write(Kommando_Licht_aus);
				CAN.endPacket();
				Taster_2.StatusAenderung = false;
			}
	
	// put your main code here, to run repeatedly:
	// try to parse packet
	// Serial.println("Run on loop");
	/*
	int packetSize = CAN.parsePacket();

	if (packetSize) {
		// received a packet
		Serial.print("Received ");

		if (CAN.packetExtended()) {
			Serial.print("extended ");
		}

		if (CAN.packetRtr()) {
			// Remote transmission request, packet contains no data
			Serial.print("RTR ");
		}

		Serial.print("packet with id 0x");
		Serial.println(CAN.packetId(), HEX);
		
		switch(CAN.packetId())
		{
			case  ID_01_Keller_1_Bastelkeller_Licht:
			//Licht schalten
			Serial.println("Licht wird geschaltet");
			switch(CAN.read())
			{
				case Kommando_Licht_an:
				LED_Rot.setze_Status(true);
				Serial.println("Licht wird geschaltet an");
				break;
				case Kommando_Licht_aus:
				LED_Rot.setze_Status(false);
				Serial.println("Licht wird geschaltet aus");
				break;
				case Kommando_Licht_toggle:
				LED_Rot.toggle_Pin();
				Serial.println("Licht wird getoggelt");
				break;
				default:
				Serial.println("Unbekannter Befehl an ID_01_Keller_Licht");
				break;
			}
			break;
			
			default:
			//keine passende ID gefunden
			Serial.println("Keine passende ID im System");
			break;
		}

		if (CAN.packetRtr()) {
			Serial.print(" and requested length ");
			Serial.println(CAN.packetDlc());
			} else {
			Serial.print(" and length ");
			Serial.println(packetSize);

			// only print packet data for non-RTR packets
			while (CAN.available()) {
				Serial.print((char)CAN.read());
			}
			Serial.println();
		}

		Serial.println();
	}*/
}

//Wird aufgerufen wenn ein ungefiltertes CAN Paket empfangen wurde
void onReceive(int packetSize) {
	// received a packet
	Serial.print("Received ");

	if (CAN.packetExtended()) {
		Serial.print("extended ");
	}

	if (CAN.packetRtr()) {
		// Remote transmission request, packet contains no data
		Serial.print("RTR ");
	}

	Serial.print("packet with id 0x");
	Serial.print(CAN.packetId(), HEX);

	if (CAN.packetRtr()) {
		Serial.print(" and requested length ");
		Serial.println(CAN.packetDlc());
		} else {
		Serial.print(" and length ");
		Serial.println(packetSize);

		// only print packet data for non-RTR packets
		while (CAN.available()) {
			Serial.print((char)CAN.read());
		}
		Serial.println();
	}

	Serial.println();
	CAN_Message_detected = true;
}

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
