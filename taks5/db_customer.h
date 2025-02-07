#pragma once
#include <string>
#include <pqxx/pqxx>
/*
*/
class CustoManager {
public:
    void createTables();
    int addCustomer( const std::string& firstName, 
                     const std::string& lastName, const std::string& email);
    void addPhoneNum( int customId, const std::string& phoneNumber);
    void changeCustomer( int customId, const std::string& firstName,
          const std::string& lastName, const std::string& email);
    int findCustomer( const std::string& email);
    
    void deletePhoneNum( const std::string& phoneNumber);
    void deleteCustomer(const std::string& email);
    void deleteTables( const std::string& table);
    //[[nodiscard("PURE FUN")]]
    CustoManager(void)= delete;
    CustoManager(pqxx::connection& other);
    virtual ~CustoManager();
private:
    pqxx::connection& con;
};
