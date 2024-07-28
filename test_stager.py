import time
import socket
import binascii
import numpy as np
import rp2daq 
import threading

#!/usr/bin/python3  
#dump as hex : nc -lp 2000|hexdump -C



channels = [0]     # 0,1,2 are GPIOs 26-28;  3 is V_ref and 4 is internal thermometer
kSPS_total = 500    # note there is only one multiplexed ADC


    
    

socktcp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
socktcp.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)




## Connect to the device
rp = rp2daq.Rp2daq()


## Run-time objects and variables
all_ADC_done = threading.Event() # a thread-safe semaphore
all_data = []
delayed = []

def ADC_callback(**kwargs): 
    all_data = kwargs['data']
    delayed = [kwargs['block_delayed_by_usb']]*(len(kwargs['data'])//2)
    #print(len(all_data),len(delayed))
    gosm = np.array(all_data).astype(np.int16)
    socktcp.sendto(gosm.tobytes(order='C'), ("255.255.255.255", 1245))


## Initialize the ADC into asynchronous operation...
t0 = None
rp.adc(channel_mask=1, 
        blocksize=1000, 
        infinite=1,
        trigger_gpio=-1,
        clkdiv=int(48000//kSPS_total), 
        _callback=ADC_callback)

all_ADC_done.wait()