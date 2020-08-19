import socket

s=socket.socket()
s.bind(('140.115.158.219',5000))
s.listen(5)

while 1:
    cs, address = s.accept()
    print ('got connected from', address)
    cs.send('Hello'.encode())
    ra = cs.recv(512)
    addr = cs.getpeername()
    print (ra)
    
    
    
    cs.close()

