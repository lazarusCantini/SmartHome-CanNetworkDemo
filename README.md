# SmartHome-CanNetworkDemo
Dieses Repository beinhaltet alle Dateien die Nötig sind, um das CAN NetzwerkDemo-Board aufzubauen.
## Aufbau
### Schema
![Aufbau-Schema](Bilder/Aufbau-Schema.png)
### Foto
![Aufbau-Foto](Bilder/Testaufbau-Foto.jpg)
### Pinbelegung für alle drei Arduinos gleich
CAN-BUS Modul | Arduino | ATMEGA328P
--------------|---------|-----------
INT (Invertiert)|2|PD2
SCK SPI CLK|13|PB5
SI MOSI|11|PB3
SO MISO|12|PB4
CS Chip Select|10|PB2
GND|GND|GND
VCC1 Versorgung|5V|\-
VCC Spg. Logikpegel|5V|\-

