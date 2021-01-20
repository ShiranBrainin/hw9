#include <iostream>
#include <stdio>
#include "string.h"
#include <ctype.h>

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
					cout << strlen(temp_str) << " = temp_str length" << endl;
					strncpy(temp_str, cur_begin_p, cur_str_size);
					/*cout << temp_str[0] << " = temp_str[0]" << endl;
					cout << temp_str[1] << " = temp_str[1]" << endl;
					cout << temp_str[2] << " = temp_str[2]" << endl;
					cout << temp_str[3] << " = temp_str[3]" << endl;
					cout << temp_str[4] << " = temp_str[4]" << endl;*/
					String *out_element = new String(temp_str); 
					output[cur_output_size] = out_element;
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