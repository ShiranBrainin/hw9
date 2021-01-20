#include "ip.h"


Ip::Ip(String pattern) : Field(pattern){

	this->set_value(pattern);
}

bool Ip::set_value(String val) {
	String **substr = new String*[6]; //IP_SUBSTRINGS=4
	size_t tsize  = 0;
	size_t *sub_size = &tsize;
	val.split("=./",substr,sub_size);

	int num_care = substr[5]->to_integer();

	Field field(val);

	unsigned int ip_int = 0;
	for (int i=0; i<4 ; i++) {       //IP_BYTES=4
		int cur_add = substr[1+i]->to_integer();
		ip_int += cur_add << (24-8*i);
	}
	unsigned int var = 0xffffffff;
	unsigned int and_var = var << (32-num_care);
	this->low = and_var & ip_int;
	
	var = var >> num_care;
	this->high = this->low+var;
	
	cout << "high = " << this->high << endl;
	cout << "low = " << this->low << endl;

	for(int j=0;j<6;j++) {
		delete substr[j];
	}
	delete[] substr;

	return 1;
}

bool Ip::match_value(String val) const{
	String **substr = new String*[4]; //IP_VALUE_SUBSTRINGS=4
	size_t tsize = 0;
	size_t *sub_size = &tsize;
	//val.split("=./",substr,sub_size);
	val.split("/.@",substr,sub_size);

	unsigned int ip_int = 0;
	for (int i=0; i<4 ; i++) {       //IP_BYTES=4
		int cur_add = substr[i]->to_integer();
		cout << "cur_add = " << cur_add << endl;
		ip_int += cur_add << (24-8*i);
	}

	cout << "ip_int = " << ip_int << endl;

	for(int j=0;j<4;j++) { //IP_BYTES=4
		delete substr[j];
	}
	delete[] substr;
	if (this->low <= ip_int && ip_int <= this->high) {
		return true;
	}
	return false;
}