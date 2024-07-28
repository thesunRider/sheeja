import time
import socket
import binascii

socktcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
socktcp.connect(('127.0.0.1', 1273))  





client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client_socket.settimeout(5)
client_socket.bind(('',1234))

delta_avg = 0
count = 0
try:
    while(1):
        start_time = time.time()
        data, server = client_socket.recvfrom(1472)
        socktcp.sendall(b'1')  
        end_time = time.time()
        delta_time = end_time - start_time
        delta_avg = (delta_avg*count + delta_time)/(count+1)
        count += 1
        print(binascii.hexlify(bytearray(data))," avg=",delta_avg)

except socket.timeout:
    print('REQUEST TIMED OUT')

sock.close()
client_socket.close()