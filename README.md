# rshell
Assingment2

This repository has made a small command shell that emulates the commandline of your average terminal. This program is equiped with the utility and abilty that the normal terminals posses, such as executing commands and even using connectors to execute multiple commands based on the success or failure of the previous command.

# Known Bugs
1) Inputing a invalid command breaks our shell, so you will have to close the client manually.

2) Inputing two connectors one after another will not work and will break the client.

3) This specific combination of commands will not work "cat && date && ls" They work alone and in pairs, but unfortunatly, all three in this order will break the shell.
