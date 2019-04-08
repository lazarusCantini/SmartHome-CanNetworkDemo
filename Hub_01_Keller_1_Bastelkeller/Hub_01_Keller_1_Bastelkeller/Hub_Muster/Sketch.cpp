/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

#include <stdint.h>
#include <avr/eeprom.h>
#include "Hausbus.h"
#include "CAN.h"

uint32_t EEPROM_UID_KELLER_HUB EEMEM = UID_KELLER_HUB;

uint32_t CAN_Buffer[20];
bool CAN_Message_detected = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);  //VCC für den Can Baustein zur Verfügung stellen
  digitalWrite(4, HIGH);
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Can Hub");
  
  
  if (!CAN.begin(500E3))
  {
	  Serial.println("Starting Can failed.");
	  while (1);
  }
  Serial.println("Es wird auf eine Can Nachricht gewartet...");
  
  //Testweise wird der Filter mal auf den Node eingestellt
  CAN.filterExtended(UID_NODE, UID_MASK_ZERO);
  
  while(CAN.parsePacket() == 0)
  {
	  //Endlosschleife bis eine CAN Nachricht gefunden wurde
  }
  Serial.println("Es wurde eine CAN Nachricht empfangen.");
  if (CAN.available())
  {
	  Serial.println("Can Message wurde empfangen");
	  if ((CAN.packetId()== UID_NODE) && (CAN.read() == Kommando_Get_HUB_ID) )
	  {
		  Serial.println("Es wurde die HUB ID angefordert.");
		  //Die Antwort senden (Aktuell noch Hardgecodete ID zurück senden)
		  CAN.beginExtendedPacket(UID_KELLER_HUB);
		  CAN.write(UID_KELLER_HUB);
		  CAN.endPacket();
	  } 
	  else
	  {
		  Serial.println("Entweder unbekannte ID, oder unbekanntes Kommando.");
	  }
  } 
  else
  {
	Serial.println("Da ist was falsch gelaufen.");  
  }
  
  
  while(CAN.parsePacket() == 0)
  {
	  //Endlosschleife bis eine CAN Nachricht gefunden wurde
  }
  Serial.println("Es wurde eine CAN Nachricht empfangen.");
  if (CAN.available())
  {
	  Serial.println("Can Message wurde empfangen");
	  if ((CAN.packetId()== UID_NODE) && (CAN.read() == Kommando_Get_ID_LIST_FROM_HUB) )
	  {
		  Serial.println("Es wurde die ID Liste auf die gelauscht wird angefordert");
		  //Die Antwort senden (Aktuell noch Hardgecodete ID zurück senden)
		  CAN.beginExtendedPacket(UID_KELLER_HUB);
		  CAN.write(Zeiger_auf_UID_01_Keller_1_Bastelkeller_Lichtschalter, 4);
		  CAN.endPacket();
		  
		  CAN.beginExtendedPacket(UID_KELLER_HUB);
		  CAN.write(Zeiger_auf_UID_01_Keller_1_Bastelkeller_Licht, 4);
		  CAN.endPacket();
		  
		  CAN.beginExtendedPacket(UID_KELLER_HUB);
		  CAN.write(Zeiger_auf_UID_Liste_EndeIndikator, 4);
		  CAN.endPacket();		  
		  
	  }
	  else
	  {
		  Serial.println("Entweder unbekannte ID, oder unbekanntes Kommando.");
	  }
  }
  else
  {
	  Serial.println("Da ist was falsch gelaufen.");
  }


}

void loop() {
  // put your main code here, to run repeatedly:
	_delay_ms(2000);
	  CAN.beginExtendedPacket(ID_01_Keller_1_Bastelkeller_Licht);
	  CAN.write(Kommando_Licht_toggle);
	/*  CAN.write('w');
	  CAN.write('o');
	  CAN.write('r');
	  CAN.write('l');
	  CAN.write('d');*/
	  CAN.endPacket();

	  Serial.println("done");
}
