#include "input.h"
//#include "libinput.so"
//#include "libfirewall.so"
//#include "string.h"
//#include "field.h"
//#include "ip.h"
//#include "port.h"
#include <iostream>
//#include <ctype.h>

using namespace std;

int main(int argc, char **argv) {
	
	//String str("dst-ip=120.0.0.0/8");
	//Field f1(str);
	//String Packet2("dst-port  =  280  ,src-ip =120.0.123.19   ,dst-ip=   122.1.255.255  ,  src-port= 101 ");
	//bool x1 = f1.match(Packet2);
	//cout << "x1 = " << x1 << endl;	

	//cout << argc << endl;
	//cout << argv[1] << endl;
	bool x2 = check_args(argc, argv);
	//cout << "x2 = " << x2 << endl;
	
	Field f(argv[1]);
	//cout << endl;
	//cout << "finished constructing field" << endl;
	//cout << endl;

	parse_input(f);
	//String pat(pattern);

	return 0;

}
