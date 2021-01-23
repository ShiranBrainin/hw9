#include <iostream>
#include "string.h"
#include <ctype.h>
using namespace std;

String::String(){
	this->data = NULL;
	this->length=0;
}

String::String(const String &str):
	data(new char[str.length +1] ),
	length(str.length){
	//cout << "string with reference" << endl;
	strcpy(this->data , str.data);
}

String::String(const char *str):
	data(new char[strlen(str) +1]),
	length(strlen(str)) {
	//cout << "string with char*" << endl;
	strcpy(this->data , str);
	//cout << "after string with char*" << endl;
}

String::~String(){
	delete[] this->data;
} 

String&  String::operator=(const String &rhs) {
	//cout << "string operator = with reference" << endl;
	delete[] this->data;  // maybe just data, no need for "this"?
	this->length = rhs.length;
	this->data = new char[rhs.length+1];
	strcpy(this->data,rhs.data);
	return *this;
}

String& String::operator=(const char *str) {
	//cout << "string operator = with reference" << endl;
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
	//cout << "entered equals char *" << endl;
	//cout << this->data <<  endl;
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
	bool no_char_approp = true;

	if(output == NULL) {
		while(this->data[cur_p]) {
			while(delimiters[deli_cnt]) {
				if(this->data[cur_p] == delimiters[deli_cnt]) {
					cur_output_size++;
				}
				deli_cnt++;
			}
			deli_cnt = 0;
			cur_p++;
		}
		*size = cur_output_size+1;
		return;
	}

	while(this->data[cur_p]) {
		while(delimiters[deli_cnt]) {
			if(this->data[cur_p] == delimiters[deli_cnt]) {
				no_char_approp = false;
				if(cur_str_size != 0) {
					char *temp_str = new char[cur_str_size+1];
					int j = 0;
					temp_str[cur_str_size] = '\0';
					while(temp_str[j]) {
						temp_str[j] = '\0';
						j++;
					}
					strncpy(temp_str, cur_begin_p, cur_str_size);
					output[cur_output_size] = new String(temp_str);
					//cout << "wow! out new substring is: " << temp_str << endl;
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
	if(cur_str_size>0 || no_char_approp) {
		char *temp_str2 = new char[cur_str_size+1];
		temp_str2[cur_str_size] = '\0';
		int k=0;
		while(temp_str2[k]) {
			temp_str2[k] = '\0';
			k++;
		}
		strncpy(temp_str2, cur_begin_p, cur_str_size);
		String *out_element = new String(temp_str2); 
		output[cur_output_size] = out_element;
		//cout << "wow! out new substring is: " << temp_str2 << endl;
		cur_output_size++;
		delete[] temp_str2;
	}
	*size = cur_output_size;
	//cout << cur_output_size << " = cur_output_size" << endl;
}

int String::to_integer() const{
	int p = 0;
	//cout << "out string = " << this->data << endl;
	while(this->data[p]) {
		//cout << "something" << endl;
		if (isdigit(this->data[p]) == 0) {
			//cout << "not an integer" << endl;
			return 0;
		}
		p++;
	}
	int x = atoi(this->data);
	//cout << "it is an integer = " << x << endl;
	return x;
}

String String::trim() const{
	//cout << this->data << " data" << endl;
	//cout << this->length << " length" << endl;
	/*if(!this->data[0]) {
		cout << "NULL" << endl;
		return(*this);
	}*/
	int front_spaces = 0;
	int back_i = this->length - 1;
	int back_spaces = 0;
	while(this->data[front_spaces] == ' ') {
		front_spaces++;
	}
	while(this->data[back_i] == ' ') {
		back_spaces++;
		this->data[back_i] = '\0';
		back_i--;
	}
	if(back_spaces + front_spaces >= this->length) {
		//cout << "good" << endl;
		return(*this);
	}
	size_t n = this->length - back_spaces - front_spaces;
	//cout << "n = " << n << endl;
	if(n == this->length) {
		//cout << "we return the original string" << endl;
		return String(*this);
	}
	char *temp_str = new char[n+1];
	strncpy(temp_str, this->data+front_spaces, n+1);
	//cout << temp_str << " = temp_str" << endl;
	String new_string = String(temp_str);
	delete[] temp_str;
	return new_string;
}
	
