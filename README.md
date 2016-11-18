# rshell

Rshell is a command shell that emulates the command line of your average terminal. This program is equiped with the abilty to execute any command in bin that normal terminals posses, such as executing commands and even using connectors to execute multiple commands based on the success or failure of the previous command. Rshell can also execute the command test (using the test keyword or the symbolic implementation [ ]) and can handle precedence operators ().

# Known Bugs
1. Inputing a invalid command breaks our shell, so you will have to close the client manually.

2. The command echo cannot output connectors (e.g. echo "hello&&bye"). Attempting to do so will break the shell.
