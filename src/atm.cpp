#include "atm.h"

#include <iostream>
#include <string>

using std::string;

namespace atm_controller
{

string KeyPad::getStringInput(const string& messageToUser)
{
    std::cout << messageToUser << std::endl;
    string stringInput;
    std::cin >> stringInput;

    return stringInput;
}

unsigned int KeyPad::getDigitInput(const string& messageToUser)
{
    std::cout << messageToUser << std::endl;
    unsigned int digitInput;
    std::cin >> digitInput;

    return digitInput;
}

void CardReader::readCard()
{
    cardRead_ = Card("003", "Tri Khuu", "01/01/2025");
}

// ================================= ATM =================================
ATM::ATM(const Bank& bank, const string& atmId)
    : bank_(bank), id_(atmId)
{

}


Account ATM::_selectAccount(const Card& card)
{
    vector<Account> accounts = bank_.lookUpAccounts(card);
    string listOfAccountsString;
    std::cout << accounts.size() << std::endl;
    for (int i = 0; i < accounts.size(); i++)
    {
        listOfAccountsString += (std::to_string(i) + ". Account Number: " + accounts[i].accountNumber() + "\n");
    }

    unsigned int selectedAccountIdx = 0;
    while(true)
    {
        string userMessage = "Please select account\n";
        selectedAccountIdx = keypad_.getDigitInput(userMessage + listOfAccountsString);
        if (selectedAccountIdx < accounts.size()) break;
    }
    // auto a = accounts[2];
    return accounts[selectedAccountIdx];

}

Transaction ATM::_selectTransaction()
{
    string listOfTransactionString;
    listOfTransactionString += "1. View Balance\n";
    listOfTransactionString += "2. Deposit\n";
    listOfTransactionString += "3. Withdrawal\n";
    listOfTransactionString += "4. Exit\n";
    string msgToUser = "Please select transaction:\n";

    while(true)
    {
        unsigned int userInput = keypad_.getDigitInput(msgToUser + listOfTransactionString);
        switch(userInput)
        {
            case 1:
            return Transaction::BALANCE;

            case 2:
            return Transaction::DEPOSIT;

            case 3:
            return Transaction::WITHDRAWAL;

            case 4:
            return Transaction::EXIT;
        }
    }

    return Transaction::EXIT;

}

void ATM::readCard()
{
    cardReader_.readCard();
}

bool ATM::authenticate()
{
    Card cardRead = cardReader_.getReadCard();
    string userPin = keypad_.getStringInput("Please enter your PIN");

    auto transactionStatus = bank_.verifyPin(cardRead, userPin);

    if (!transactionStatus)
    {
        std::cerr << "Failed to authenticate" << std::endl;
        return false;
    }

    return true;
}

bool ATM::makeTransaction()
{
    Card cardRead = cardReader_.getReadCard();
    Account account = _selectAccount(cardRead);

    bool endTransaction = false;
    while(!endTransaction)
    {
        Transaction transaction = _selectTransaction();
    
        switch (transaction)
        {
            case Transaction::WITHDRAWAL:
            {
                unsigned int amountWithdrawn = keypad_.getDigitInput("Please enter amount");
                if (bank_.withdraw(cardRead, account, amountWithdrawn))
                {
                    cashSlot_.dispense(amountWithdrawn);
                }
                else
                {
                    std::cout << "Failed to withdraw money" << std::endl << std::endl;
                }
            }
            break;

            case Transaction::DEPOSIT:
            {
                unsigned int amountReceived = keypad_.getDigitInput("Please enter amount");
                if (bank_.deposit(cardRead, account, amountReceived))
                {
                    std::cout << "====> Deposited " << amountReceived << std::endl << std::endl;
                }
                else
                {
                    std::cout << "Failed to deposit money" << std::endl << std::endl ;
                }
            }
            break;

            case Transaction::BALANCE:
            {
                unsigned int balance = 0;
                if (bank_.viewBalance(cardRead, account, balance))
                {
                    std::cout << "====> Balance: " << balance << std::endl << std::endl ;
                }
                else
                {
                    std::cout << "Failed to view balance" << std::endl << std::endl;
                }
            }
            break;

            case Transaction::EXIT:
            {
                endTransaction = true;
            }
            break;
        }
    }

    return true;
}

}