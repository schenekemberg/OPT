#ifndef OPTOBJECT_H
#define OPTOBJECT_H
#include <string>

class OptObject
{
public:
    OptObject();
    virtual void optimize() = 0;

protected:
    //Function/////////////////////////////////
    virtual ~OptObject() = 0;



};

#endif // OPTOBJECT_H
