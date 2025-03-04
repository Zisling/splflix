# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11

# All Targets
all: splflix

# Tool invocations
# Executable "splflix" depends on the files splflix.o and run.o.
splflix: bin/Session.o bin/Action.o bin/User.o bin/Watchable.o bin/Main.o
	@echo 'Building target: splflix'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/splflix bin/Session.o bin/Action.o bin/User.o bin/Watchable.o bin/Main.o$(LFLAGS)
	@echo 'Finished building target: splflix'
	@echo ' '

# Depends on the source and header files
bin/Session.o: src/Session.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Session.o src/Session.cpp
	
	# Depends on the source and header files
bin/Action.o: src/Action.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Action.o src/Action.cpp
	
	# Depends on the source and header files
bin/User.o: src/User.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/User.o src/User.cpp
	
bin/Watchable.o: src/Watchable.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Watchable.o src/Watchable.cpp


# Depends on the source and header files 
bin/Main.o: src/Main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Main.o src/Main.cpp
# Depends on the source and header files 


#Clean the build directory
clean: 
	rm -f bin/*
