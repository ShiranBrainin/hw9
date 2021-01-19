#ifndef FIELD_H
#define FIELD_H

#include "string.h"

enum field_type { IP=0, PORT, GENERIC };

class Field {
private:
    String pattern;
    field_type type;

protected:

    Field(String pattern, field_type type);

public:

    Field(String pattern);

    ~Field();

    field_type get_type() const;

    bool set_value(String val);

    bool match_value(String val) const;

    bool match(String packet);

};



#endif
