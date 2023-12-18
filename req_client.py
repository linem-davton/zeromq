import zmq
import argparse
# Contexct and Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

# get the client id from the command line
parser= argparse.ArgumentParser()
parser.add_argument('client', type=int, help='Client id')
args = parser.parse_args()

#  Do 10 requests, waiting each time for a response
for request in range(100):
    # message to be sent
    msg_str = f'I am Client {args.client}'
    print(f"Sending request {request} {msg_str}")

    socket.send_string(msg_str)

    #  Get the reply.
    message = socket.recv()

    # Reply is bytes converting to string 
    print(f"Received reply {message.decode()}")
    