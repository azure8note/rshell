#!/bin/sh

cd $OLDPWD

echo "Testing Multi Commands...\n"

rshell/src/bin/rshell < multi_command.txt
