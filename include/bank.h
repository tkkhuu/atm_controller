#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::unordered_map;
using std::vector;


class Card
{
    private:
    string cardNumber_;
    string cardName_;
    string expDate_;

    public:
    Card(){}
    Card(const string& cardNumber, const string& cardName, const string& expDate) 
        : cardNumber_(cardNumber), cardName_(cardName), expDate_(expDate) {}

    string cardNumber() const {return cardNumber_;}
    string cardName()   const {return cardName_;}
    string expDate()    const {return expDate_;}
    bool operator==(const Card& other) const
    {
        return (cardNumber_ == other.cardNumber() &&
                cardName_   == other.cardName()   &&
                expDate_    == other.expDate());
    }
    
};

class Account
{
    protected:
    string accountNumber_;
    unsigned int accountBalance_;
    unsigned int withdrawLimit_;

    public:
    Account(const string& accountNumber) 
        : accountNumber_(accountNumber), withdrawLimit_(-1) {}

    virtual unsigned int getBalance() 
    {
        return accountBalance_;
    }

    virtual void deposit(const unsigned int& ammount)
    {
        accountBalance_ += ammount;
    }

    virtual bool withdraw(const unsigned int& ammount)
    {
        if (withdrawLimit_ > 0 && ammount > withdrawLimit_) 
        {
            std::cout << "Withdrawal Limit Exceeded" << std::endl;
            return false;
        }
        else if (ammount > accountBalance_)
        {
            std::cout << "Not enough money" << std::endl;
            return false;
        }

        accountBalance_ -= ammount;
        return true;
    }

    string accountNumber() const {return accountNumber_;}

    bool operator==(const Account& other) const
    {
        return accountNumber_ == other.accountNumber();
    }

    string toString() const
    {
        string accountString = "Account Number: ";
        accountString += accountNumber_;
        return accountString;
    }
};

class SavingAccount : public Account
{
    private:
    double interestRate_;

    public:
    SavingAccount(const string& accountNumber, const unsigned int& balance) 
        : Account(accountNumber)
        {
            accountBalance_ = balance;
        }
};

class CheckingAccount : public Account
{
    public:
    CheckingAccount(const string& accountNumber, const unsigned int& balance)
        : Account(accountNumber)
        {
            accountBalance_ = balance;
        }
};

/**
 * This class is a place holder for the API provided from the bank, this is a simple interface so that we can test our ATM
 */
class Bank
{
    struct CardHasher
    {
        size_t operator()(const Card& card) const
        {
            return ((std::hash<string>()(card.cardNumber())
                   ^(std::hash<string>()(card.cardName()) << 1)) >> 1)
                   ^(std::hash<string>()(card.expDate()) << 1);
        }
    };
    std::string bankName_;
    unordered_map<Card, pair<string, vector<Account>>, CardHasher> database_;

    public:
    Bank(const string& bankName) : bankName_(bankName) {}
    bool addUser(const Card& card, string pinNumber, const Account& account);
    bool verifyPin(const Card& card, const string& pinNumber);
    vector<Account> lookUpAccounts(const Card& card);
    bool deposit(const Card& card, const Account& account, const unsigned int& amount);
    bool withdraw(const Card& card, const Account& account, const unsigned int& amount);
    bool viewBalance(const Card& card, const Account& account, unsigned int& balance);
};







