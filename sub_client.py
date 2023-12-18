import sys
import zmq
import argparse


#  Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)

# get the client id from the command line
parser= argparse.ArgumentParser()
parser.add_argument('zip', type=str, help='zip code')
args = parser.parse_args()

print("Collecting updates from weather server for...", args.zip)
socket.connect("tcp://localhost:5556")

# Subscribe to zipcode, default is NYC, 10001
zip_filter = args.zip
socket.setsockopt_string(zmq.SUBSCRIBE, zip_filter)

# Process 5 updates
total_temp = 0
for update_nbr in range(100):
    string = socket.recv_string()
    print(f'Recieved {string}')
    zipcode, temperature, relhumidity = string.split()
    total_temp += int(temperature)

print((f"Average temperature for zipcode " 
    f"'{zip_filter}' was {total_temp / (update_nbr+1)} F"))