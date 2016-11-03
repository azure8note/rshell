#!/bin/sh

cd $OLDPWD

echo "Testing Single Commands...\n"

rshell/src/bin/rshell < single_command.txt
