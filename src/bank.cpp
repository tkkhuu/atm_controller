#include "bank.h"

#include <iostream>

bool Bank::addUser(const Card& card, string pinNumber, const Account& account)
{
    if (database_.find(card) != database_.end())
    {
        std::cout << "Adding User to Bank failed: User already exists" << std::endl;
        return false;
    }

    database_[card] = {pinNumber, {account}};
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