
/*
selbst erstellte Library
zur Ansteuerung eines Pins an einem ATMEGA328
Version 0.1		04.11.2018		Erstellung der Klasse
Version 1.0		05.11.2018		Fertigstellung der rudimentären Funktionen der Klasse Pin
Version 1.1		09.04.2019		Erweiterung PullUp um Kompatibilität zur Klasse Taster zu schaffen
*/

#ifndef PIN_H
#define PIN_H
#include <stdint-gcc.h>

class Pin
{
	public:
	Pin();
	Pin(char PublicPort, uint8_t Public_Nummer_Pin, bool Eingang);
	void setze_Status(bool Status);
	void setze_Port(char PortBuchstabe);
	void setze_PinNummer(uint8_t Pin_Nummer);
	void setze_Richtung(bool is_Eingang);
	void initialisierePin();
	void toggle_Pin();
	char lese_Port();
	uint8_t lese_PinNummer();
	void PullUpSchalten(bool anschalten);
	
	bool lese_status();
	//virtual ~Pin();
	
	protected:
	
	private:
	char private_Port;
	uint8_t private_Nummer_Pin;
	void merke_status(bool status);
	bool private_Eingang;
	bool status_intern;
	bool status_PullUp_active = false;
};

#endif // PIN_H