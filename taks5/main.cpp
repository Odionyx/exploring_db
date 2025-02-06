#include <iostream>
#include <exception>
#include "db_customer.h"

#ifdef _WIN32
#include <windows.h>
#pragma execution_character_set( "utf-8")
#endif


int main(int argc, char** argv){
    //setlocale(LC_ALL, "ru-RU");
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::cout<< "Hello!"<< std::endl;

    std::string first_name = "Qwer";
    std::string last_name = "Qwerty";
    std::string email = "qq@qq.qq";
    std::string telephone{ "1234567890"};

    std::string first_name2 = "Abc";
    std::string last_name2 = "Qwerty";
    std::string email2 = "aaaa@qq.aa";
    std::string telephone2{ "90987654321"};

    try{
        Customer cust{ first_name, last_name, email, telephone};
        cust.creates_tables();
        cust.new_customer();
        cust.add_phone_num();
        cust.find_customer();

    }
    //catch (pqxx::sql_error e) {
    //    std::cout << e.what() << std::endl;
    //}
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << __func__ << '.' << std::endl;
    }
    return 0;
}
