/*
 * Hausbus.h
 *
 * Created: 17.12.2018 16:58:44
 *  Author: Bastian Reul
 */ 



#ifndef HAUSBUS_H_
#define HAUSBUS_H_

#define UID_KELLER_HUB	0b00100100000000000000000000
#define UID_NODE		0b00100100101100000000000000
//#define UID_MASK_ONE	0b11111111111111111111111111
#define UID_MASK_ONE	0x1fffffff
#define UID_MASK_ZERO	0x00000000
#define ID_01_Keller_1_Bastelkeller_Licht_ROT			0b00000011001001001011000000000000
#define ID_01_Keller_1_Bastelkeller_Licht_GRUEN			0b00000011001001001011100000000000
#define ID_01_Keller_1_Bastelkeller_Licht_BLAU			0b00000011001001001010100000000000
#define ID_01_Keller_1_Bastelkeller_Licht				0b00000011001001001011000000000000
#define ID_02_Keller_1_Bastelkeller_Lichtschalter_ROT	0b00100100101100000000000000000001
#define ID_02_Keller_1_Bastelkeller_Lichtschalter_Gruen	0b00100100101100000000000000000010
#define ID_02_Keller_1_Bastelkeller_Lichtschalter_BLAU	0b00100100101100000000000000000011


#define Kommando_Get_HUB_ID 1 
#define Kommando_Get_ID_LIST_FROM_HUB 2 

#define Kommando_Licht_an 1
#define Kommando_Licht_aus 2
#define Kommando_Licht_toggle 3

#define ID_LIST_MAXIMUM 20


uint32_t ID_Zusammensetzen (uint8_t *_8Bit_array/*, uint32_t *Zeiger*/);
uint32_t ID_Maske_berechnen (uint32_t *_ID_Liste, uint8_t ID_list_lenght);
//Die Funktion ist n�tig zum Debugging, da eine Serielle Datenausgabe der ID mittels Serial.println(ID, BIN); keine f�hrende Nullen ausgibt
void ID_Ausgeben(uint32_t ID);


#endif /* HAUSBUS_H_ */