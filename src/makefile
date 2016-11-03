CC=g++
CC_FLAGS= -g -Wall -Werror -ansi -pedantic
EXEC=rshell
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
SAVFILES1=$(wildcard *.cpp~)
SAVFILES2=$(wildcard *.h~)

all: main.cpp $(OBJECTS) #|bin
	$(CC) $(OBJECTS) -o $(EXEC) #&& mv rshell bin/

rshell: $(OBJECTS) #|bin
	$(CC) $(OBJECTS) -o $(EXEC) #&& mv rshell bin/ 

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

bin: 
	mkdir bin

clean:
	rm -f $(EXEC) $(OBJECTS) $(SAVFILES1) $(SAVFILES2)
