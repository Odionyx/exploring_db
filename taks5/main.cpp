#include <iostream>
#include <exception>
#include <memory>
#include <pqxx/pqxx>
#include "db_customer.h"

#ifdef _WIN32
#include <windows.h>
#pragma execution_character_set( "utf-8")
#endif
/*
*/
int main(int argc, char** argv){
    //setlocale(LC_ALL, "ru-RU");
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::cout<< "Hello!"<< std::endl;

    int customId = 1;
    std::string table = "customer";
    //std::string table = "phone_number";

    std::string firstName = "Qwer";
    std::string lastName = "Qwerty";
    std::string email = "qq@qq.qq";
    std::string phoneNum{ "1234567890"};

    std::string firstName2 = "Abc";
    std::string lastName2 = "Qwerty";
    std::string email2 = "aaaa@qq.aa";
    std::string phoneNum2{ "90987654321"};

    std::string key{ 
        "host=localhost "
        "port=5432 "
        "dbname=test_pqxx "
        "user=postgres "
        "password=passWORD"
    };
    try{
        pqxx::connection conn( key);
        CustoManager cust(conn);

        cust.createTables();
        //customId = cust.addCustomer( firstName, lastName, email);
        //cust.addPhoneNum( customId, phoneNum);
        //cust.findCustomer( email);
        //cust.changeCustomer( customId, firstName2, lastName2, email2);
        //cust.deletePhoneNum( phoneNum);
        //cust.deleteCustomer( email2);
        //cust.deleteTables( table);

    }
    catch (pqxx::sql_error e) {
        std::cout << e.what() << std::endl;
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << __func__ << '.' << std::endl;
    }
    return 0;
}

