#include "db_customer.h"
#include <iostream>
#include <tuple>
/*
*/
CustoManager::CustoManager( pqxx::connection& other): con{ other}{
    std::cout << "Welcome "<< std::endl;
}

CustoManager::~CustoManager(){
    std::cout<< "~Goodbye "<< std::endl;
}

void CustoManager::createTables(){
    pqxx::work tx{ con};
    tx.exec(
        "CREATE TABLE IF NOT EXISTS customer( "
            "id SERIAL PRIMARY KEY NOT NULL, "
            "first_name TEXT NOT NULL, "
            "last_name TEXT NOT NULL, "
            "email TEXT NOT NULL UNIQUE); "
        "CREATE TABLE IF NOT EXISTS phone_number("
            "id SERIAL PRIMARY KEY NOT NULL,"
            "number VARCHAR(20) UNIQUE,"
            "customer_id INTEGER NOT NULL "
            "REFERENCES customer(id) ON DELETE CASCADE); "
    );
    tx.commit();
}

int CustoManager::addCustomer( const std::string& firstName, 
                               const std::string& lastName, 
                               const std::string& email){
    pqxx::work tx{ con};
    tx.exec(
        "INSERT INTO customer( first_name, last_name, email) "
        "VALUES( '"+tx.esc(firstName)+"', '"+tx.esc(lastName)+"', '"+tx.esc(email)+"'); "
    );
    int custId = tx.query_value< int>(
            "SELECT id FROM customer "
            "WHERE email LIKE '" + tx.esc(email) + "'; "
    );
    tx.commit();
    return custId;
}

void CustoManager::addPhoneNum( int customId, const std::string& phoneNumber){
    pqxx::work tx{ con};
    tx.exec(
        "INSERT INTO phone_number( number, customer_id) "
        "VALUES( '"+ tx.esc(phoneNumber) +"', '"+ std::to_string(customId) +"'); "
    );
    tx.commit();
}

void CustoManager::changeCustomer( int customId, const std::string& firstName,
                    const std::string& lastName, const std::string& email){
    pqxx::work tx{ con};
    tx.exec(
        "UPDATE customer SET first_name= '" + firstName + "', "
        "last_name= '"+ tx.esc(lastName) +"', email= '"+ tx.esc(email) +"'"
        "WHERE id = " + std::to_string(customId) +"; "
    );
    tx.commit();
}

int CustoManager::findCustomer( const std::string& email){
    int custId = 0;
    pqxx::work tx{ con};
    auto results = tx.query< int, std::string, std::string,
        std::string, std::string>(
            "SELECT c.id, c.first_name, c.last_name, c.email, pn.number "
            "FROM customer c JOIN phone_number pn ON c.id = pn.customer_id "
            "WHERE c.email LIKE '" + tx.esc(email) + "'; "
        );
    for (std::tuple<int, std::string, std::string,
        std::string, std::string> row : results) {
        std::cout << "ID: "     << std::get<0>(row)
            << "\t first_name: "<< std::get<1>(row)
            << "\t last_name: " << std::get<2>(row)
            << "\t email: "     << std::get<3>(row)
            << "\t number: "    << std::get<4>(row) << std::endl;
        custId = std::get<0>(row);
    }
    tx.commit();
    return custId;
}

void CustoManager::deletePhoneNum( const std::string& phoneNumber){
    pqxx::work tx{ con};
    tx.exec(
        "DELETE FROM phone_number WHERE number LIKE '"+ 
        tx.esc(phoneNumber) +"'; "
    );
    tx.commit();
}

void CustoManager::deleteCustomer( const std::string& email){
    pqxx::work tx{ con};
    tx.exec(
        "DELETE FROM customer WHERE email LIKE '"+ tx.esc(email) +"' ; "
    );
    tx.commit();
}

void CustoManager::deleteTables( const std::string& table){
    pqxx::work tx{ con};
    tx.exec( "DROP TABLE "+ tx.esc(table) +" ; "); //CASCADE if need
    tx.commit();
}
