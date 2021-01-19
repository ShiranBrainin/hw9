#ifndef PORT_H
#define PORT_H

#include "string.h"
#include "field.h"

class Port : public Field {
private:
    int range[2];

public:

    Port(String pattern);
    bool set_value(String val);
    bool match_value(String val) const;
};

#endif
