# rshell
Assingment2

This repository has made a small command shell that emulates the commandline of your average terminal. This program is equiped with the utility and abilty that the normal terminals posses, such as executing commands and even using connectors to execute multiple commands based on the success or failure of the previous command.

# Known Buggs
1) inputing a invalid command breaks our shell so you will have to close the client manually
2) imputing two connecters next to eachother will not work and will break the client
3) this specific combination of commands will not work "cat && date && ls" they work alone and in pairs but unfortunatly all three in this order will break the shell.
