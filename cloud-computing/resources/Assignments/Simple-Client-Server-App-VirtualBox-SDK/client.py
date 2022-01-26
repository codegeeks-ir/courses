from socket import *

server_port = YOUR_PORT_NUMBER
server_socket = socket(AF_INET, SOCK_STREAM)
server_socket.bind(('',server_port))
server_socket.listen(2)
while True:
  connection_socket, address = server_socket.accept()
  Receive_message = connection_socket.recv(YOUR_PORT_NUMBER).decode(“utf-8”)
  print(Receive_message)
  if Receive_message == 'Hello Guest’
    Response_message= 'How are you?’
    connection_socket.send(Response_message.encode(“utf-8”)
  connection_socket.close()
  Break 
