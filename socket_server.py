# server

import socket
# set IP and Port
address = ('127.0.0.1', 31500)
# choose IPV4, stream type
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# bind address and ip
s.bind(address)
# allow max five connection
s.listen(5)                                             

while True:
    # wait client's request, cs is a new socket object and server use it to communicate with client
    cs, address = s.accept()                            
    print('got connected from', address)
    # send message to client
    cs.send('123')
    # receive message from client and decode
    re = cs.recv(1024).decode('utf-8')                  
    print(re)
    cs.close()
