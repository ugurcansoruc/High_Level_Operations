#include <iostream>
#include <_Thread.h>

using namespace std;

void test_1(int x)
{
	printf("%d--------\n", x);
}


void test_2(int x)
{
	printf("--------%d\n", x);
}

int main()
{
	Thread_Manager* _Thread_Manager = new Thread_Manager();
	
	_Thread_Manager->Create_Thread("thread_1",test_1, 1);
	_Thread_Manager->Create_Thread("thread_2", test_2, 2);

	IThread * thread_1 = _Thread_Manager->GetThread("thread_1");
	IThread * thread_2 = _Thread_Manager->GetThread("thread_2");
	
	thread_1->run();
	thread_2->run();
	this_thread::sleep_for(chrono::seconds(5));

	return 0;
}
