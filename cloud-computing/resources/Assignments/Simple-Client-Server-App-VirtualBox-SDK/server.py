import virtualbox
from virtualbox.library import ProcessCreateFlag
from socket import *

vbox = virtualbox.VirtualBox()
session = virtualbox.Session()
machine = vbox.find_machine(“YOUR_VIRTUAL_OS_NAME”)
progress = machine.launch_vm_process(session, "gui", [])
progress.wait_for_completion()

host_session = machine.create_session()
guest_session = host_session.console.guest.create_session("YOUR_USERNAME” ,"YOUR_PASS”)
process = guest_session.process_create("/user/bin/terminal.sh ," ['/c ‘,'python client.py'], [], [ProcessCreateFlag(1)],0)
                                                                  
server_name = 'YOUR_IP_ADRESS’
sever_port = YOUR_PORT_NUMBER
client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((server_name, sever_port))
send_message = 'Hello Guest'
client_socket.send(send_message.encode(“utf-8”)
response_message = client_socket.recv(1024)
print("Host's Response:\n" + response_message.decode(“utf-8”))
client_socket.close() 
