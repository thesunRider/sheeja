import time
import socket
import binascii
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client_socket.settimeout(5)
client_socket.bind(('',1234))

try:
    while(1):
        data, server = client_socket.recvfrom(1024)
        #print(binascii.hexlify(bytearray(data)))

except socket.timeout:
    print('REQUEST TIMED OUT')
