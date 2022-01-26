# Work with VirtualBox SDK
Generally, in this case, i'll show you how to write and develope a simple application with virtualbox SDK.<br>
After that, i'll work with virtualbox api's, connection with COM port from windows to ubuntu-linux and creating an interface to interact and communication with virtual machine.
### Virtualbox SDK
Oracle VM VirtualBox comes with comprehensive support for third-party developers. The so-called Main API of Oracle VM VirtualBox exposes the entire feature set of the virtualization engine.<br>It is completely documented and available to anyone who wishes to control Oracle VM VirtualBox programmatically.<br>
The Main API is made available to C++ clients through COM on Windows hosts or XPCOM on other hosts. Bridges also exist for SOAP, Java and Python. 
### Download and Install SDK
Here you will find [links](https://www.virtualbox.org/wiki/Downloads) to VirtualBox binaries, SDK and its source code. 
### Configuration
After Download and install the pakage, you can follow these steps to config the virtualbox sdk and it's libraries. <br>
1. First in package directory, go to the installer folder and open your command-line, then type the `python vboxapisetup.py install` command.
Note that this command is for install all the virtualbox api and libraries you need for start the coding. second thing you should attention to it is you must installed 32-bit version of python in your system. 
2. At the end, with the `python -m pip install virtualbox` command, we add the main library of virtualbox to my python language using PyPi.
## Add Connection
You can open Python live and test the connection with your virtual-box.
- **To find available machine**
```
>> import virtualbox
>> vbox = virtualbox.VirtualBox()
>> [machine.name for machine in vbox.machines]
YOUR_AVAILABLE_VIRTUAL_MACHINES
```
- **Lunching your virtual-machine**
```
>>> session = virtualbox.Session()
>>> machine = vbox.find_machine("YOUR_AVAILABLE_VIRTUAL_MACHINE")
>>> progress = machine.launch_vm_process(session, "gui", [])
>>> progress.wait_for_completion()
```
- **Sending query**
```
>>> session.state
SessionState(2)  # Locked state
>>> machine.state
MachineState(5)  # Running state
>>> height, width = session.console.display.get_screen_resolution()
```
- **Interacting with virtual-machine**
```
>>> guest_session = session.console.guest.create_session("YOUR_USER_NAME", "YOUR_PASSWORD")
>>> guest_session.directory_exists("/usr/bin")
True
```
- **Shut it down**
```
>>> session.console.power_down()
>>>
```
