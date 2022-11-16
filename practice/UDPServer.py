from socket import *
import rsa
# assign port and create socket with ipv4 and socket type dgram (UDP)
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
# assign port number to server socket
serverSocket.bind(('', serverPort))
print('The server is ready to receive')
# while loop allow server to receive and process from clients indefinitely, waits for a packet to arrive
while True:
    #when packet arrives at socket, packet's data is put into variable message and source address (IP and port num) in clientAddress
    message, clientAddress = serverSocket.recvfrom(2048)
    # modifies packet data
    modifiedMessage = message.decode().upper()
    print("Server received and changed original message from: " + message.decode() + " to: " + modifiedMessage)
    serverSocket.sendto(modifiedMessage.encode(), clientAddress)