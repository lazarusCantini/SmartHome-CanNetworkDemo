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
#define UID_MASK_ZERO	0b11111111111111111111111111

//#define UID_01_Keller_1_Bastelkeller_Lichtschalter	*	//0b00000001 //0b 00100100 10110000 00000000 01
#define ID_01_Keller_1_Bastelkeller_Lichtschalter 0b00100100101100000000000000000001
uint8_t UID_01_Keller_1_Bastelkeller_Lichtschalter[] = {0b00100100, 0b10110000, 0b00000000, 0b00000001};
														//  00100100    10110000    00000000    00001100
uint8_t *Zeiger_auf_UID_01_Keller_1_Bastelkeller_Lichtschalter = UID_01_Keller_1_Bastelkeller_Lichtschalter;

uint8_t UID_01_Keller_1_Bastelkeller_Licht[] = {0b00000011, 0b00100100, 0b10110000, 0b00000000};
#define ID_01_Keller_1_Bastelkeller_Licht 0b00000011001001001011000000000000
												 // 00000011    00100100    10110000    00010110
uint8_t *Zeiger_auf_UID_01_Keller_1_Bastelkeller_Licht = UID_01_Keller_1_Bastelkeller_Licht;

uint8_t UID_Liste_EndeIndikator[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000};
uint8_t *Zeiger_auf_UID_Liste_EndeIndikator = UID_Liste_EndeIndikator;

#define Kommando_Get_HUB_ID 1 
#define Kommando_Get_ID_LIST_FROM_HUB 2 

#define Kommando_Licht_an 1
#define Kommando_Licht_aus 2
#define Kommando_Licht_toggle 3

#endif /* HAUSBUS_H_ */