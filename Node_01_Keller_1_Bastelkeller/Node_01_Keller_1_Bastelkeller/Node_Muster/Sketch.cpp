/*ToDO:
uint32_t SetzeIDZusammen(uint8_t *CAN_Array) scheint die ID nicht korrekt zusammenzusetzten. Beheben!
31.3.2019 scheint behoben zu sein. Wurde ausprobiert. Das Buffer Array buffer[]
uint8_t buffer[] = {0xAB, 0xCD, 0xEF, 0x89};
wird zu ABCDEF89 zusammengeführt. Wurde per CodeBlocks ausprobiert
*/

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
//UID Keller Node Bastelkeller	0b 001 001 001 011 0 0000 00000000 0 
//UID Keller HUB				0b 001 001 000 000 0 0000 00000000 0

uint32_t EEPROM_UID_NODE EEMEM = UID_NODE;
uint32_t EEPROM_UID_KELLER_HUB EEMEM = UID_KELLER_HUB;

uint32_t CAN_Buffer[20];
uint32_t CAN_UID_List[20] = {
	/*	0	*/					ID_01_Keller_1_Bastelkeller_Licht_ROT,
	/*	1	*/					ID_01_Keller_1_Bastelkeller_Licht_GRUEN,
	/*	2	*/					ID_01_Keller_1_Bastelkeller_Licht_BLAU,
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
bool CAN_UID_LIST_Complete = false;

bool CAN_Message_detected = false;

Pin LED_Rot('D', 5, false);
Pin LED_Gruen('D', 6, false);
Pin LED_Blau('D', 7, false);


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

	LED_Rot.setze_Status(false);
	LED_Gruen.setze_Status(false);
	LED_Blau.setze_Status(false);			
	Serial.println("LEds wurden gesetzt");
}



void loop() {
 // put your main code here, to run repeatedly:
	// try to parse packet
	// Serial.println("Run on loop");
	
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
			case  ID_01_Keller_1_Bastelkeller_Licht_ROT:
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
	}
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
