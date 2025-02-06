#pragma once
#include <string>
#include <pqxx/pqxx>

class Customer{
public:
    void creates_tables();

    void new_customer();
    void add_phone_num();
    void change_customer();
    void find_customer();

    void delete_phone_num();
    void delete_customer();
    void delete_tables();

    Customer(void)= default;
    Customer(std::string& first_name_, std::string& last_name_, 
             std::string& email_, std::string& telephone_);
    virtual ~Customer();
private:
    pqxx::connection* con;
    std::string key{ 
        "host=localhost "
        "port=5432 "
        "dbname=test_pqxx "
        "user=postgres "
        "password=passWORD"};
    std::string first_name= "";
    std::string last_name= "";
    std::string email= "";
    std::string temp = "Qwerty";
    std::string telephone= "";
    int id= 0;
};
