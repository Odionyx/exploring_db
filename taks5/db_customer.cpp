#include "db_customer.h"
#include <iostream>

Customer::Customer(std::string& first_name_, std::string& last_name_, 
                   std::string& email_, long int& telephone_){
    this->con = new pqxx::connection(key);
    this->first_name = first_name_;
    this->last_name = last_name_;
    this->email = email_;
    this->telephone = telephone_;
    std::cout<< "Customer: " << ++count<< std::endl;
}

Customer::~Customer(){
    this-> con-> ~connection();
    std::cout<< "~Customer: " << count--<< std::endl;
}

void Customer::creates_tables(){
    pqxx::work tx{ *con};
    tx.exec(
        "CREATE TABLE IF NOT EXISTS customer( "
            "id SERIAL PRIMARY KEY, "
            "first_name TEXT, "
            "last_name TEXT, "
            "email TEXT); "
        "CREATE TABLE IF NOT EXISTS phone_number("
            "id SERIAL PRIMARY KEY,"
            "name TEXT,"
            "phone_number_id INTEGER NOT NULL REFERENCES customer(id) ON DELETE CASCADE);"
    );
    tx.commit();
}

void Customer::new_customer(){
    //    pqxx::work tx{ c};
    //    tx.exec();
    //    tx.commit();
}

void Customer::add_phone_num(){
    //    pqxx::work tx{ c};
    //    tx.exec();
    //    tx.commit();
}

void Customer::change_customer(){
    //    pqxx::work tx{ c};
    //    tx.exec();
    //    tx.commit();
}

void Customer::find_customer(){
    //    pqxx::work tx{ c};
    //    tx.exec();
    //    tx.commit();
}

void Customer::delete_phone_num(){
    //    pqxx::work tx{ c};
    //    tx.exec();
    //    tx.commit();
}

void Customer::delete_customer(){
    //    pqxx::work tx{ c};
    //    tx.exec();
    //    tx.commit();
}

void Customer::delete_tables(){
    //    pqxx::work tx{ c};
    //    tx.exec();
    //    tx.commit();
}
