all.o: main.o CmdComposite.o SingleCmd.o  MultiCmd.o
	g++ -g main.o CmdComposite.o SingleCmd.o MultiCmd.o
