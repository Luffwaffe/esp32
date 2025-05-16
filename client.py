import socket
import time

sock = socket.socket()
sock.connect(('192.168.2.17', 12345))
sock.sendall(b'start\n')
print(sock.recv(1024))
time.sleep(10)
# sock.sendall(b'start1\n')
# print(sock.recv(1024))
sock.close()