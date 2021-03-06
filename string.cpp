#include <iostream>
#include <stdio>
#include "string.h"


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
	cout << "wow" << endl;
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
	//char *cur_p = this->data;
	int cur_p = 0;
	char *cur_begin_p = this->data+cur_p;
	int cur_output_size = 0;
	int cur_str_size = 0;
	bool just_splitted = false;
	int deli_cnt = 0;
	//cout << "wow we about to start a while loop" << endl;
	while(this->data[cur_p]) {
		//cout << "not good to see it infinity times" << endl
		while(delimiters[deli_cnt]) {
			cout << deli_cnt << endl;
			cout << "we eneted second while" << endl;
			if(this->data[cur_p]==delimiters[deli_cnt]) {
				char *temp_str = new char[cur_str_size+1];
				strncpy(temp_str, cur_begin_p, cur_str_size);
				cout << cur_str_size << endl;
				String *out_element = new String(temp_str); 
				output[cur_output_size] = out_element;
				cout << "wow" << endl;
				delete[] temp_str;

				//deli_cnt++;
				cur_str_size = 0;
				cur_begin_p = this->data+cur_p+1;
				cur_output_size++;
				just_splitted = true;
			}
			if (just_splitted) {
				cout << "we split, deli_cnt = " << delimiters[deli_cnt] << endl;
				just_splitted = false;
				break;
			}
			deli_cnt++;
		}
		cur_str_size++;
		deli_cnt = 0;
		cout<< this->data[cur_p] <<endl;
		cur_p++;
	}
	*size = cur_output_size;
}

int String::to_integer() const{
	int out = 0;
	/*int temp = sscanf(this->data , %d , &out);
	if ( temp != this->length){
		return 0;
	}*/
	return out;
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
	return new_string;
}
