#include "transaction.hpp"
// transaction info
Transaction::Transaction(const std::string &sender, const std::string &receiver,
                         double amount, const std::string &signature)
    : sender(sender), receiver(receiver), amount(amount), signature(signature) {
}

std::string Transaction::getSender() const { return sender; }

std::string Transaction::getReceiver() const { return receiver; }

double Transaction::getAmount() const { return amount; }

std::string Transaction::getSignature() const { return signature; }
