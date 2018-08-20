# client

import socket

address = ('127.0.0.1', 31500)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# connect address to correct ip and port
s.connect(address)                                      
s.send(b'hello, I am client')
data = s.recv(1024).decode('utf-8')
print('the data received is', data)

s.close()
