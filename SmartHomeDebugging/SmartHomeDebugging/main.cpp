#include <iostream>

using namespace std;

/*Die Funktion ID_Zusammensetzen nimmt 4 aufeinander folgende
je 8Bit groﬂen Can-Datentelegramme, und setzt daraus eine
32-Bit lange CAN UID zusammen:
n8Bit_array = { 0b00001111, 0b10101010, 0b11001100, 0b11111111}
cout << ID_Zusammensetzen(n8Bit_Array);
Ausgabe:
00001111101010101100110011111111
Version 0.1		30.12.2018
*/
uint32_t ID_Zusammensetzen (uint8_t *_8Bit_array/*, uint32_t *Zeiger*/)
{
/*	Serial.println("ID wird nun zusammengesetzt");
	Serial.println(_8Bit_array[0]);
	Serial.println(_8Bit_array[1]);
	Serial.println(_8Bit_array[2]);
	Serial.println(_8Bit_array[3]);
	uint32_t ID = 0;
	Zeiger = &ID;
	for (int i=0; i<4; i++)
	{
		ID = ID + (_8Bit_array[i] << (8*(3-i)));
		Serial.println(ID, BIN);
	}
	return Zeiger;
	*/
			uint32_t ID = 0;
			uint32_t temp = 0;
				for (int i=0; i<4; i++)
				{
					temp = _8Bit_array[i];
					ID = ID + (temp << (8*(3-i)));
				}
				_8Bit_array[0] = 0;
				_8Bit_array[1] = 0;
				_8Bit_array[2] = 0;
				_8Bit_array[3] = 0;
				return ID;
}

uint32_t ID_Maske_berechnen (uint32_t *_ID_Liste, uint8_t ID_list_lenght)
{
	//ODER-Verkn¸fung aller IDs der Reihe nach
	uint32_t Maske = 0;
	for (uint8_t i=0; i<ID_list_lenght; i++ )
	{
		Maske = Maske | _ID_Liste[i];
	}
	return Maske;
}



int main()
{
    uint8_t buffer[] = {0xAB, 0xCD, 0xEF, 0x89};
    uint32_t ID = 0;
    cout << "Smart Home Debugging!" << endl;
    ID = ID_Zusammensetzen(buffer);
    cout << "ID lautet: " << hex << ID << endl;
    return 0;
}
