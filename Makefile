CXX=g++										# gcc is the compiler
CCLINK=$(CXX) 								# Read variable CC using $(CC)
CXXFLAGS=-g -Wall -std=c11					# c99 or c11???????
OBJSF=field.o ip.o port.o string.o			#all of out object files
OBJSM=main.o
EXEC=firewall.exe			#our execute file
RM=rm -rf *.o *.exe libfirewall.so						# make clean command

#g++ -g -Wall -std=c11 

#linker command, creates the execute file from the objects file
$(EXEC): main.o 					
	$(CCLINK) -shared main.o -o firewall.exe -llibfirewall -llibinput -L.
# we have to link it also to libinput.so

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

libfirewall.so: field.o ip.o port.o string.o
	$(CXX) -shared field.o ip.o port.o string.o -o libfirewall.so 

field.o: field.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp

ip.o: ip.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

string.o: string.cpp
	$(CXX) $(CXXFLAGS) -c -fpic string


























































	.cpp

# the command "make clean" will call this rule
clean:
	$(RM)			#reading the variable RM

