#include "db_customer.h"
#include <iostream>
#include <tuple>

Customer::Customer(std::string& first_name_, std::string& last_name_, 
                   std::string& email_, std::string& telephone_){
    this->con = new pqxx::connection(key);
    this->first_name = first_name_;
    this->last_name = last_name_;
    this->email = email_;
    this->telephone = telephone_;
    std::cout<< "Welcome " << ++id<< std::endl;
}

Customer::~Customer(){
    this-> con-> ~connection();
    std::cout<< "~Goodbye "<< std::endl;
}

void Customer::creates_tables() {
    pqxx::work tx{ *con };
    tx.exec(
        "CREATE TABLE IF NOT EXISTS customer( "
            "id SERIAL PRIMARY KEY NOT NULL, "
            "first_name TEXT NOT NULL, "
            "last_name TEXT NOT NULL, "
            "email TEXT NOT NULL); "
        "CREATE TABLE IF NOT EXISTS phone_number("
            "id SERIAL PRIMARY KEY NOT NULL,"
            "number VARCHAR(20),"
            "customer_id INTEGER NOT NULL "
            "REFERENCES customer(id) ON DELETE CASCADE); "
    );
    tx.commit();
}

void Customer::new_customer(){
    pqxx::work tx{ *con};
    tx.exec(
        "INSERT INTO customer( first_name, last_name, email) "
        "VALUES( '" + first_name + "', '" + last_name + "', '" + email + "'); "
    );
    tx.commit();
}

void Customer::add_phone_num(){
    pqxx::work tx{ *con};
    tx.exec(
        "INSERT INTO phone_number( number, customer_id) "
        "VALUES( '" + telephone + ""
        "', '" + std::to_string(id) + "'); "
    );
    tx.commit();
}

void Customer::change_customer(){
    pqxx::work tx{ *con};
    tx.exec(
        "UPDATE customer SET first_name= '" + first_name + "', "
        "last_name= '" + last_name + "', email= '" + email + "'"
        "WHERE id = "+ std::to_string(id) +"; "
    );
    tx.commit();
}

void Customer::find_customer(){
    pqxx::work tx{ *con};
    auto results = tx.query< int, std::string, std::string, 
                                  std::string, std::string>(
        "SELECT c.id, c.first_name, c.last_name, c.email, pn.number "
        "FROM customer c "
        "JOIN phone_number pn ON c.id = pn.customer_id "
        "WHERE c.first_name LIKE '" + temp + "' OR "
              "c.last_name LIKE '" + temp + "' OR "
              "c.email LIKE '" + temp + "' OR "
              "pn.number LIKE '" + temp + "'; "
    );
    for (std::tuple<int, std::string, std::string, 
                         std::string, std::string> row : results){
        std::cout << "ID: "     << std::get<0>(row)
           << "\t first_name: " << std::get<1>(row)
           << "\t last_name: "  << std::get<2>(row)
           << "\t email: "      << std::get<3>(row)
           << "\t number: "     << std::get<4>(row)<< std::endl;
    }
    tx.commit();
}

void Customer::delete_phone_num(){
    pqxx::work tx{ *con };
    tx.exec(
        "DELETE FROM phone_number "
        "WHERE number LIKE '" + temp + "'; "
    );
    tx.commit();
}

void Customer::delete_customer(){
    pqxx::work tx{ *con };
    tx.exec(
        "DELETE FROM customer"
        "WHERE email LIKE '" + temp + "' ; "
    );
    tx.commit();
}

void Customer::delete_tables(){
    pqxx::work tx{ *con };
    tx.exec(
        "DROP TABLE '" + temp + "' ; "
    );
    tx.commit();
}
