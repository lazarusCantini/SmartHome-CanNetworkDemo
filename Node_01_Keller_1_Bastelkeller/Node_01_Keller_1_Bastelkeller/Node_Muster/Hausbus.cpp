/*
 * Hausbus.cpp
 *
 * Created: 17.12.2018 16:58:32
 *  Author: Bastian Reul
 */ 

#include <stdint.h>

#include <Arduino.h>
#include <math.h>
/*Die Funktion ID_Zusammensetzen nimmt 4 aufeinander folgende
je 8Bit groﬂen Can-Datentelegramme, und setzt daraus eine
32-Bit lange CAN UID zusammen:
n8Bit_array = { 0b00001111, 0b10101010, 0b11001100, 0b11111111}
cout << ID_Zusammensetzen(n8Bit_Array);
Ausgabe:
00001111101010101100110011111111
Version 0.1		30.12.2018
Version 0.1a	03.04.2019
*/

uint32_t BinaerPotenzen[] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648 };


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

//Die Funktion ist nˆtig zum Debugging, da eine Serielle Datenausgabe der ID mittels Serial.println(ID, BIN); keine f¸hrende Nullen ausgibt
void ID_Ausgeben(uint32_t ID)
{
	uint32_t rest = ID;
	for (int i=31; i>=0; i--)
	{
		if (rest >= BinaerPotenzen[i])
		{
			Serial.print('1');
			rest = rest - BinaerPotenzen[i];	
		}
		else
		{
			Serial.print('0');
		}
	}
}