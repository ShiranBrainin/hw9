

CXX = g++
CXXFLAGS = -g -Wall -Wextra -L.
RM = clean
LINKFLAF = -fPIC -shared

LIB_OBJS = string.cpp field.cpp port.cpp ip.cpp
MAIN_OBGS = main.cpp

EXECXX = firewall.exe
EXECXX_LIB = firewall
SUPP_LIB = input

all::firewall.exe

firewall:
	$(CXX) $(CXXFLAGS) $(LINKFLAF) $(LIB_OBJS) -o libfirewall.so

firewall.exe: firewall
	$(CXX) $(CXXFLAGS) main.cpp -o firewall.exe -lfirewall -linput


$(RM):
	rm -rf *.o $(EXECXX) $(EXECXX_LIB)