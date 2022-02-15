import struct
import time
import busio
import board
import canio
from digitalio import DigitalInOut
import digitalio

from adafruit_wiznet5k.adafruit_wiznet5k import WIZNET5K
import adafruit_wiznet5k.adafruit_wiznet5k_socket as socket

import adafruit_minimqtt.adafruit_minimqtt as MQTT

# Get Adafruit IO details and more from a secrets.py file
try:
    from secrets import secrets
except ImportError:
    print("Adafruit IO secrets are kept in secrets.py, please add them there!")
    raise

cs = DigitalInOut(board.D10)
spi_bus = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)

# Initialize ethernet interface with DHCP
eth = WIZNET5K(spi_bus, cs)

### Feeds ###

# Setup a feed named 'photocell' for publishing to a feed
photocell_feed = secrets["aio_username"] + "/feeds/photocell"

# Setup a feed named 'onoff' for subscribing to changes
onoff_feed = secrets["aio_username"] + "/feeds/onoff"

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


count = 0


# Define callback methods which are called when events occur
# pylint: disable=unused-argument, redefined-outer-name
def connected(client, userdata, flags, rc):
    # This function will be called when the client is connected
    # successfully to the broker.
    print("Connected to Adafruit IO! Listening for topic changes on %s" % onoff_feed)
    # Subscribe to all changes on the onoff_feed.
    client.subscribe(onoff_feed)


def disconnected(client, userdata, rc):
    # This method is called when the client is disconnected
    print("Disconnected from Adafruit IO!")


def message(client, topic, mqtt_message):
    # This method is called when a topic the client is subscribed to
    # has a new message.
    print("New message on topic {0}: {1}".format(topic, mqtt_message))
    print(f"Can Master: ")
    old_bus_state = None
    #bus_state = None
    bus_state = can.state
    if bus_state != old_bus_state:
        print(f"Bus state changed to {bus_state}")
        old_bus_state = bus_state

    print(f"Sending message: count={count}")
    can_max_laenge = 8
    #json_String = '{"Relaisnummer": "1" , "Status": "True"}'
    json_String = mqtt_message
    message_laenge = len(json_String)
    message_anzahl = int(message_laenge / can_max_laenge)
    messages = list()
    aktueller_Teilstring = ""
    counter = 0
    for i in json_String:
        aktueller_Teilstring = aktueller_Teilstring + i
        counter = counter +1
        if counter > 7:
            messages.append(aktueller_Teilstring)
            #print(aktueller_Teilstring)
            aktueller_Teilstring = ""
            counter = 0
    aktueller_Teilstring = ""
    while counter != 0:
        aktueller_Teilstring = aktueller_Teilstring + json_String[message_laenge - counter]
        counter = counter - 1
    messages.append(aktueller_Teilstring)

    print(f"Message wurde zerlegt: ")
    for i in messages:
        print(i)

    for x in messages:
        message = canio.Message(id=0x408, data=x)
        can.send(message)
        time.sleep(.5)



# Initialize MQTT interface with the ethernet interface
MQTT.set_socket(socket, eth)

# Set up a MiniMQTT Client
# NOTE: We'll need to connect insecurely for ethernet configurations.
mqtt_client = MQTT.MQTT(
    broker="bastian-server.ddns.net",
    username=secrets["aio_username"],
    password=secrets["aio_key"],
    is_ssl=False,
)

# Setup the callback methods above
mqtt_client.on_connect = connected
mqtt_client.on_disconnect = disconnected
mqtt_client.on_message = message

# Connect the client to the MQTT broker.
print("Connecting to Adafruit IO...")
mqtt_client.connect()

photocell_val = 0

while True:
    # Poll the message queue
    mqtt_client.loop()
    #bus_state = can.state

    # Send a new message
    #
    #



