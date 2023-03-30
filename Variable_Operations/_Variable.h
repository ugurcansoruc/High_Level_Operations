#ifndef VARIABLE_OPERATIONS__VARIABLE_H__
#define VARIABLE_OPERATIONS__VARIABLE_H__

#include <iostream>

using namespace std;

class IVariable_Controller
{
public:
    virtual bool Check_All_Control() = 0;
    virtual bool Check_Null_Ref() = 0;
private:

};

class String_Controller :public IVariable_Controller
{
private:
    string string_to_check;
public:
    String_Controller(string string_to_check);
    bool Check_All_Control();
    bool Check_Null_Ref();
};

class Variable_Manager
{
public:
    bool Check_Variable(IVariable_Controller * ivariable_controller);

private:

};


#endif // VARIABLE_OPERATIONS__VARIABLE_H__
