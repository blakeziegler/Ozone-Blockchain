#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <vector>

class Transaction {
public:
    Transaction(const std::string& sender, const std::string& receiver, double amount, const std::string& signature);

    std::string getSender() const;
    std::string getReceiver() const;
    double getAmount() const;
    std::string getSignature() const;
    
    bool isValid() const; // Method to validate the transaction

private:
    std::string sender;
    std::string receiver;
    double amount;
    std::string signature;
};

#endif // TRANSACTION_HPP
