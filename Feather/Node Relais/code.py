import board
import digitalio
import time
import struct

import json
import canio

Relais1_aus = digitalio.DigitalInOut(board.D4)
Relais1_ein = digitalio.DigitalInOut(board.D9)
Relais1_aus.direction = digitalio.Direction.OUTPUT
Relais1_ein.direction = digitalio.Direction.OUTPUT
Relais1_aus.value = False
Relais1_ein.value = False

Relais2_aus = digitalio.DigitalInOut(board.D6)
Relais2_ein = digitalio.DigitalInOut(board.D5)
Relais2_aus.direction = digitalio.Direction.OUTPUT
Relais2_ein.direction = digitalio.Direction.OUTPUT
Relais2_aus.value = False
Relais2_ein.value = False

# Funktionen des Client Nodes
def Relais_1_einschalten():
    Relais1_aus.value = False
    Relais1_ein.value = True
    time.sleep(0.5)
    Relais1_ein.value = False

def Relais_1_ausschalten():
    Relais1_ein.value = False
    Relais1_aus.value = True
    time.sleep(0.5)
    Relais1_aus.value = False

def Relais_2_einschalten():
    Relais2_aus.value = False
    Relais2_ein.value = True
    time.sleep(0.5)
    Relais2_ein.value = False

def Relais_2_ausschalten():
    Relais2_ein.value = False
    Relais2_aus.value = True
    time.sleep(0.5)
    Relais2_aus.value = False



# If the CAN transceiver has a standby pin, bring it out of standby mode
if hasattr(board, 'CAN_STANDBY'):
    standby = digitalio.DigitalInOut(board.CAN_STANDBY)
    standby.switch_to_output(False)

# If the CAN transceiver is powered by a boost converter, turn on its supply
if hasattr(board, 'BOOST_ENABLE'):
    boost_enable = digitalio.DigitalInOut(board.BOOST_ENABLE)
    boost_enable.switch_to_output(True)

# Use this line if your board has dedicated CAN pins. (Feather M4 CAN and Feather STM32F405)
can = canio.CAN(rx=board.CAN_RX, tx=board.CAN_TX, baudrate=250_000, auto_restart=True)
# On ESP32S2 most pins can be used for CAN.  Uncomment the following line to use IO5 and IO6
#can = canio.CAN(rx=board.IO6, tx=board.IO5, baudrate=250_000, auto_restart=True)
listener = can.listen(matches=[canio.Match(0x408)], timeout=.9)

old_bus_state = None
old_count = -1
json_String = ""

while True:
    bus_state = can.state
    if bus_state != old_bus_state:
        print(f"Bus state changed to {bus_state}")
        old_bus_state = bus_state

    message = listener.receive()
    if message is None:
        print("No messsage received within timeout")
        if json_String != "":
            y = json.loads(json_String)
            # the result is a Python dictionary:
            print(y["Relaisnummer"])
            print(y["Status"])

            if y["Relaisnummer"] == "1":
                if y["Status"] == "True":
                    Relais_1_einschalten()
                else:
                    Relais_1_ausschalten()
            elif y["Relaisnummer"] == "2":
                if y["Status"] == "True":
                    Relais_2_einschalten()
                else:
                    Relais_2_ausschalten()
            else:
                print("Kein Passendes Relais gefunden")
            json_String = ""
        continue

    data = message.data
    print(data)
    #json_String = '{"Relaisnummer": "1" , "Status": "True"}'
    json_String = json_String + data.decode('utf-8')





