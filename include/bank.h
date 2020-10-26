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

/**
 * A Card class to implement a physical Card info
 */
class Card
{
    private:
    string cardNumber_;
    string firstName_;
    string lastName_;
    string expDate_;

    public:
    Card(){}
    Card(const string& cardNumber, const string& firstName, const string& lastName, const string& expDate) 
        : cardNumber_(cardNumber), firstName_(firstName), lastName_(lastName), expDate_(expDate) {}

    string cardNumber() const {return cardNumber_;}
    string cardFirstName()   const {return firstName_;}
    string cardLastName()   const {return lastName_;}
    string expDate()    const {return expDate_;}
    bool operator==(const Card& other) const
    {
        return (cardNumber_ == other.cardNumber_ &&
                firstName_  == other.firstName_ &&
                lastName_   == other.lastName_ &&
                expDate_    == other.expDate_);
    }
    
};

/**
 * Class to represent a bank account, this base class is inherited by the 2 sub classes CheckingAccount and SavingAccount
 */
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
            return ((std::hash<string>()(card.cardNumber()))
                   ^(std::hash<string>()(card.cardFirstName()))
                   ^(std::hash<string>()(card.expDate()))
                   ^(std::hash<string>()(card.cardLastName())));
        }
    };
    std::string bankName_;
    unordered_map<Card, pair<string, vector<Account>>, CardHasher> database_;

    public:
    Bank(const string& bankName) : bankName_(bankName) {}

    /**
     * Adding an account to the database, given a card, pin number of the card and the account
     */
    bool addAccount(const Card& card, string pinNumber, const Account& account);

    /**
     * Populate the bank from a CSV file
     */
    bool populateDatabase(const string& databaseFilePath);

    /**
     * Verify a PIN number with the one stored in the database
     */
    bool verifyPin(const Card& card, const string& pinNumber);

    /**
     * Lookup all accounts associated with a given Card
     */
    vector<Account> lookUpAccounts(const Card& card);

    /**
     * Deposit money to a given account
     */
    bool deposit(const Card& card, const Account& account, const unsigned int& amount);

    /**
     * Withdraw money from a given account
     */
    bool withdraw(const Card& card, const Account& account, const unsigned int& amount);

    /**
     * View balance of a given account
     */
    bool viewBalance(const Card& card, const Account& account, unsigned int& balance);
};







