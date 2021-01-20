#include "input.h"
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <ctype.h>

using namespace std;
//#define TOT_SUBSTRINGS 4;
//#define TYPE_SUBSTR 1;

// compiling in terminal with: "g++ -g -Wall -o main.exe atest.cpp"

int main() {
	/*String str("src-ip=122.0.0.0/8");
	String str1("    Ori     ");
	String str_trimmed("sss");

	String ori_str("998asdf");

	int g = ori_str.to_integer();
	cout << "g is " << g << endl;
	

	str_trimmed = str1.trim();
	if(str_trimmed.equals("Ori")){
		cout << "was a good trim" << endl;
	}

	//str = str1;
	bool x = str_trimmed.equals("Ori");
	bool y = str1.equals("Shiran");
	cout << "x = " << x << endl;
	//cout << y << endl;
	String **substr = new String*[5];
	size_t sizet = 0;
	size_t *sub_size = &sizet;
	str.split(",=.",substr,sub_size);
	cout << "finished split" << endl;
	if(substr[0]->equals("src-ip")) {
		cout << "first substring works" << endl;
	} 
	if(substr[1]->equals("122")){
		cout << "second substring works" << endl;
	}
	if(substr[2]->equals("0")){
		cout << "third substring works" << endl;
	}
	if(substr[3]->equals("0")){
		cout << "fourth substring works" << endl;
	}
	int sub3 = substr[2]->to_integer();
	cout << "sub3 = " << sub3 << endl;
*/
	String pat("dst-ip=120.0.0.0/16");
	String pat2("dst-port=100-300");
	//String val("122.255.255.255");
	String Packet("dst-port=150,src-ip=121.0.3.0,dst-ip=120.0.255.255,src-port=76");

	//String test("300");
	Field ourfield(pat2);
	//cout << "before match" << endl;
	bool x = ourfield.match(Packet);
	//bool x = ourip.match_value(val);
	cout << "x = " << x << endl;
	//Port iport(pat2);
	//bool m = iport.match_value(test);
	//cout << "m = " << m << endl;

/*	Field ourf(pat);
	Field ourf2(pat2);
	field_type ftype = ourf.get_type();
	field_type ft2 = ourf2.get_type();
	cout << "ftype should be 0 and is actually " << ftype << endl;
	cout << "ft2 should be 1 and is actually " << ft2 << endl;
*/
	return 0;
}

Port::Port(String pattern):Field(pattern){
	this->set_value(pattern);
}

bool Port::set_value(String val){
	String** sub_pattern = new String*[4];
	size_t t=0;
	size_t *num_sub_pattern = &t;
	
	val.split("=-",sub_pattern, num_sub_pattern);
	this->range[0] = sub_pattern[2]->to_integer();
	this->range[1] = sub_pattern[3]->to_integer();
	cout << "range[0] - " << this->range[0] << endl;
	cout << "range[1] - " << this->range[1] << endl;
	int i;
	for(i=0; i<4; i++){
		delete sub_pattern[i];
	}
	delete[] sub_pattern;
	return true;
}

bool Port::match_value(String val) const{
	int port_val = val.to_integer();
	cout << port_val << " = port value" << endl;
	if( port_val >= this->range[0] && port_val <= this->range[1] ){
		return true;
	}
	else{
		return false;
	}
}


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




String::String(){
	this->data = NULL;
	this->length=0;
}

String::String(const String &str):
	data(new char[str.length +1] ),
	length(str.length){
	strcpy(this->data , str.data);
}

String::String(const char *str):
	data(new char[strlen(str) +1]),
	length(strlen(str)) {
	strcpy(this->data , str);
	cout << "the actual string is = " << this->data << endl;
}

String::~String(){
	delete[] this->data;
} 

String&  String::operator=(const String &rhs) {
	delete[] this->data;  // maybe just data, no need for "this"?
	this->length = rhs.length;
	this->data = new char[rhs.length+1];
	strcpy(this->data,rhs.data);
	return *this;
}

String& String::operator=(const char *str) {
	delete[] this->data;
	this->length = strlen(str);
	this->data = new char[strlen(str)+1];
	strcpy(this->data,str);
	return *this;
}

bool String::equals(const String &rhs) const {
	int x = strcmp(this->data,rhs.data);
	return (x==0);
}

bool String::equals(const char *rhs) const {
	int x = strcmp(this->data,rhs);
	return (x==0);
}

void String::split(const char *delimiters, String **output, size_t *size) const{
	int cur_p = 0;
	char *cur_begin_p = this->data+cur_p;
	int cur_output_size = 0;
	int cur_str_size = 0;
	bool just_splitted = false;
	int deli_cnt = 0;
	int integer = 0;

	while(this->data[cur_p]) {
		while(delimiters[deli_cnt]) {
			if(this->data[cur_p] == delimiters[deli_cnt]) {
				
				if(cur_str_size != 0) {
					//cout << cur_str_size << " = cur_str_size" << endl;
					char *temp_str = new char[cur_str_size+1];
					temp_str[cur_str_size] = '\0';
					int z = strlen(temp_str);
					cout << z << " = temp_str length" << endl;
					strncpy(temp_str, cur_begin_p, cur_str_size);
					/*cout << temp_str[0] << " = temp_str[0]" << endl;
					cout << temp_str[1] << " = temp_str[1]" << endl;
					cout << temp_str[2] << " = temp_str[2]" << endl;
					cout << temp_str[3] << " = temp_str[3]" << endl;
					cout << temp_str[4] << " = temp_str[4]" << endl;*/
					//String *out_element = new String(temp_str); 
					//output[cur_output_size] = out_element;
					output[cur_output_size] = new String(temp_str);
					integer = output[cur_output_size]->to_integer();
					cout << "wow! out new substring is: " << temp_str << endl;
					//cout << "and as integer it is " << integer << endl;
					delete[] temp_str;
					cur_output_size++;
				}
				cur_str_size = 0;
				cur_begin_p = this->data+cur_p+1;
				just_splitted = true;
			}
			if (just_splitted) {
				break;
			}
			deli_cnt++;
		}
		cur_str_size++;
		if(just_splitted) {
			just_splitted = false;
			cur_str_size = 0;
		}
		deli_cnt = 0;
		//cout << this->data[cur_p] <<endl;
		cur_p++;
	}
	if(cur_str_size>0) {
		char *temp_str = new char[cur_str_size+1];
		temp_str[cur_str_size] = '\0';
		strncpy(temp_str, cur_begin_p, cur_str_size);
		//cout << cur_str_size << endl;
		String *out_element = new String(temp_str); 
		output[cur_output_size] = out_element;
		cout << "wow! out new substring is: " << temp_str << endl;
		delete[] temp_str;
	}
	*size = cur_output_size;
	//cout << "exited 2 while loops" << endl;
}

int String::to_integer() const{
	int p = 0;
	cout << endl;
	//cout << "enetered to_integer!!!@@@!!!" << endl;
	cout << "out string = " << this->data << endl;
	while(this->data[p]) {
		//cout << "something" << endl;
		if (isdigit(this->data[p]) == 0) {
			//cout << "not an integer" << endl;
			return 0;
		}
		p++;
	}
	int x = atoi(this->data);
	cout << "it is an integer = " << x << endl;
	cout << endl;
	return x;
}

String String::trim() const{
	int front_spaces = 0;
	int back_i = this->length - 1;
	int back_spaces = 0;
	while(this->data[front_spaces] == ' ') {
		front_spaces++;
	}
	while(this->data[back_i] == ' ') {
		back_spaces++;
		back_i--;
	}
	int n = this->length - back_spaces - front_spaces;
	if(n == 0) {
		return String();
	}
	char *temp_str = new char[n+1];
	strncpy(temp_str, this->data+front_spaces, n);
	String new_string = String(temp_str);
	delete[] temp_str;
	return new_string;
}