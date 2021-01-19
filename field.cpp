#include "field.h"
enum TOT_SUBSTRINGS 4;
enum TYPE_SUBSTR 1;

Field::Field(String pattern) : 
	pattern(pattern) {
	this->type = this->get_type();
}

Field:~Field() {
	delete this->pattern;
}

field_type Field::get_type() const{
	String **substr = new String*[TOT_SUBSTRINGS];
	int *sub_size;
	this->pattern.split("=-",substr,sub_size);
	if(substr[TYPE_SUBSTR]->equals("port")) {
		return PORT;
	} else if(substr[TYPE_SUBSTR]->equals("ip")) {
		return IP;
	} else {
		return GENERIC;
	}
}