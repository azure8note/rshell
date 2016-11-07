CC=g++
CC_FLAGS= -g -Wall -Werror -ansi -pedantic

all: CmdComposite And MultiCmd SingleCmd Or
	mkdir -p bin
	$(CC) $(CC_FLAGS) ./src/main.cpp CmdComposite.o And.o MultiCmd.o SingleCmd.o Or.o -o ./bin/rshell

rshell: CmdComposite And MultiCmd SingleCmd Or
	mkdir -p bin
	$(CC) $(CC_FLAGS) ./src/main.cpp CmdComposite.o And.o MultiCmd.o SingleCmd.o Or.o -o ./bin/rshell

CmdComposite:
	$(CC) $(CC_FLAGS) -c ./src/CmdComposite.cpp

And: 
	$(CC) $(CC_FLAGS) -c ./src/And.cpp

MultiCmd:
	$(CC) $(CC_FLAGS) -c ./src/MultiCmd.cpp

SingleCmd:
	$(CC) $(CC_FLAGS) -c ./src/SingleCmd.cpp

Or:
	$(CC) $(CC_FLAGS) -c ./src/Or.cpp

clean:
	rm -f *.o
	rm -f *.cpp~
	rm -f *.h~
	rm -r bin

