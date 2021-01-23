#include "port.h"
using namespace std;

Port::Port(String pattern):Field(pattern){
	this->set_value(pattern);
}
bool Port::set_value(String val){
	String** sub_pattern = new String*[4];
	size_t t = 0;
	size_t *num_sub_pattern = &t;
	
	val.split("=-",sub_pattern, num_sub_pattern);
	for(size_t j=0; j<*num_sub_pattern; j++){
		//cout << "in for loop" << endl;
		*sub_pattern[j] = sub_pattern[j]->trim();
	}
		
	this->range[0] = sub_pattern[2]->to_integer();
	this->range[1] = sub_pattern[3]->to_integer();
	//cout << "range[0] - " << this->range[0] << endl;
	//cout << "range[1] - " << this->range[1] << endl;
	int i;
	for(i=0; i<4; i++){
		delete sub_pattern[i];
	}
	delete[] sub_pattern;
	return true;
}

bool Port::match_value(String val) const{
	int port_val = val.to_integer();
	//cout << port_val << " = port value" << endl;
	if( port_val >= this->range[0] && port_val <= this->range[1] ){
		return true;
	}
	else{
		return false;
	}
}
