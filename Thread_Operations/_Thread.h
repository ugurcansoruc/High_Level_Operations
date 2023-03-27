#ifndef THREAD_OPERATIONS__THREAD_H__
#define THREAD_OPERATIONS__THREAD_H__

#include <iostream>
#include <thread>
#include <_Variable.h>
#include <map>

using namespace std;

class Thread_Manager
{
private:
    map<string, thread> _thread_map;
    Variable_Manager variable_manager;
public:
    template<typename... Args>
    void Thread_Olustur(string thread_name ,void(*function), Args... args)
    {
        //thread_name ile ilgili veri kontrolleri gerceklestirilir

        variable_manager.Check_Variable(new String_Controller(thread_name));


        // args... ile argümanlar ayrıştırılır ve her biri ekrana yazdırılır
        ((std::cout << args << " "), ...);
        std::cout << std::endl;
    }
};

#endif // !THREAD_OPERATIONS__THREAD_H__

