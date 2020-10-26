#include "bank.h"

#include <fstream>
#include <iostream>
#include <sstream>


bool Bank::addAccount(const Card& card, string pinNumber, const Account& account)
{
    if (database_.find(card) != database_.end())
    {
        if (database_[card].first != pinNumber)
        {
            std::cout << "Adding Account to Bank failed: Conflicting PIN Number on the same card" << std::endl;
            return false;
        }
        for (auto acc : database_[card].second)
        {
            if (acc == account)
            {
                std::cout << "Adding Account to Bank failed: Account with the same account number already exist" << std::endl;
                return false;
            }
        }

        database_[card].second.push_back(account);
        
    }
    else
    {
        database_[card] = {pinNumber, {account}};
    }
    return true;
}

bool Bank::verifyPin(const Card& card, const string& pinNumber)
{
    if (database_.find(card) == database_.end())
    {
        std::cout << "No card info found" << std::endl;
        return false;
    }

    if (database_[card].first != pinNumber)
    {
        std::cout << "Invalid PIN" << std::endl;
        return false;
    }

    return true;
}

vector<Account> Bank::lookUpAccounts(const Card& card)
{
    if (database_.find(card) == database_.end())
    {
        return {};
    }

    return database_[card].second;
}

bool Bank::deposit(const Card& card, const Account& account, const unsigned int& amount)
{
    if (database_.find(card) == database_.end())
    {
        return false;
    }

    for (Account& acc : database_[card].second)
    {
        if (acc == account)
        {
            acc.deposit(amount);
            return true;
        }
    }

    return false;
}

bool Bank::withdraw(const Card& card, const Account& account, const unsigned int& amount)
{
    if (database_.find(card) == database_.end())
    {
        return false;
    }

    for (Account& acc : database_[card].second)
    {
        if (acc == account)
        {
            return acc.withdraw(amount);
        }
    }

    return false;
}

bool Bank::viewBalance(const Card& card, const Account& account, unsigned int& balance)
{
    if (database_.find(card) == database_.end())
    {
        return false;
    }

    for (Account& acc : database_[card].second)
    {
        if (acc == account)
        {
            balance = acc.getBalance();
            return true;
        }
    }

    return false;
}

bool Bank::populateDatabase(const string& databaseFilePath)
{
    std::ifstream csvFileStream;
    csvFileStream.open(databaseFilePath);
    if (!csvFileStream.is_open())
    {
        std::cout << "Error opening file at " << databaseFilePath << std::endl;
        return false;
    }

    std::cout << "Populate bank with the following users" << std::endl;

    vector<string> row;
    string line, word;
    while(!csvFileStream.eof())
    {
        row.clear();
        std::getline(csvFileStream, line);
        std::stringstream ss(line); 
  
        while(std::getline(ss, word, ',')){
            
            row.push_back(word);
        }

        if (row[6] == "Checking")
        {
            addAccount(Card(row[0], row[1], row[2], row[3]), row[4], CheckingAccount(row[5], std::atoi(row[7].c_str())));
        }
        else
        {
            addAccount(Card(row[0], row[1], row[2], row[3]), row[4], SavingAccount(row[5], std::atoi(row[7].c_str())));
        }

        std::cout << "Card number:     " << row[0] << std::endl
                  << "Card first name: " << row[1] << std::endl
                  << "Card last name:  " << row[2] << std::endl
                  << "Card Exp Date:   " << row[3] << std::endl
                  << "PIN Number:      " << row[4] << std::endl
                  << "Acc Number:      " << row[5] << std::endl
                  << "Acc Type:        " << row[6] << std::endl
                  << "Acc Balance:     " << row[7] << std::endl
                  << "============" << std::endl;
    }

    return true;
}