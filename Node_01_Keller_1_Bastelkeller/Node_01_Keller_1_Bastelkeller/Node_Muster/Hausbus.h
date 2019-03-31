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
#define UID_MASK_ONE	0b11111111111111111111111111
#define UID_MASK_ZERO	0b00000000000000000000000000


#define Kommando_Get_HUB_ID 1 
#define Kommando_Get_ID_LIST_FROM_HUB 2 

#define ID_LIST_MAXIMUM 20


uint32_t ID_Zusammensetzen (uint8_t *_8Bit_array/*, uint32_t *Zeiger*/);
uint32_t ID_Maske_berechnen (uint32_t *_ID_Liste, uint8_t ID_list_lenght);

#endif /* HAUSBUS_H_ */