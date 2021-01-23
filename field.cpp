#include "field.h"
#include "ip.h"
#include "port.h"

using namespace std;
enum {TOT_SUBSTRINGS=4};
enum {TYPE_SUBSTR=1};

Field::Field(String pattern) : 
	pattern(pattern) {
	this->type = this->get_type();
}

Field::~Field() {
	//this->pattern.~String();
}

field_type Field::get_type() const{
	String **substr = new String*[TOT_SUBSTRINGS]; //TOT_SUBSTRINGS=4
	size_t tsize = 0;
	size_t *sub_size = &tsize;
	this->pattern.split("=-",substr,sub_size);
	field_type ftype = GENERIC;
	//cout << "before using substring in get type" << endl;
	*substr[TYPE_SUBSTR] = substr[TYPE_SUBSTR]->trim();
	if(substr[TYPE_SUBSTR]->equals("port")) { //TYPE_SUBSTR=1
		//cout << "PORT!!!!!!!!!!!!!!" << endl;
		ftype = PORT;
	} else if(substr[TYPE_SUBSTR]->equals("ip")) { //TYPE_SUBSTR=1
		//cout << "IP!!!!!!!!!!!!!!" << endl;
		ftype = IP;
	}
	//cout << "used substrings in get type" << endl;
	//cout << *sub_size << endl;
	for(int i=0; i<*sub_size; i++) {
		delete substr[i];
		//cout << "okay" << endl;
	}
	delete[] substr;
	return ftype;
}

bool Field::set_value(String val){
	return 0;
}

bool Field::match_value(String val) const{
	bool x = false;
	if(this->type == PORT) {
		Port temport(this->pattern);
		x = temport.match_value(val);
		//cout << "this is PORT" << endl;
		// calling port match value
	}
	else if(this->type == IP) {
		Ip tempip(this->pattern);
		x = tempip.match_value(val);
		//cout << "this is IP" << endl;
	}
	return x;
}

bool Field::match(String packet) {
	//cout << "!!! entered Field::match !!!" << endl;
	String** sub_pattern = new String*[2];
	size_t t = 0;
	size_t *num_sub_pattern = &t;
	this->pattern.split("=",sub_pattern, num_sub_pattern);
	//cout << "!!! splitted Field::match - pattern !!!" << endl;

	for(size_t j=0; j<*num_sub_pattern; j++){
		//cout << "in for loop" << endl;
		*sub_pattern[j] = sub_pattern[j]->trim();
	}

	String** sub_packet = new String*[8];
	size_t t2 = 0;
	size_t *num_sub_packet = &t2;
	packet.split(",=", sub_packet, num_sub_packet);
	//cout << "finished packet split !!!" << endl;
	//cout << "num_sub_packet = " << *num_sub_packet << endl;
	
	for(size_t j=0; j<*num_sub_packet; j++){
		//cout << "in for loop" << endl;
		*sub_packet[j] = sub_packet[j]->trim();
	}
	//cout << "finished for loop" << endl;
	
	for (size_t i = 0 ; i<*num_sub_packet ; i++) {
		//cout << "i = " << i << endl;
		if(sub_pattern[0]->equals(*sub_packet[i])){ /* need to check if its OK to put pointer argument instead of refference in equals */
			bool ret = this->match_value(*sub_packet[i+1]);
			//cout << ret << " = ret, " << i << " = i." << endl;
			//cout << endl;
			//cout << endl;
			delete sub_pattern[0];
			delete sub_pattern[1];
			delete[] sub_pattern;
			for(size_t k = 0; k<*num_sub_packet; k++){
				delete sub_packet[k];
			}
			delete[] sub_packet;
			return ret;
		}
	}
	return 0;
}