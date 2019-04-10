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

uint32_t EEPROM_UID_NODE EEMEM = UID_NODE;
uint32_t EEPROM_UID_KELLER_HUB EEMEM = UID_KELLER_HUB;

uint32_t CAN_Buffer[20];
uint32_t CAN_UID_List[20];
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
	  Serial.println("Can Nachricht wird gesendet");
	  CAN.filterExtended(UID_KELLER_HUB, UID_MASK_ZERO);
	  CAN.beginExtendedPacket(UID_NODE);
	  CAN.write(Kommando_Get_HUB_ID);
	  CAN.endPacket();
	  Serial.println("Can Nachricht wurde gesendet");
	  while(CAN.parsePacket() == 0)
	  {
		  //Endlosschleife bis die UID vom HUB empfangen wurde
	  }
	  if (CAN.packetId() == UID_KELLER_HUB)
	  {
		  if (CAN.read() == UID_KELLER_HUB)
		  {	//Es bleibt bei der alten Keller HUB ID
			  Serial.println("Es bleibt bei der alten Keller HUB ID");
		  } 
		  else
		  {
			  //es wurde eine neue HUB ID empfangen
		  }
	  } 
	  else //Das empfangene Packet hat eine nicht erwartete ID
	  {
		  Serial.println("Das Paket hat eine falsche ID");
	  }
	  CAN_Message_detected = false;
	  while (CAN.parsePacket() != 0)
	  {
		  CAN.read();
		  Serial.println("Dummy Nachricht weglesen");
	  }
	  
	  //Eine Liste der IDs vom HUB anfordern, auf die gelauscht werden soll
	  CAN.beginExtendedPacket(UID_NODE);
	  CAN.write(Kommando_Get_ID_LIST_FROM_HUB);
	  CAN.endPacket();
	  
	  Serial.println("Die Liste aller zu belauschenden IDs");
	  //_delay_ms(1000);
		uint8_t buffer[4];
		uint8_t ID_List_numerator = 0;
		uint32_t ID = 0;
		uint32_t temp = 0;
		while((CAN_UID_LIST_Complete == false) && (ID_List_numerator < ID_LIST_MAXIMUM))
		{
				while(CAN.parsePacket() == 0)
				{
					//Endlosschleife bis die UID vom HUB empfangen wurde
				}					
				CAN.readBytes(buffer, 4);

						//uint32_t *Zeiger_auf_ID = &ID;
						//Serial.println(ID_Zusammensetzen(buffer), BIN);
						//Zeiger_auf_ID = ID_Zusammensetzen(buffer, Zeiger_auf_ID);
						//Serial.println(Zeiger_auf_ID, BIN);
			/*	for (int i=0; i<4; i++)
				{
					temp = buffer[i];
					ID = ID + (temp << (8*(3-i)));
				}
				buffer[0] = 0;
				buffer[1] = 0;
				buffer[2] = 0;
				buffer[3] = 0;
				*/
				ID = ID_Zusammensetzen(buffer);
				//ID_Ausgeben(ID);
				//Serial.println("ID fertig");
				if (ID == 0) //Falls in der CAN Nachricht eine 0x0000 steht, zeigt das an, dass die UID Liste komplett übertragen wurde
				{
					CAN_UID_LIST_Complete = true;
					Serial.println("Uebertragung der UID Liste beendet");
				}
				else
				{
					CAN_UID_List[ID_List_numerator] = ID;
					ID_List_numerator++;
				}
				ID = 0;
			
		}
				//Testausgaben aller UIDs
				for (int i=0; i<=ID_List_numerator; i++)
				{
					Serial.print("Ausgabe Arduino: ");
					Serial.println(CAN_UID_List[i], BIN);
					Serial.print("Ausgabe eigene Funktion: ");
					ID_Ausgeben(CAN_UID_List[i]);
					Serial.println(" ");
				}
				Serial.print("Es wurden insgesammt ");
				Serial.print(ID_List_numerator);
				Serial.print(" IDs uebertragen. ");
				Serial.println();
				
				
	//Nachdem alle zu belauschenden IDs empfangen wurde, wird die Maske berechnet und auf den CAN Controller angewandt
	//ID_Maske_berechnen(CAN_UID_List);
	Serial.println("Can Maske wird berechnet");
	uint32_t Maske = ID_Maske_berechnen(CAN_UID_List, 2);
	Serial.print("Maske: ");
	Serial.println(Maske, BIN);
	//CAN.filterExtended(ID_Maske_berechnen(CAN_UID_List, 2), UID_MASK_ONE);
	CAN.filterExtended(CAN_UID_List[1], UID_MASK_ONE);
	Serial.println("Can Filtermaske wurde angewandt");
	LED_Rot.setze_Status(false);
	LED_Gruen.setze_Status(false);
	LED_Blau.setze_Status(true);			
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
