import zmq
from random import randrange
import time


context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5556")

while True:
    zipcode = 10001
    temperature = randrange(-80, 135)
    relhumidity = randrange(10, 60)

    print(f"sending {zipcode} {temperature} {relhumidity}")
    
    socket.send_string(f"{zipcode} {temperature} {relhumidity}")
    time.sleep(5)