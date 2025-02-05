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
    long int telephone = 0101010101;

    std::string first_name2 = "Abcd";
    std::string last_name2 = "Abcde";
    std::string email2 = "aaa@aaa.aaa";
    long int telephone2 = 1010101010;

    try{
        Customer cust( first_name, last_name, email, telephone);
        cust.creates_tables();


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
