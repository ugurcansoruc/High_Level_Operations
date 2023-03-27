#include <_Variable.h>

String_Controller::String_Controller(string string_to_check)
{
	this->string_to_check = string_to_check;
}

bool String_Controller::Check_Null_Ref()
{
	return false; //(this->string_to_check != nullptr);
}


bool Variable_Manager:: Check_Variable(IVariable_Controller * ivariable_controller)
{
	bool result = ivariable_controller->Check_All_Control();

	delete ivariable_controller;

	return result;
}

bool String_Controller::Check_All_Control()
{
	return false;
}
