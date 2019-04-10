/* 
* Taster.h
*
* Created: 09.04.2019 11:33:54
* Author: Bastian Reul
Version 1.0		09.04.2019		Fertigstellung der rudimentären Funktionen der Klasse Taster
*/


#ifndef __TASTER_H__
#define __TASTER_H__

#include "Pin_ATMEGA328.h"

class Taster
{
//variables
public:
	bool StatusAenderung = false;
protected:
private:
	bool pPullDown = true;
	uint8_t pDelayTime = 200; //Standard Delay Time zum entprellen des Tasters. Kann für jeden Taster manuel verändert werden, ist aber Standardmäßig auf 200ms eingestellt
	bool pIgnore = false;	//Hiermit kann der Taster ignoriert oder gesperrt werden. Ist standardmäßig deaktiviert.

//functions
public:
	Taster(Pin TasterPin, bool PullUp);
	Taster();
	~Taster();
protected:
private:
	Taster( const Taster &c );
	Taster& operator=( const Taster &c );

}; //Taster

#endif //__TASTER_H__
