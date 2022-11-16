# Simple socket programming with UDP python version

from socket import *

# set hostname (can be string of IP address or hostname of server) and port
serverName = 'hostname'
serverPort = 12000

# create client's socket
clientSocket = socket(AF_INET, SOCK_DGRAM) #af_inet indicates ipv4, sockdram indicates udp
# input message
message = raw_input('Input lowercase sentence:') # input message
# send message through socket to destination host
clientSocket.sendto(message.encode(),(serverName, serverPort))
# when packet arrives at client's socket, packet's data is put into modifiedMessage and packet's source is put to serverAddress
modifiedMessage, serverAddress = clientSocket.recvfrom(2048) # buffer size 2048 as input works for most purposes
print(modifiedMessage.decode())
# close socket
clientSocket.close()