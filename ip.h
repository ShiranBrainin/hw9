#ifndef IP_H
#define IP_H

#include "field.h"

#define MASK_SEGMENT 2
#define SEGMENTS 4

class Ip : public Field {
private:
    unsigned int low;
    unsigned int high;

public:

    Ip(String pattern);
    bool set_value(String val);
    bool match_value(String val) const;
};



#endif
