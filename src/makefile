CC=g++
CC_FLAGS= -g -Wall -Werror -ansi -pedantic
EXEC=a.out
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
SAVFILES1=$(wildcard *.cpp~)
SAVFILES2=$(wildcard *.h~)

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

rshell: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS) $(SAVFILES1) $(SAVFILES2)