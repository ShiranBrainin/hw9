#include "field.h"
enum TOT_SUBSTRINGS 4;
enum TYPE_SUBSTR 1;


Field::Field(String pattern) : 
	pattern(pattern) {
	this->type = this->get_type();
}

Field::~Field() {
	//this->pattern.~String();
}

field_type Field::get_type() const{
	String **substr = new String*[4]; //TOT_SUBSTRINGS=4
	size_t tsize = 0;
	size_t *sub_size = &tsize;
	this->pattern.split("=-",substr,sub_size);
	field_type ftype = GENERIC;

	if(substr[1]->equals("port")) { //TYPE_SUBSTR=1
		cout << "subsr1=port!!!!" << endl;
		ftype = PORT;
	} else if(substr[1]->equals("ip")) { //TYPE_SUBSTR=1
		ftype = IP;
	}
	for(int i=0; i<4; i++) {
		delete substr[i];
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
		cout << "this is PORT" << endl;
		// calling port match value
	}
	else if(this->type == IP) {
		Ip tempip(this->pattern);
		x = tempip.match_value(val);
		cout << "this is IP" << endl;
	}
	return x;
}

bool Field::match(String packet) {
	cout << "entered match" << endl;
	String** sub_pattern = new String*[2];
	size_t t = 0;
	size_t *num_sub_pattern = &t;
	cout << "Before split pattern in MATCH" << endl;
	this->pattern.split("=",sub_pattern, num_sub_pattern);
	
	String** sub_packet = new String*[8];
	size_t t2=0;
	size_t *num_sub_packet = &t2;
	cout << "Before split packet in MATCH" << endl;
	packet.split(",=",sub_packet, num_sub_packet);
	cout << "After split packet in MATCH" << endl;
	int j;
	for(j=0; j<8; j++){
		*sub_packet[j] = sub_packet[j]->trim();
	}
	int i;
	for (i=0 ; i<8 ; i++) {
		cout << "i = " << i << endl;
		if(sub_pattern[0]->equals(*sub_packet[i])){ /* need to check if its OK to put pointer argument instead of refference in equals */
			cout << "equals worked in MATCH" << endl;
			bool ret = this->match_value(*sub_packet[i+1]);
			cout << ret << " = ret, " << i << " = i." << endl;
			delete sub_pattern[0];
			delete sub_pattern[1];
			delete[] sub_pattern;
			int k;
			for(k=0; k<8; k++){
				delete sub_packet[k];
			}
			delete[] sub_packet;
			return ret;
		}
	}
	cout << "finished for loop in MATCH" << endl;
	return 0;
}
