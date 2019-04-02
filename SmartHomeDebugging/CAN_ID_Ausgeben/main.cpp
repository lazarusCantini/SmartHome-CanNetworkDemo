#include <iostream>
#include <math.h>

using namespace std;



//Die Funktion ist nötig zum Debugging, da eine Serielle Datenausgabe der ID mittels Serial.println(ID, BIN); keine führende Nullen ausgibt
void ID_Ausgeben(uint32_t ID)
{
	uint32_t rest = ID;
	for (int i=31; i>=0; i--)
	{
        if (rest >= pow(2, i))
        {
            cout << "1";
            rest = rest - pow(2,i);
        }
        else
        {
            cout << "0";
        }
	}
	cout << " " << endl;
	cout << "Ausgabe der ID beendet." << endl;

}

int main()
{
    uint32_t ID_Lichstschalter =    0b00100100101100000000000000000001;
    uint32_t ID_Licht =             0b00000011001001001011000000000000;
    cout << "IDs Ausgeben" << endl;
    cout << "ID Lichtschalter: \t\t";
    ID_Ausgeben(ID_Lichstschalter);
    cout << " " << endl;
    cout << "ID Licht: \t\t\t";
    ID_Ausgeben(ID_Licht);

    return 0;
}
